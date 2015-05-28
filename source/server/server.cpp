#include "server.h"

void assertS(int truthy, string message) {
    if (!truthy) {
        cout << message << " on line " << __LINE__ << endl;
    }
}

SocketServer::SocketServer(int port) {
    // setting port
    this->port = port;
    assertS(port > 0, "No port provided@server...");

    // opening socket
    // SOCK_STREAM = use tcp stream sockets, not udp.
    this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    assertS(this->socketFileDescriptor >= 0, "Error opening socket@server");

    // configuring server address
    bzero((char *) &serverAddress, sizeof(this->serverAddress));

    this->serverAddress.sin_family      = AF_INET;
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    this->serverAddress.sin_port        = htons(port);

    // binding socket
    bool bindResult = bind(this->socketFileDescriptor, (struct sockaddr *) &this->serverAddress, sizeof(this->serverAddress)) < 0;
    assertS(!bindResult, "Error on binding socket@server");
}

void SocketServer::start() {
    // declaring variables
    struct sockaddr_in clientAddress;
    socklen_t          clientLength;
    int                n;
    char               buffer[MAX_MESSAGE_LENGTH];

    // start listening
    // what's that 5?...
    listen(this->socketFileDescriptor, 5);
    clientLength            = sizeof(this->serverAddress);
    newSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress, &clientLength);

    assertS(newSocketFileDescriptor >= 0, "Error on accept@server");

    // empty buffer
    bzero(buffer, MAX_MESSAGE_LENGTH);
    // read from socket
    n = read(newSocketFileDescriptor, buffer, MAX_MESSAGE_LENGTH - 1);

    assertS(n >= 0, "Error reading from socket@server");
    cout << "Received message " << buffer << endl;

    n = write(newSocketFileDescriptor, "I got your message", 18);
}

void SocketServer::stop() {
  close(this->newSocketFileDescriptor);
  close(this->socketFileDescriptor);
}
