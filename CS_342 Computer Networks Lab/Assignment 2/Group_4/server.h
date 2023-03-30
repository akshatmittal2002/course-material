#include <signal.h>
#include "global.h"
int serverSkt, clientSkt;

// Breaks one line from the database into hostname and ip 
void getHostIPMapping(char *line, char *ip, char *host){
	int linePtr = 0;

	// Set 0th character as 3 to indicate type 3 response
	host[0] = '3';
	ip[0] = '3';
	int ptr = 1;
	
	// Skip extra spaces in start
	while (line[linePtr] == ' ')
		linePtr++;
	
	// Store first word in host
	while (line[linePtr] != ' '){
		host[ptr] = line[linePtr];
		ptr++;
		linePtr++;
	}

	// Skip extra spaces in between
	while (line[linePtr] == ' ')
		linePtr++;
	
	// Store second word in ip
	ptr = 1;
	while (line[linePtr] != '\n' && line[linePtr] != ' '){
		ip[ptr] = line[linePtr];
		ptr++;
		linePtr++;
	}
}

// Gracefully releases the socket resources if Ctrl C is pressed
void signalHandler(int signum){
	close(serverSkt);
	close(clientSkt);
	exit(0);
}