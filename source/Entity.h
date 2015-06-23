#ifndef ENTITY_H
#define ENTITY_H

#include "onByte.h"
#include "Vector.h"
#include "ESContext.h"
#include <stdlib.h>
#include <stdarg.h>
#include "esUtil.h"
#include "GameState.h"

extern const char *defaultFragmentShader[6];
extern const char *defaultVertexShader[6];

class GameState;

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

    bool wireframe;
    bool fill;

    // Both name and type are used to retrieve an entity from within another entity
    // Name is to collect a single unique object (such as score)
    // type is to collect all objects in a group, for example, ball needs to do hit-detection on all bats.

    vector<Entity *> *entityCollection;
  public:
    string name;
    string type;
    Vector* position;

    GameState *gameState;

    void         printInfo();

    void         loadShaders();
    string       getName();
    string       getType();
    void         setCollection(vector<Entity *> *entityCollection);
    Entity      *findEntity(string name, string type);

    virtual void render();
    virtual void update(float dt, vector<string> input);

    Entity();
};

#endif // ENTITY_H
