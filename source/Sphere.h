#include "Entity.h"
#include <math.h>
#include "globals.h"
#include <stdlib.h>

class Sphere : public Entity {
public:
	Sphere(int numSlices, float radius);
	int generateGeometry(int numSlices, float radius);
	void update(float);
};
