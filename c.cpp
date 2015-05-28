#include "client.h"

int main() {
  SocketClient *client = new SocketClient("localhost", 1337);
  client.start();
}
