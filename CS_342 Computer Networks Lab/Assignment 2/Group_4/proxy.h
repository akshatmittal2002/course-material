#include <netinet/in.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <time.h>
#include "global.h"

struct proxyCache{
    int front;
    int back;
    char hostname[CACHE_SIZE + 1][MAXSIZE];
    char ip[CACHE_SIZE + 1][MAXSIZE];
    sem_t mutex;
};

// Global variables
int proxySkt, clientSkt, sockfd;
int ID;
struct proxyCache *myCache;

// Sends request to DNS Server when proxy doesn't have mapping in its cache.
int getResponsefromDNSServer(char *dnsIP, char *dnsPort, char *response, const char *request){
    struct sockaddr_in dnsServer;
    bzero(response, sizeof(response));
    bzero(&dnsServer, sizeof(dnsServer));

    // Create socket for proxy server to communicate with DNS server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 1){
        printf("Error: Could not create socket to communicate with DNS server!\n");
        return -1;
    }
    else;
        // continue

    // Fill DNS server IP and port information
    dnsServer.sin_family = AF_INET;
    dnsServer.sin_port = htons(strtol(dnsPort, NULL, 10));
    my_inet_pton(AF_INET, dnsIP, &dnsServer.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&dnsServer, sizeof(dnsServer)) >= 0)
        printf("Connected to DNS server successfully!\n");
    else{
        printf("Error: Could not connect to DNS server!\n");
        close(sockfd);
        return -1;
    }

    if (write(sockfd, request, MAXSIZE) == MAXSIZE)
        printf("Request Sent!\n");
    else{
        printf("Error: Could not send request to DNS server!\n");
        close(sockfd);
        return -1;
    }

    if (read(sockfd, response, MAXSIZE) >= 0)
        printf("Response Received!\n");
    else{
        printf("Error: Could not receive response from DNS server!\n");
        close(sockfd);
        return -1;
    }   

    // Close the socket
    printf("Closing Connection with DNS server!\n");
    close(sockfd);
    return 0;
}

// Searches for the requested hostname/ip in the proxy's cache.
int searchProxyCache(char *response, const char *request){
    int pos = -1;
    if (request[0] == '2'){
        for (int i = myCache->front; i != myCache->back; i = (i + 1) % (CACHE_SIZE + 1)){
            if (strcasecmp(request + 1, myCache->ip[i]) == 0){
                pos = i;
                break;
            }
            else;
                // continue
        }
        if (pos != -1){
            response[0] = '3';
            memcpy(response + 1, myCache->hostname[pos], MAXSIZE - 1);
        }
        else;
            // continue
    }
    else{
        for (int i = myCache->front; i != myCache->back; i = (i + 1) % (CACHE_SIZE + 1)){
            if (strcasecmp(request + 1, myCache->hostname[i]) == 0){
                pos = i;
                break;
            }
        else;
            // continue
        }
        if (pos != -1){
            response[0] = '3';
            memcpy(response + 1, myCache->ip[pos], MAXSIZE - 1);
        }
        else;
            // continue
    }
    if (pos != -1){
        printf("Found in cache!\n");
        return 0;
    }
    else{
        printf("Not found in cache!\n");
        return -1;
    }
}

// Saves hostname/IP obtained from DNS Server response in cache
void saveInCache(const char *response, const char *request){
    printf("Updating cache!\n");

    // Clear the cache location
    bzero(myCache->hostname[myCache->back], MAXSIZE);
    bzero(myCache->ip[myCache->back], MAXSIZE);
    
    // Place requsted ip and hostname in cache
    if (request[0] == '1'){
        memcpy(myCache->ip[myCache->back], response + 1, MAXSIZE - 1);
        memcpy(myCache->hostname[myCache->back], request + 1, MAXSIZE - 1);
    }
    else{
        memcpy(myCache->hostname[myCache->back], response + 1, MAXSIZE - 1);
        memcpy(myCache->ip[myCache->back], request + 1, MAXSIZE - 1);
    }

    // Update back and front pointers
    myCache->back = (myCache->back + 1) % (CACHE_SIZE + 1);
    if (myCache->front == myCache->back)
        myCache->front = (myCache->front + 1) % (CACHE_SIZE + 1);
    else;
        // continue
}

// Gracefully releases the socket resources and shared memory cache
void signalHandler(int signum){
    close(sockfd);
    close(proxySkt);
    close(clientSkt);
    shmctl(ID, IPC_RMID, NULL);
    exit(0);
}