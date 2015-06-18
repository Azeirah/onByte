#pragma once

#include "onByte.h"

class Vector {
  public:
    GLfloat x;
    GLfloat y;
    GLfloat z;

    Vector*      add(Vector* v2);
    Vector* multiply(Vector* v2);
    Vector*    scale(float scale);
    Vector*    clone(Vector* v);

    void printInfo();

    Vector(float x=0.0f, float y=0.0f, float z=0.0f);
};
