#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <poll.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include "rlib.h"
#include  <signal.h>

// Macros for some fixed things
typedef int bool;
#define TRUE 1
#define FALSE 0
#define ACK_PACKET_LEN 8
#define DATA_PACKET_HEADER_LEN 12
#define DATA_PACKET_MAX_LEN 512

// Enumerating different packets for better understanding
enum packet_type {
  DATA_PACKET, ACK_PACKET, INVALID_PACKET
};

// Define reliable_state structure
struct reliable_state {
  rel_t *next;		             	 		 // Linked list for traversing all connections
  rel_t **prev;
  conn_t *c;			             			 // This is the connection object
  // Add your own data fields below this
  struct sockaddr_storage ss;        // Network peer
  int window_size;                   // The size of the window
  packet_t *pkts_sent;               // An array of packets sent with size = window size
  packet_t *pkts_recvd;              // An array of packets received with size = window size
  bool *is_pkt_recvd;                // An array of booleans indicating which packets in the receive window have been received
  uint32_t *is_data_pkt;             // Variable to check
  uint64_t *pkt_send_time;           // An array of timestamps representing when each packet in the window was sent
  uint32_t last_seqno_sent;          // The sequence number of the last sent packet
  uint32_t last_seqno_recvd;         // The sequence number of the last received packet
  uint32_t last_ackno_sent;          // The last ackno sent to the other side of the connection
  uint32_t last_ackno_recvd;         // The last ackno received from the other side of the connection
  uint16_t last_pkt_bytes_output;    // The number of bytes of the last packet that have been sent to the output connection already
  bool last_pkt_recvd_eof;           // Signifies whether the last received data packet was an EOF
  bool read_eof;                     // Whether or not the last read input was EOF
  int timeout;                       // The maximum timeout before attempting to re-send a packet
};

rel_t *rel_list;

// Various utility function definitions
void pkt_ntoh(packet_t *pkt);
void pkt_hton(packet_t *pkt);
bool is_pkt_recvd(rel_t *r, packet_t *pkt);
uint32_t get_pkt_idx(rel_t *r, uint32_t seqno);
uint16_t output_pkt(rel_t *r, packet_t *pkt, uint16_t start, uint16_t payload_len);
int send_ack_pkt(rel_t *r, uint32_t ackno);
int send_new_data_pkt(rel_t *r, char *data, uint16_t payload_len);
int send_data_pkt(rel_t *r, packet_t *pkt);
enum packet_type get_pkt_type(packet_t *pkt, size_t n);
bool check_cksum(packet_t *pkt);
uint64_t get_time();

// Creates a new reliable protocol session, returns NULL on failure.
// Exactly one of c and ss should be NULL.
// ss is NULL when called from rlib.c while c is NULL when this function is called from rel_demux.
rel_t * rel_create(conn_t *c, const struct sockaddr_storage *ss, const struct config_common *cc) {
  rel_t *r;
  r = xmalloc (sizeof (*r));
  memset (r, 0, sizeof (*r));
  if (!c) {
    c = conn_create (r, ss);
    if (!c) {
      free(r);
      return NULL;
    }
  }
  r->c = c;
  r->next = rel_list;
  r->prev = &rel_list;
  if (rel_list) {
    rel_list->prev = &r->next;
  }
  rel_list = r;
  // Do any other initialization you need here
  if (ss == NULL){
    // Do Nothing
  }
  else{
    r->ss = *ss;
  }
  r->window_size = cc->window;
  r->pkts_sent = xmalloc(r->window_size * sizeof(packet_t));
  r->pkts_recvd = xmalloc(r->window_size * sizeof(packet_t));
  r->is_data_pkt = xmalloc(sizeof(uint32_t));
  r->is_pkt_recvd = xmalloc(r->window_size * sizeof(bool));
  r->pkt_send_time = xmalloc(r->window_size * sizeof(uint64_t));
  for (int i = 0; i < r->window_size; i++) {
    r->is_pkt_recvd[i] = FALSE;
    r->pkt_send_time[i] = 0;
  }
  r->last_pkt_bytes_output = 0;
  r->last_pkt_recvd_eof = FALSE;
  r->read_eof = FALSE;
  r->timeout = cc->timeout;
  r->last_seqno_sent = 0;
  r->last_ackno_sent = 1;
  r->last_seqno_recvd = 1;
  r->last_ackno_recvd = 1;
  return r;
}

void rel_destroy(rel_t *r) {
  if (r->next) {
    r->next->prev = r->prev;
  }
  *r->prev = r->next;
  conn_destroy (r->c);
  // Free any other allocated memory here
  free(r->is_data_pkt);
  free(r->pkts_sent);
  free(r->pkts_recvd);
  free(r->is_pkt_recvd);
  free(r->pkt_send_time);
  free(r);
}

// This function only gets called when the process is running as a server and must handle connections from multiple clients.
// You have to look up the rel_t structure based on the address in the sockaddr_storage passed in.
// If this is a new connection (sequence number 1), you will need to allocate a new conn_t using rel_create().
// Pass rel_create NULL for the conn_t, so it will know to allocate a new connection.
void rel_demux(const struct config_common *cc, const struct sockaddr_storage *ss, packet_t *pkt, size_t len){
  // We do not have to implement this
}

void rel_recvpkt(rel_t *r, packet_t *pkt, size_t n) {
  enum packet_type pkt_type = get_pkt_type(pkt, n);
  pkt_ntoh(pkt);

  // If data pkt
  if (pkt_type == DATA_PACKET) {
    fprintf(stderr,"\t%d receive data(%d): cksum = %d, len = %d, ack_no = %d, seq_no = %d\n", getpid(), pkt->len, pkt->cksum, pkt->len, pkt->ackno, pkt->seqno);
    // Process data pkt
    // If next expected seq no not received or pkt received out of window
    if ((pkt->seqno < r->last_ackno_sent) || (pkt->seqno >= r->last_ackno_sent + r->window_size)) {
      fprintf(stderr, "%d: dropping out of window pkt: seq_no = %d\n", getpid(), pkt->seqno);
      send_ack_pkt(r, r->last_ackno_sent); 
      return;
    }
    // If data pkt received after receiving closing connection pkt
    if (r->last_pkt_recvd_eof == TRUE) {
      fprintf(stderr, "%d: ignoring data packet, already received EOF\n", getpid());
      send_ack_pkt(r, r->last_ackno_sent);
      return;
    }
    // If duplicate pkt received
    if (is_pkt_recvd(r, pkt)){
      fprintf(stderr, "%d: ignoring duplicate pkt: seq_no = %d\n", getpid(), pkt->seqno);
      send_ack_pkt(r, r->last_ackno_sent); 
      return;
    }
    // If received EOF while some packets are yet stored in buffer
    if (pkt->len == DATA_PACKET_HEADER_LEN) {
      // Has buffered pkts
      if (r->last_ackno_sent < r->last_seqno_recvd) {
        fprintf(stderr, "%d: ignoring EOF, waiting for pkt, seq_no = %d\n", getpid(), r->last_ackno_sent);
        send_ack_pkt(r, r->last_ackno_sent);
      }
      else {
        fprintf(stderr, "%d: received EOF\n", getpid());
        r->last_pkt_recvd_eof = TRUE;
        conn_output(r->c, NULL, 0);
        send_ack_pkt(r, r->last_ackno_sent + 1);
      }
      return;
    }
    // Add pkt to receive window
    uint32_t idx = get_pkt_idx(r, pkt->seqno);
    r->is_pkt_recvd[idx] = TRUE;
    r->pkts_recvd[idx] = *pkt;
    if (pkt->seqno > r->last_seqno_recvd) {
      r->last_seqno_recvd = pkt->seqno;
    }
    // output all correctly received pkt
    rel_output(r);
  }
  
  // Else if ack pkt
  else if (pkt_type == ACK_PACKET) {
    fprintf(stderr,"\t%d receive ack(%d): cksum = %d, len = %d, ack_no = %d\n", getpid(), pkt->len, pkt->cksum, pkt->len, pkt->ackno);
    // Process ack pkt;
    // If duplicate ack received
    if (pkt->ackno <= r->last_ackno_recvd) {
      fprintf(stderr, "%d: ignoring already received ack: ack_no = %d\n", getpid(), pkt->ackno);
      return;
    }
    // If next expected ack doesn't received
    if (pkt->ackno > r->last_seqno_sent + 1) {
      fprintf(stderr, "%d: invalid ack: ack_no = %d\n", getpid(), pkt->ackno);
      return;
    }
    // Correct ack
    r->last_ackno_recvd = pkt->ackno;
    rel_read(r);
  }
}

void rel_read(rel_t *r) {
  // Already got EOF, no more read
  if (r->read_eof == TRUE) {
    fprintf(stderr, "%d: already read EOF\n", getpid());
    return;
  }

  // Get count of number of packets to be sent
  uint32_t pkts_to_send = r->window_size - (r->last_seqno_sent - r->last_ackno_recvd + 1);

  for(int i=0; i<pkts_to_send; i++) {
    char buf[DATA_PACKET_MAX_LEN - DATA_PACKET_HEADER_LEN];
    // Read from application using conn_input (in rlib.h)
    int bytes_read = conn_input(r->c, buf, DATA_PACKET_MAX_LEN - DATA_PACKET_HEADER_LEN);
    fprintf(stderr,"%d: READ len = %d\n", getpid(), bytes_read);

    // If empty, exit the while loop
    if (bytes_read == 0) {
      return;
    }
    // Else if read success, create new data packet with read data and transmit
    else if(bytes_read > 0){
      send_new_data_pkt(r, buf, bytes_read);
    }
    // else if error in reading, i.e., CTRL+D is pressed, asking to terminate connection.
    else{
      fprintf(stderr, "%d: READ EOF\n", getpid());
      r->read_eof = TRUE;
      // send EOF to other side
      send_new_data_pkt(r, NULL, 0);
      return;
    }
  }
}

void rel_output(rel_t *r) {
  uint32_t idx = get_pkt_idx(r, r->last_ackno_sent);
  uint16_t num_pkts = 0;
  // While there are pkts in buffer in correct order
  while (r->is_pkt_recvd[idx] != FALSE){
    packet_t *pkt = &r->pkts_recvd[idx];
    // Ouput pkt using utility function output_pkt to application
    uint16_t bytes_outputted = output_pkt(r, pkt, r->last_pkt_bytes_output, pkt->len - DATA_PACKET_HEADER_LEN);
    // If cannot output, call error and destroy the pckt
    if (bytes_outputted < 0){
      rel_destroy(r);
      fprintf(stderr,"error calling conn_output\n");
      return;
    }
    // If all bytes of pkt not sent for some reason, do not send next pkt but exit.
    // Next time rel_ouput is called, the remaining bytes will only be sent.
    uint16_t bytes_left = (pkt->len - DATA_PACKET_HEADER_LEN) - (bytes_outputted + r->last_pkt_bytes_output);
    if (!(bytes_left <= 0)){
      r->last_pkt_bytes_output += bytes_outputted;
      return;
    }
    // Else pkt sent to application, empty the buffer slot
    r->is_pkt_recvd[idx] = FALSE;
    r->last_pkt_bytes_output = 0;
    // Increment count and get next pkt
    num_pkts++;
    idx = get_pkt_idx(r, r->last_ackno_sent + num_pkts);
  }

  // If some pkts were sent
  if (num_pkts != 0) {
    send_ack_pkt(r, r->last_ackno_sent + num_pkts);
  }
}

void rel_timer() {
	// Retransmit any packets that need to be retransmitted
  rel_t *r = rel_list;
  while (r != NULL) {
    // If already ack received, do nothing
    if (r->last_seqno_sent < r->last_ackno_recvd) {
      // Do nothing
    }
    else {
      int idx = get_pkt_idx(r, r->last_ackno_recvd);
      packet_t *pkt = &r->pkts_sent[idx];
      // If time exceeded timeout, re-transmit pkt.
      if (!(get_time() - r->pkt_send_time[idx] <= r->timeout)) {
        fprintf(stderr, "%d: re-transmitting pkt due to timeout, seq_no = %d\n", getpid(), pkt->seqno);
        send_data_pkt(r, pkt);
      }
    }
    // If already received EOF from both sides, do not re-transmit and destroy
    // Received EOF, Read EOF, No buffered pkts and No un-sent ack
    if (r->last_pkt_recvd_eof == TRUE && r->read_eof == TRUE && r->last_seqno_sent == (r->last_ackno_recvd - 1) && r->last_ackno_sent > r->last_seqno_recvd){
      fprintf(stderr, "%d: closing connection\n", getpid());
      rel_t *next = r->next;
      // Destroy this connection
      rel_destroy(r);
      r = next;
    }
    // Else go to next connection
    else {
      r = r->next;
    }
  }
}

// Returns if the given buffer idx has un-acked pkt
bool is_pkt_recvd(rel_t *r, packet_t *pkt) {
  return r->is_pkt_recvd[get_pkt_idx(r, pkt->seqno)];
}

// Returns buffer index in which pkt is kept according to seq number
uint32_t get_pkt_idx(rel_t *r, uint32_t seqno) {
  return (seqno-1)%r->window_size;
}

// Output a pkt to application
uint16_t output_pkt(rel_t *r, packet_t *pkt, uint16_t start, uint16_t payload_len) {
  // Check if buffer space is availble to output
  uint16_t bufspace = conn_bufspace(r->c);
  if (bufspace <= 0) {
    fprintf(stderr, "%d: no bufspace available\n", getpid());
    return 0;
  }

  // Find number of bytes to output
  uint16_t bytes_to_output = bufspace;
  if(bytes_to_output > payload_len - start){
  	bytes_to_output = payload_len - start;
  }

  // Copy required data to our buffer and send this to application using conn_output
  char buf[bytes_to_output];
  memcpy(buf, pkt->data + start, bytes_to_output);
  int bytes_outputted = conn_output(r->c, buf, bytes_to_output);

  // guaranteed not to be 0 because we checked bufspace
  assert(bytes_outputted != 0);
  return bytes_outputted;
}

// To send a new data pkt over UDP
int send_new_data_pkt(rel_t *r, char *data, uint16_t payload_len) {
  // Create and initialize new data pkt
  packet_t pkt;
  pkt.cksum = 0;
  pkt.len = DATA_PACKET_HEADER_LEN + payload_len;
  pkt.ackno = r->last_ackno_sent;
  pkt.seqno = r->last_seqno_sent + 1;
  memcpy(pkt.data, data, payload_len);

  // Add pkt to window;
  uint32_t idx = get_pkt_idx(r, pkt.seqno);
  r->pkts_sent[idx] = pkt;
  r->pkt_send_time[idx] = get_time();
  if (pkt.seqno > r->last_seqno_sent) {
    r->last_seqno_sent = pkt.seqno;
  }

  // Send over UDP
  return send_data_pkt(r, &pkt);
}

// To send an ack pkt over UDP
int send_ack_pkt(rel_t *r, uint32_t ackno) {
  // Create and initialize new ack pkt
  packet_t pkt;
  pkt.cksum = 0;
  pkt.len = ACK_PACKET_LEN;
  pkt.ackno = ackno;

  // Convert all values to network byte order using hton to send pkt over UDP
  pkt_hton(&pkt);
  pkt.cksum = cksum((void *)&pkt, ACK_PACKET_LEN);
  int bytes_sent = conn_sendpkt(r->c, &pkt, ACK_PACKET_LEN);
  pkt_ntoh(&pkt);

  // If sent successfully, update last ack number
  if (bytes_sent > 0) {
    r->last_ackno_sent = ackno;
    fprintf(stderr,"\t%d send ack (%d): cksum = %d, len = %d, ack_no = %d\n",getpid(), ACK_PACKET_LEN, pkt.cksum, pkt.len, pkt.ackno);
  }
  // If no bytes sent, give error
  else if (bytes_sent == 0) {
    fprintf(stderr, "%d: no bytes sent calling conn_sendpkt", getpid());
  }
  // If conn_sendpkt return error
  else {
    fprintf(stderr,"error calling conn_sendpkt\n");
  }

  return bytes_sent;
}

// To send an existing data pkt over UDP
int send_data_pkt(rel_t *r, packet_t *pkt) {
  uint16_t pkt_len = pkt->len;

  // Convert all values to network byte order using hton to send pkt over UDP
  pkt_hton(pkt);
  pkt->cksum = cksum((void *)pkt, pkt_len);
  int bytes_sent = conn_sendpkt(r->c, pkt, pkt_len);
  pkt_ntoh(pkt);

  // If sent successfully, update last ack number
  if(bytes_sent > 0){
    fprintf(stderr,"\t%d send data (%d): cksum = %d, len = %d, ack_no = %d, seq_no = %d\n",getpid(), pkt->len, pkt->cksum, pkt->len, pkt->ackno, pkt->seqno);
  }
  // If no bytes sent, give error
  else if (bytes_sent == 0){
    fprintf(stderr, "no bytes sent calling conn_sendpkt\n");
  }
  // If conn_sendpkt return error
  else{
    fprintf(stderr,"error calling conn_sendpkt\n");
  }

  // Update timestamp of re-transmitted pkt
  uint32_t idx = get_pkt_idx(r, pkt->seqno);
  r->pkt_send_time[idx] = get_time();

  return bytes_sent;
}

// Convert pkt to network byte order
void pkt_hton(packet_t *pkt) {
  if (!(pkt->len < DATA_PACKET_HEADER_LEN)) {
    pkt->seqno = htonl(pkt->seqno);
  }
  pkt->len = htons(pkt->len);
  pkt->ackno = htonl(pkt->ackno);
}

// Convert pkt to host byte order
void pkt_ntoh(packet_t *pkt) {
  pkt->len = ntohs(pkt->len);
  pkt->ackno = ntohl(pkt->ackno);
  if (!(pkt->len < DATA_PACKET_HEADER_LEN)){
    pkt->seqno = ntohl(pkt->seqno);
  }
}

// Get pkt type based on header
enum packet_type get_pkt_type(packet_t *pkt, size_t n) {
  // If header size < 8, invalid
  if (!(n >= ACK_PACKET_LEN)) {
    fprintf(stderr, "%d: invalid packet length: %zu\n", getpid(), n);
    return INVALID_PACKET;
  }
  // If checksum not matches, invalid
  if (check_cksum(pkt) != TRUE) {
    fprintf(stderr, "%d: invalid checksum: %d\n", getpid(), pkt->cksum);
    return INVALID_PACKET;
  }
  
  int pkt_len = ntohs(pkt->len);
  // If 12 <= lenght <= 512, data pkt 
  if (DATA_PACKET_HEADER_LEN <= pkt_len && pkt_len <= DATA_PACKET_MAX_LEN) {
    return DATA_PACKET;
  }
  // If length == 8, ack pkt
  if (pkt_len == ACK_PACKET_LEN) {
    return ACK_PACKET;
  }
  // else invalid
  fprintf(stderr, "%d: invalid packet length: %d", getpid(), pkt_len);
  return INVALID_PACKET;
}

// Computes and compares checksum of pkt
bool check_cksum(packet_t *pkt) {
  uint16_t len = ntohs(pkt->len);
  if (!(len != 0 && len <= sizeof(*pkt))) {
    return FALSE;
  }
  uint16_t cksum_val = pkt->cksum;
  pkt->cksum = 0;
  uint16_t cksum_computed = cksum((void *)pkt, len);
  pkt->cksum = cksum_val;
  if (cksum_val != cksum_computed) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// Get timestamp values
uint64_t get_time() {
  struct timespec tp;
  int ret = clock_gettime(CLOCK_MONOTONIC, &tp);
  if (ret < 0) {
    fprintf(stderr, "error calling clock_gettime\n");
  }
  return (tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
}