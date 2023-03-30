#include "server.h"

int main(int argc, char **argv){
	signal(SIGINT, signalHandler);

	char hostname[MAXSIZE];
	char ip[MAXSIZE];
	char request[MAXSIZE];
	char line[2*MAXSIZE];
	struct sockaddr_in serverAddr, clientAddr;

	// Clear all variables
	bzero(hostname, sizeof(hostname));
	bzero(ip, sizeof(ip));
	bzero(request, sizeof(request));
	bzero(line, sizeof(line));
	bzero(&serverAddr, sizeof(serverAddr));
	bzero(&clientAddr, sizeof(clientAddr));
	bzero(&serverSkt, sizeof(serverSkt));
	bzero(&clientSkt, sizeof(clientSkt));

	// Verify command format
	if (argc != 2){
		printf("Error: Invalid command format!\n");
		printf("Use ./s <ServerPort>\n");
		exit(1);
	}

	// Create server side listening socket
	serverSkt = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSkt < 1){
		printf("Error: Socket could not be created!\n");
		exit(1);
	}

	// Bind address to the server socket
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(getPort(serverSkt, argv[1]));
	if (bind(serverSkt, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
		printf("Error: Could not bind socket!\n");
		closeAndExit(serverSkt, 1);
	}

	// Wait for connection requests from clients
	if (listen(serverSkt, 25) >= 0)
		printf("DNS Server listening for request...\n\n");
	else{
		printf("Listen Error!\n");
		closeAndExit(serverSkt, 1);
	}

	while(1){
		int length = sizeof(clientAddr);

		// Accept a client's request to communicate with server
		if ((clientSkt = accept(serverSkt, (struct sockaddr *)&clientAddr, (socklen_t *)&length)) < 0){
			printf("Error: Could not connect to proxy server!\n");
			continue;
		}
		else
			printf("Connection established with %s : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		// Fork a child process for concurrency
		pid_t child_pid;
		int status = 0;
		if ((child_pid = fork()) == 0){
			// Inside child process
			// Close the copy of listening socket present in child
			close(serverSkt);
			// Acknowledge request sent by client
			read(clientSkt, request, MAXSIZE);
			// Print the received request on server
			printf("Request Type = %c\n",  request[0]);
			printf("Request = %s\n", request + 1);
			
			// Open DNS server's database
			FILE *filePtr = fopen("database.txt","r");
			int found = 0;
			while (fgets(line, 2*MAXSIZE, filePtr)){
				// Parse the read line from database to get ip and hostname
				getHostIPMapping(line, ip, hostname);

				// If request was for hostname and ip found in database, Send hostname for type 2 request
				if (request[0] == '2' && strcasecmp(ip + 1, request + 1) == 0){
					write(clientSkt, hostname, MAXSIZE);
					found = 1;
				}
				// Else if request was for ip and hostname found in database, Send ip for type 1 request
				else if (request[0] == '1' && strcasecmp(hostname + 1, request + 1) == 0){
					write(clientSkt, ip, MAXSIZE);
					found = 1;
				}

				// Clear out arrays that are reused
				bzero(hostname, sizeof(hostname));
				bzero(ip, sizeof(ip));
				bzero(line, sizeof(line));

				// If information found in database, break the process
				if(found == 1)
					break;
			}

			// If information not found in database, Send type 4 response
			if (found != 1){
				printf("Oops! Entry not found in database\n");
				bzero(request, sizeof(request));
				strcpy(request, "4Entry not found in the database!");
				write(clientSkt, request, MAXSIZE);
			}

			// Close file, socket and exit child process
			fclose(filePtr);
			closeAndExit(clientSkt, 0);
			exit(0);
		}

		// Wait for child to finish
		waitpid(child_pid, &status, 0);

		// Close client-socket in parent since child caters to client
		printf("Connection Closed!\n\n");
		close(clientSkt);
	}
	closeAndExit(serverSkt, 0);
}
