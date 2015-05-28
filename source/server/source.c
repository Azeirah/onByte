/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void assertS(int truthy, char* message) {
    if (!truthy) {
        printf("%s at line %i", message, __LINE__);
    }
}

void error(const char *msg) {
    perror(msg);
    printf("");
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd;
    int newsockfd;
    int portNumber;
    int n;

    socklen_t clilen;
    char      buffer[256];
    struct    sockaddr_in serv_addr;
    struct    sockaddr_in cli_addr;

    assertS(argc >= 2, "ERROR, no port provided");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assertS(sockfd >= 0, "ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));

    portNumber                = atoi(argv[1]);
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port        = htons(portNumber);

    int bindResult = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0;
    assertS(!bindResult, "ERROR on binding socket");

    listen(sockfd, 5);
    clilen    = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    assertS(newsockfd >= 0, "ERROR on accept");
    bzero(buffer, 256);

    n = read(newsockfd, buffer, 255);
    assertS(n >= 0, "ERROR reading from socket");
    printf("Here is the message: %s\n", buffer);

    n = write(newsockfd,"I got your message",18);
    assertS(n < 0, "ERROR writing to socket");

    close(newsockfd);
    close(sockfd);

    return 0;
}
