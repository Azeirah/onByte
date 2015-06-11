#pragma once

#include <math.h>
#include <stdlib.h>
#include "../globals.h"
#include "../shapes/Sphere.h"

#include "Bat.h"

class Ball : public Sphere {
public:
    void update(float, vector<Json::Value*>);
    Ball();
};
