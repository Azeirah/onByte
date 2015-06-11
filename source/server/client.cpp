#include "client.h"

#define assertS(truthy, message) if (!(truthy)) {cout << message << " on line " << __LINE__ << " in file " << __FILE__ << ". Check was " << #truthy << endl;}

SocketClient::SocketClient(string host, int port) {
    // setting member variables
    this->port = port;
    this->host = host;

    // opening socket file
    this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    assertS(this->socketFileDescriptor >= 1, "Error opening socket");

    // creating reference to server
    this->server = gethostbyname(this->host.c_str());
    assertS(this->server != NULL, "Error, no such host");

    // configuring server address
    bzero((char *) &this->serverAddress, sizeof(this->serverAddress));
    this->serverAddress.sin_family = AF_INET;
    bcopy(
      (char *) this->server->h_addr,
      (char *) &this->serverAddress.sin_addr.s_addr, this->server->h_length
    );

    this->serverAddress.sin_port = htons(this->port);

    // connecting to server
    bool succesvolConnection = connect(
      this->socketFileDescriptor,
      (struct sockaddr *) &this->serverAddress,
      sizeof(this->serverAddress)
    ) >= 0;
    assertS(succesvolConnection, "Error connecting, maybe there's no socket server running..?");
}

bool SocketClient::send(char * data) {
  int n = write(this->socketFileDescriptor, data, strlen(data));
  assertS(n >= 0, "Error writing to socket");

  return n >= 0;
}

bool SocketClient::receive(char * data) {
    int n;

    n = read(this->socketFileDescriptor, data, MAX_MESSAGE_LENGTH - 1);
    assertS(n >= 0, "Received no data.");

    return n >= 0;
}

void SocketClient::stop() {
    close(this->socketFileDescriptor);
}
