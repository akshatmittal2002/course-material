#include <netinet/in.h>
#include <ctype.h>
#include "global.h"

// Prints the response from server
int getResponse(int sockfd, void *buffer){
	// Get response from server
	if(read(sockfd, buffer, MAXSIZE) < 0)
		return -1;

	// Print the response
	printf("\nResponse received!\n");
	printf("Response Type: %c\n", ((char *)buffer)[0]);
	printf("Response Message: %s\n", ((char *)buffer) + 1);

	// Clear the buffer
	bzero(buffer, MAXSIZE);
	return 0;
}

// Clears standard input buffer of any trailing \n 
void clearStdin(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Takes user's request from input and saves it in requestBuffer.
int getUserRequest(char *requestBuffer){
	bzero(requestBuffer, MAXSIZE);
	printf("Enter the request type: ");
	scanf("%c%*c", &requestBuffer[0]);
	if (requestBuffer[0] != '1' && requestBuffer[0] != '2'){
		printf("Invalid request type!\n");
		return -1;
	}
	printf("Enter the request message: ");
	scanf("%s", requestBuffer + 1);
	return 0;
}