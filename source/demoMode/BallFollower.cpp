#include "BallFollower.h"

void BallFollower::update(float dt, vector<char *> input) {
    this->position->z = *this->positionToTrack;
}

BallFollower::BallFollower(GLfloat* positionToTrack) : Rectangle(fieldwidth, fieldheight, 0.002f) {
    this->fill            = false;
    this->wireframe       = true;

    this->positionToTrack = positionToTrack;

    memcpy(this->color, blue, sizeof(blue));
}
