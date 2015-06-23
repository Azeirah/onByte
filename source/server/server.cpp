#include "server.h"

#define assertS(truthy, message) if (!(truthy)) {cout << message << " on line " << __LINE__ << " in file " << __FILE__ << ".cpp, Check was " << #truthy << endl;}

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

    int flag = 1;
    setsockopt(this->socketFileDescriptor, IPPROTO_TCP, TCP_NODELAY, (char*) &flag, sizeof(int));

    // configuring server address
    bzero((char *) &serverAddress, sizeof(this->serverAddress));

    this->serverAddress.sin_family      = AF_INET;
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    this->serverAddress.sin_port        = htons(port);

    // binding socket
    bool bindResult = bind(this->socketFileDescriptor, (struct sockaddr *) &this->serverAddress, sizeof(this->serverAddress));
    assertS(bindResult >= 0, "Error on binding socket");

    // start listening
    // what's that 5?...
    cout << "Waiting for a client to connect to the socket server... Use threads to make this nonblocking?" << endl;
    listen(this->socketFileDescriptor, 5);
    clientLength            = sizeof(this->serverAddress);
    newSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress, &clientLength);

    assertS(newSocketFileDescriptor >= 0, "Error on accept");
}

int SocketServer::sendString(string data) {
    return this->send((char *) data.c_str());
}

int SocketServer::send(char * data) {
    int n = write(this->newSocketFileDescriptor, data, strlen(data));
    assertS(n >= 0, "Error writing to socket");

    return n;
}

bool SocketServer::receive(char * receiver) {
    int n;

    n = read(this->newSocketFileDescriptor, receiver, MAX_MESSAGE_LENGTH - 1);
    assertS(n >= 0, "Error receiving data");

    return n >= 0;
}

void SocketServer::stop() {
    close(this->newSocketFileDescriptor);
    close(this->socketFileDescriptor);
}
