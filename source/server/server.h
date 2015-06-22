#pragma once

#include "socketCommons.h"

class SocketServer {
  private:
    int                port;
    int                socketFileDescriptor;
    int                newSocketFileDescriptor;
    struct sockaddr_in serverAddress;
  public:
    bool send   (char *);
    bool receive(char *);
    bool sendString(string);

    SocketServer(int port);
    void stop();
};
