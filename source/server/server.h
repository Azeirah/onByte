#pragma once

#include "socketCommons.h"

class SocketServer {
  private:
    int                port;
    int                socketFileDescriptor;
    int                newSocketFileDescriptor;
    struct sockaddr_in serverAddress;
    bool               send(Json::Value *);
    bool               receive(Json::Value);
  public:
    SocketServer(int port);
    void start();
    void stop();
};
