#pragma once

#include "../shapes/Rectangle.h"

// another rectangle, "wooh!" for reuse
class BallFollower : public Rectangle {
public:
    void update(float, vector<char *>);
    BallFollower();
};
