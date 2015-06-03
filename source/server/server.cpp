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
    listen(this->socketFileDescriptor, 5);
    clientLength            = sizeof(this->serverAddress);
    newSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress, &clientLength);

    assertS(newSocketFileDescriptor >= 0, "Error on accept");
}

bool SocketServer::send(Json::Value *data) {
    string encodedValue = data->toStyledString();

    cout << "Sending " << encodedValue << endl;
    int n = write(this->newSocketFileDescriptor, encodedValue.c_str(), strlen(encodedValue.c_str()) - 1);
    assertS(n >= 0, "Error writing to socket@client");

    return n >= 0;
}

bool SocketServer::receive(Json::Value *receiver) {
    char buffer[MAX_MESSAGE_LENGTH];
    int n;
    Json::Reader reader;

    n = read(this->newSocketFileDescriptor, buffer, MAX_MESSAGE_LENGTH - 1);
    reader.parse(buffer, *receiver, false);

    return n >= 0;
}

void SocketServer::stop() {
    close(this->newSocketFileDescriptor);
    close(this->socketFileDescriptor);
}
