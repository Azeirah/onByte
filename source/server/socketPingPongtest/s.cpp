#include "server.h"
// I've provided two separate programs to demonstrate usage of a socket client (c.cpp) and a socket server (s.cpp)
// usage:
// ./s 2000
// ./c "localhost" 2000

int main(int argc, char const *argv[]) {
    char * receive;
    char * send = "Blabal lalabaaalaaa!!";

    SocketServer *server = new SocketServer(1338);

    while (true) {
        server->receive(receive);
        server->send(send);
    }
}
