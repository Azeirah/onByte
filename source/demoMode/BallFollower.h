#pragma once

#include "../shapes/Rectangle.h"

namespace demo {
    // another rectangle, "wooh!" for reuse
    class BallFollower : public Rectangle {
    public:
        void update(float, vector<string>);
        BallFollower();
    };
}
