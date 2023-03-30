#include "proxy.h"

int main(int argc, char **argv){
    signal(SIGINT, signalHandler);

    char request[MAXSIZE] = {0};
    char response[MAXSIZE] = {0};
    struct sockaddr_in proxyAddr, clientAddr;

    // Clear all variables
	bzero(request, sizeof(request));
    bzero(response, sizeof(response));
	bzero(&proxyAddr, sizeof(proxyAddr));
	bzero(&clientAddr, sizeof(clientAddr));
	bzero(&proxySkt, sizeof(proxySkt));
	bzero(&clientSkt, sizeof(clientSkt));
    bzero(&ID, sizeof(ID));

    // Verify command format
    if (argc != 4){
        printf("Error: Invalid command format!\n");
        printf("Use ./p <ProxyPort> <ServerIP> <ServerPort>\n");
        exit(1);
    }
    else;
        // continue

    // Creating shared memory region for proxy cache.
    ID = shmget(IPC_PRIVATE, sizeof(struct proxyCache), IPC_CREAT | 0666);
    myCache = (struct proxyCache *)shmat(ID, NULL, 0);
    bzero(myCache, sizeof(struct proxyCache));

    // Initialising semaphore for mutually exclusive access to cache between child processes
    sem_init(&(myCache->mutex), 1, 1);

    // Create server side listening socket
    proxySkt = socket(AF_INET, SOCK_STREAM, 0);
    if (proxySkt < 1){
        printf("Error: Socket could not be created!\n");
        exit(1);
    }
    else;
        // continue

    // Bind address to the server socket
    proxyAddr.sin_family = AF_INET;
    proxyAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    proxyAddr.sin_port = htons(getPort(proxySkt, argv[1]));
    if (bind(proxySkt, (struct sockaddr *)&proxyAddr, sizeof(proxyAddr)) < 0){
        printf("Error: Could not bind socket!\n");
        closeAndExit(proxySkt, 1);
    }
    else;
        // continue

    // Wait for connection requests from clients
    if (listen(proxySkt, 25) >= 0)
        printf("Proxy Server listening for request...\n\n");
    else{
        printf("Listen Error\n");
        closeAndExit(proxySkt, 1);
    }

    while(1){
        int length = sizeof(clientAddr);

        // Accept a client's request to communicate with server
        if ((clientSkt = accept(proxySkt, (struct sockaddr *)&clientAddr, (socklen_t *)&length)) >= 0){
            printf("Connection established with %s : %d \n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        }
        else{
            printf("Error: Could not connect to client!\n");
            continue;
        }

        // Fork a child process for concurrent service to multiple clients
        pid_t child_pid;
        int status = 0;
        if ((child_pid = fork()) == 0){
            // Inside child process
            // Close copy of listening socket in child
            close(proxySkt);
            // Acknowledge request from client
            read(clientSkt, request, MAXSIZE);
            // Print the received request on server
			printf("Request Type = %c\n", request[0]);
            printf("Request = %s\n", request + 1);

            // Lock the cache
            sem_wait(&(myCache->mutex));
            // Search request in the cache
            if (searchProxyCache(response, request) < 0){
                // If not available, forward request to DNS server
                if (getResponsefromDNSServer(argv[2], argv[3], response, request) < 0){
                    // If communication with server fails or request not found in server too, send Type 4 Response
                    bzero(response, MAXSIZE);
                    printf("Oops! Entry not found in server's database too!\n");
                    strcpy(response, "4Entry not found in the database");
                }
                // Else update cache
                else if (response[0] == '3')
                    saveInCache(response, request);
            }

            // Unlock the cache
            sem_post(&(myCache->mutex));
            // Send response to client
            write(clientSkt, response, MAXSIZE);
            // Close socket and exit child process
            closeAndExit(clientSkt, 0);
            exit(0);
        }

        // Wait for child to finish
		waitpid(child_pid, &status, 0);

        // Print current cache
        printf("\nPrinting Cache...\n");
        int i = myCache->front;
        while(1){
            if(i == myCache->back)
                break;
            printf("%s : %s\n", myCache->hostname[i], myCache->ip[i]);
            i++;
            i%=(CACHE_SIZE + 1);
        }

		// Close client-socket in parent since child caters to client
		close(clientSkt);
		printf("\nConnection Closed!\n\n");
    }

    // Delete shared memory resource, close proxy-socket and exit.
    shmctl(ID, IPC_RMID, NULL);
    close(proxySkt);
    exit(0);
}