#include "server.h"
// I've provided two separate programs to demonstrate usage of a socket client (c.cpp) and a socket server (s.cpp)
// usage:
// ./s 2000
// ./c "localhost" 2000

int main(int argc, char const *argv[]) {
    SocketServer *server = new SocketServer(1338);
    server->start();
}
