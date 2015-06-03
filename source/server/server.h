#pragma once

#include "socketCommons.h"

class SocketServer {
  private:
    int                port;
    int                socketFileDescriptor;
    int                newSocketFileDescriptor;
    struct sockaddr_in serverAddress;
  public:
    bool               send   (Json::Value *);
    bool               receive(Json::Value *);
    SocketServer(int port);
    void stop();
};
