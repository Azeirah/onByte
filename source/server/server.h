#pragma once

#include "socketCommons.h"

class SocketServer {
  private:
    int                port;
    int                socketFileDescriptor;
    int                newSocketFileDescriptor;
    struct sockaddr_in serverAddress;
  public:
    int send   (char *);
    bool receive(char *);
    int sendString(string);

    SocketServer(int port);
    void stop();
};
