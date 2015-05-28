/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define MAX_MESSAGE_LENGTH 512

using namespace std;

class SocketServer {
  private:
    int port;
    int socketFileDescriptor;
    int newSocketFileDescriptor;
    int n;
  public:
    SocketServer(int port);
    void start();
};

void assertS(int truthy, string message) {
    if (!truthy) {
        cout << message << " on line " << __LINE__ << endl;
    }
}

void error(const char *msg) {
    perror(msg);
    printf("");
    exit(1);
}

SocketServer::SocketServer(int port) {
    this->port = port;
    assertS(port > 0, "No port provided@server:26...");

    socklen_t clientLength;
    char      buffer[MAX_MESSAGE_LENGTH];
    struct    sockaddr_in serverAddress;
    struct    sockaddr_in clientAddress;

    // SOCK_STREAM = use tcp stream sockets, not udp.
    this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    assertS(this->socketFileDescriptor >= 0, "Error opening socket@server:34");

    bzero((char *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons(port);

    bool bindResult = bind(this->socketFileDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0;
    assertS(!bindResult, "Error on binding socket@server");

    // what's that 5?...
    listen(this->socketFileDescriptor, 5);
    clientLength            = sizeof(serverAddress);
    newSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress, &clientLength);
    assertS(newSocketFileDescriptor >= 0, "Error on accept@server");

    bzero(buffer, MAX_MESSAGE_LENGTH);
    n = read(newSocketFileDescriptor, buffer, MAX_MESSAGE_LENGTH - 1);
    assertS(n >= 0, "Error reading from socket@server");
    printf("Here is the message: %s", buffer);

    n = write(newSocketFileDescriptor, "I got your message", 18);

    close(newSocketFileDescriptor);
    close(socketFileDescriptor);
}

int main(int argc, char *argv[]) {
    printf("Creating new server on port 1337");
    SocketServer server = new SocketServer(1337);
}
