#include "server.h"

// #define assertS

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

bool SocketServer::send(Json::Value *data) {
  string encodedValue = data->toStyledString();

  cout << "Sending " << encodedValue << endl;
  int n = write(this->newSocketFileDescriptor, encodedValue.c_str(), strlen(encodedValue.c_str()) - 1);
  assertS(n >= 0, "Error writing to socket@client");

  return n >= 0;
}

bool SocketServer::receive(Json::Value receiver) {
    char buffer[MAX_MESSAGE_LENGTH];
    int n;
    Json::Reader reader;

    n = read(this->newSocketFileDescriptor, buffer, MAX_MESSAGE_LENGTH - 1);
    reader.parse(buffer, receiver, false);

    cout << "Received " << receiver.toStyledString() << endl;
    cout << "Plucking 'ping' out of data: " << receiver.get("ping", "no ping...") << endl;

    return n >= 0;
}

void SocketServer::start() {
    // declaring variables
    struct sockaddr_in clientAddress;
    socklen_t          clientLength;
    Json::Value        toSend;
    Json::Value        toReceive;

    // start listening
    // what's that 5?...
    listen(this->socketFileDescriptor, 5);
    clientLength            = sizeof(this->serverAddress);
    newSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress, &clientLength);

    assertS(newSocketFileDescriptor >= 0, "Error on accept@server");

    toSend["pong"] = true;

    // keep listening forever.
    while (true) {
        this->receive(toReceive);
        assertS(this->send(&toSend) >= 0, "Error writing to socket@server");
    }
}

void SocketServer::stop() {
    close(this->newSocketFileDescriptor);
    close(this->socketFileDescriptor);
}
