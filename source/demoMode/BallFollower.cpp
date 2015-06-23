#include "BallFollower.h"

namespace demo {
    void BallFollower::update(float dt, vector<string> input) {
        this->position->z = this->findEntity("ball", "ball")->position->z;
    }

    BallFollower::BallFollower() : Rectangle(fieldwidth, fieldheight, 0.002f) {
        this->fill      = false;
        this->wireframe = true;

        memcpy(this->color, blue, sizeof(blue));
    }
}
