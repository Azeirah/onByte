#include "../client.h"
#include <unistd.h>
#// I've provided two separate programs to demonstrate usage of a socket client (c.cpp) and a socket server (s.cpp)
// usage:
// ./s 2000
// ./c "localhost" 2000


int main(int argc, char const *argv[]) {
    char * receive = new char[20];
    char * send    = new char[20];

    send = "Client";

    SocketClient *client = new SocketClient("localhost", 1338);

    usleep(5000000);
    client->send(send);

    while (true) {};

}
