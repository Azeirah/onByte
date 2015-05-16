#pragma once

#include "Entity.h"
#include <math.h>
#include "globals.h"
#include <stdlib.h>

class BallFollower : public Entity {
private:
    GLfloat* positionToTrack;

public:
    BallFollower(GLfloat scale, GLfloat* positionToTrack);
    int generateGeometry(GLfloat scale);
    void update(float);
};
