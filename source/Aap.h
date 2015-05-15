#pragma once

#ifndef AAP_H
#define AAP_H

#include "Entity.h"
#include <math.h>
#include "globals.h"
#include <stdlib.h>

class Aap : public Entity {
public:
    Aap();
    void loadGeometry();
    void update(float);
    void render();
};

extern unsigned int aapNumVerts;
extern float aapVerts [];
extern float aapNormals [];

#endif // AAP_H
