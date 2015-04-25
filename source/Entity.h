#ifndef ENTITY_H
#define ENTITY_H

#include "onByte.h"
#include "Vector.h"
#include "ESContext.h"
#include <stdlib.h>
#include <stdarg.h>
#include "esTransform.h"

extern const char *defaultFragmentShader[6];
extern const char *defaultVertexShader[6];

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
    Vector* position;

    void loadShaders();

  public:
    void draw();
    void render(ESContext*);
    void update(float);
};

#endif // ENTITY_H
