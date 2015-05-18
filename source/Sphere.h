#include "Entity.h"
#include <math.h>
#include "globals.h"
#include <stdlib.h>

#include "Bat.h"

class Sphere : public Entity {
public:
    Vector* velocity;
    float   radius;

	Sphere(int numSlices, float radius);
	int generateGeometry(int numSlices, float radius);

    void printInfo();

	void update(float);
};
