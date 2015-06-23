#pragma once

#include <math.h>
#include <stdlib.h>
#include "../globals.h"
#include "../shapes/Sphere.h"
#include "../collisionDetection.h"
#include "Bat.h"


namespace handbal {
	class Ball : public Sphere {
	public:
	    void update(float, vector<string>);
	    Ball();
	};
}
