#pragma once

#include "onByte.h"
#include "Vector.h"
#include "ESContext.h"

class Entity {
  protected:
    // handle to a program object
    GLuint programObject;

    // locations for shader variables
    // attributes
    GLint positionLoc;

    // uniforms
    GLint mvpLoc;
    GLint colorLoc;

    // vertices and indices data
    GLfloat *vertices;
    GLuint *indices;
    int numIndices;

    // rotation, position and color
    GLfloat angle;
    GLfloat color[4];
    Vector* origin;

  public:
    void draw();
    void render(ESContext*);
    void update(float);
};
