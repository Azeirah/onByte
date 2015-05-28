#include "client.h"

void assertS(int truthy, string message) {
    // this is my most brilliant invention, prints line numbers also!
    if (!truthy) {
        cout << message << " on line " << __LINE__ << endl;
    }
}

SocketClient::SocketClient(string host, int port) {
    // setting member variables
    this->port = port;
    this->host = host;

    // opening socket file
    this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    assertS(this->socketFileDescriptor >= 1, "Error opening socket@client");

    // creating reference to server
    this->server = gethostbyname(this->host.c_str());
    assertS(this->server != NULL, "Error, no such host@client");

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
    assertS(succesvolConnection, "Error connecting@client");
}

void SocketClient::start() {
    // declaring variables
    char buffer[MAX_MESSAGE_LENGTH];
    int  n;

    // getting user input
    cout << "Please enter your message: " << endl;
    bzero(buffer, MAX_MESSAGE_LENGTH);
    fgets(buffer, MAX_MESSAGE_LENGTH - 1, stdin);
    n = write(this->socketFileDescriptor, buffer, strlen(buffer));
    assertS(n >= 0, "Error writing to socket@client");

    // reading response
    bzero(buffer, MAX_MESSAGE_LENGTH);
    n = read(socketFileDescriptor, buffer, MAX_MESSAGE_LENGTH - 1);
    assertS(n >= 0, "Error reading from socket@client");
}

void SocketClient::stop() {
    close(this->socketFileDescriptor);
}
