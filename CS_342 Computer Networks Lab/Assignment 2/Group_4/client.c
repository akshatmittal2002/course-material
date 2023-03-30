#include "client.h"

int main(int argc, char **argv){
	char reqMessage[MAXSIZE];
	struct sockaddr_in servaddr;

	// Verify Command Format
	if (argc != 3){
		printf("Error: Invalid command format!\n");
		printf("Use ./c <ServerIP> <ServerPort>\n");
		exit(1);
	}

	// Create a socket for client
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 1){
		printf("Error: Could not create socket!\n");
		exit(1);
	}

	// Fill server IP and port
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(getPort(sockfd, argv[2]));
	my_inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	// Connect to server
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) >= 0)
		printf("Connected to proxy server successfully!\n\n");
	else{
		printf("Error: Could not connect to proxy server!\n");
		closeAndExit(sockfd, 1);
	}

	// Get user request
	if (getUserRequest(reqMessage) >= 0){
		// Send DNS request to server
		if (write(sockfd, reqMessage, MAXSIZE) != MAXSIZE){
			printf("Error: Could not send request to proxy server!\n");
			closeAndExit(sockfd, 1);
		}
		else
			printf("Request sent!\n");

		// Clear reqMessage in order to fill it with server response
		bzero(reqMessage, sizeof(reqMessage));

		// Print server response
		if(getResponse(sockfd, reqMessage) < 0)
			printf("Error: Could not receive response from proxy server!\n");
	}
	else
		closeAndExit(sockfd, 1);

	// Close the connection
	printf("\nClosing Connection!\n");
	closeAndExit(sockfd, 0);
}