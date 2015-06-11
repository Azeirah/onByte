#include "server.h"

#define assertS(truthy, message) if (!truthy) {cout << message << " on line " << __LINE__ << " in file " << __FILE__ << endl;}

SocketServer::SocketServer(int port) {
    // declaring variables
    struct sockaddr_in clientAddress;
    socklen_t          clientLength;

    // setting port
    this->port = port;
    assertS(port > 0, "No port provided...");

    // opening socket
    // SOCK_STREAM = use tcp stream sockets, not udp.
    this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    assertS(this->socketFileDescriptor >= 0, "Error opening socket");

    // configuring server address
    bzero((char *) &serverAddress, sizeof(this->serverAddress));

    this->serverAddress.sin_family      = AF_INET;
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    this->serverAddress.sin_port        = htons(port);

    // binding socket
    bool bindResult = bind(this->socketFileDescriptor, (struct sockaddr *) &this->serverAddress, sizeof(this->serverAddress)) < 0;
    assertS(!bindResult, "Error on binding socket");

    // start listening
    // what's that 5?...
    cout << "Waiting for a client to connect to the socket server... Use threads to make this nonblocking?" << endl;
    listen(this->socketFileDescriptor, 5);
    clientLength            = sizeof(this->serverAddress);
    newSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress, &clientLength);

    assertS(newSocketFileDescriptor >= 0, "Error on accept");
}

bool SocketServer::send(char * data) {
    cout << "Sending " << data << endl;
    int n = write(this->newSocketFileDescriptor, data, strlen(data));
    assertS(n >= 0, "Error writing to socket@client");

    return n >= 0;
}

bool SocketServer::receive(char * receiver) {
    char buffer[MAX_MESSAGE_LENGTH];
    int n;

    n = read(this->newSocketFileDescriptor, buffer, MAX_MESSAGE_LENGTH - 1);
    assertS(n >= 0, "Error receiving data");

    return n >= 0;
}

void SocketServer::stop() {
    close(this->newSocketFileDescriptor);
    close(this->socketFileDescriptor);
}
