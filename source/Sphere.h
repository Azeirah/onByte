#include "Entity.h"

class Sphere : public Entity {
public:
	Sphere(int numSlices, float radius);
	void generateGeometry(int numSlices, float radius);
};
