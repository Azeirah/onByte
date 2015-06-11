#pragma once

#include <math.h>
#include <stdlib.h>
#include "../shapes/Rectangle.h"
#include "../globals.h"
#include "../onByte.h"
#include "../Text.h"

class Bat : public Rectangle {
public:
    Bat(GLfloat position, float color[4], int batNumber);

    void update(float, vector<Json::Value*>);
};
