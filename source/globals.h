#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

// Why would you include something in a globals file? I don't know either D:
// anyhow, this includes the definition of GLfloat for ESMatrix
#include "onByte.h"

// resolutie
#define SCREENWIDTH  800
#define SCREENHEIGHT 600

// titels van x-windows
#define SCREENNAME1  "speler 1"
#define SCREENNAME2  "speler 2"

// deze weet ik niet meer hoor...
#define FULLSCREEN   false

// math
#define PI           3.1415926535897932384626433832795f
#define TAU          (2 * PI)

// bat sizes
#define batwidth 0.267f
#define batheight 0.2f
#define batdepth 0.02f

// size of filed
#define fieldwidth   0.9f
#define fieldheight  0.9f
#define fielddepth   3.0f

// colors
extern float white[4];
extern float red[4];
extern float green[4];
extern float blue[4];
extern float yellow[4];

typedef struct {
    GLfloat m[4][4];
} ESMatrix;

extern ESMatrix mvpMatrix;

// all 8 outer points of the gamefield.
extern GLfloat pointA[3];
extern GLfloat pointB[3];
extern GLfloat pointC[3];
extern GLfloat pointD[3];

extern GLfloat pointE[3];
extern GLfloat pointF[3];
extern GLfloat pointG[3];
extern GLfloat pointH[3];

#endif // GLOBALS_H
