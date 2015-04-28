#include "Entity.h"
#include <math.h>
#include "globals.h"
#include <stdlib.h>

class Field : public Entity {
public:
	Field(float scale);

	int generateGeometry(float scale);
};
