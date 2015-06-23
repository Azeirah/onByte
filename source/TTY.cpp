#include "TTY.h"

TTY::TTY() {
    this->tty = open("/dev/ttyS2", O_RDWR | O_NONBLOCK | O_NOCTTY);

    if (this->tty == -1) {
        cout << "Error while opening file.\n" << endl;
        perror("open");
    }
}

void TTY::receive (char *receiver) {
    int n = read(this->tty, receiver, 64);
    if (n == -1) {
        perror("receive");
    }
}

void TTY::sendString (string data) {
    int n = write(this->tty, data.c_str(), data.length());
    if (n <= 0) {
        perror("send string");
    }
}

void TTY::stop() {
    close(this->tty);
}
