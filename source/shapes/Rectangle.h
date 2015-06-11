#pragma once

#include <stdlib.h>
#include <math.h>
#include "../Entity.h"
#include "../globals.h"
#include "../onByte.h"

class Rectangle : public Entity {
public:
    Rectangle(GLfloat width, GLfloat height, GLfloat depth);
    int generateGeometry(float width, float height, float depth);
};
