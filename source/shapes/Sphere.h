#pragma once

#include <math.h>
#include <stdlib.h>
#include "../Entity.h"
#include "../onByte.h"

class Sphere : public Entity {
public:
    Vector* velocity;
    float   radius;

    Sphere(int numSlices, float radius);
    int generateGeometry(int numSlices, float radius);

    void printInfo();
};
