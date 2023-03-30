#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CACHE_SIZE 3
#define MAXSIZE 256

void closeAndExit(int sockfd, int exitcode){
    close(sockfd);
    exit(exitcode);
}

int getPort(int sockfd, char *input){
    char *end;
    int number = strtol(input, &end, 10);
    if (input == end){
        printf("Invalid port number!\n");
        closeAndExit(sockfd, 1);
    }
    else
        // continue
    return number;
}

void my_inet_pton(int family, const char *strptr, void *addrptr){
    int n;
    if ((n = inet_pton(family, strptr, addrptr)) <= 0){
        printf("Error: inet_pton error for %s!\n", strptr);
        exit(1);
    }
}
