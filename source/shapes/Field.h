// A "Field" is a terrible shape, something like a general purpose "cube" would be a lot better. This is not the case however ;(

#pragma once

#include <math.h>
#include <stdlib.h>
#include "../Entity.h"
#include "../onByte.h"

class Field : public Entity {
public:
    Field(float scale);

    int generateGeometry(float scale);
};
