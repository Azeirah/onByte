#include "client.h"
// I've provided two separate programs to demonstrate usage of a socket client (c.cpp) and a socket server (s.cpp)
// usage:
// ./s 2000
// ./c "localhost" 2000

int main() {
    SocketClient *client = new SocketClient("localhost", 1337);
    client->start();
}
