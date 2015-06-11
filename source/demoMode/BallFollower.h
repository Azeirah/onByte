#pragma once

#include "../shapes/Rectangle.h"

// another rectangle, "wooh!" for reuse
class BallFollower : public Rectangle {
public:
    GLfloat* positionToTrack;

    void update(float, vector<Json::Value*>);
    BallFollower(GLfloat *);
};
