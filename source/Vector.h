#pragma once

#include "onByte.h"

class Vector {
  public:
    GLfloat x;
    GLfloat y;
    GLfloat z;

    void      add(Vector* v2);
    void multiply(Vector* v2);
    void    scale(float scale);

    void printInfo();

    Vector(float x=0.0f, float y=0.0f, float z=0.0f);
};
