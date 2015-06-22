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
    bool send   (string);

    SocketServer(int port);
    void stop();
};
