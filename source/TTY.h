#pragma once

#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

using namespace std;
// #include "onByte.h"

class TTY {
public:
    int tty;

    TTY();

    void receive(char *);
    void sendString(string);
    void stop();
};
