#include "Entity.h"
#include <math.h>
#include "globals.h"
#include <stdlib.h>
#include "onByte.h"

class Bat : public Entity {
public:
    Bat(float scale, GLfloat position, float color[4], int batNumber);
    int generateGeometry(float scale);
    void update(float);
};
