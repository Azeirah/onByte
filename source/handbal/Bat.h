#pragma once

#include <math.h>
#include <stdlib.h>
#include "../shapes/Rectangle.h"
#include "../onByte.h"
#include "../Text.h"

namespace handbal {
	class Bat : public Rectangle {
	public:
	    Bat(GLfloat position, float color[4], int batNumber);

	    void update(float, vector<string>);
	    // void render();
	};
}

