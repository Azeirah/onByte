#pragma once

#include "socketCommons.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

class SocketClient {
  private:
    string             host;
    int                port;
    int                socketFileDescriptor;
    struct sockaddr_in serverAddress;
    struct hostent     *server;
    bool               send(Json::Value *);
    bool               receive(Json::Value);
  public:
    SocketClient(string host, int port);
    void start();
    void stop();
};
