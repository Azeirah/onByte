#pragma once

#include <math.h>
#include <stdlib.h>
#include "../globals.h"
#include "../shapes/Sphere.h"
#include "../collisionDetection.h"
#include "Bat.h"

namespace demo {
    class Ball : public Sphere {
    public:
        void update(float, vector<char *>);
        Ball();
    };
}
