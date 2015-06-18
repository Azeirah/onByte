#include "globals.h"

// I wonder how
// I wonder why
// yesterday you told me about the mvpMatrix and all that I can see is just another error: ‘ESMatrix’ does not name a type
ESMatrix mvpMatrix;

float white[4]    = {1.0f  , 1.0f  , 1.0f  , 0.5f};
float red[4]      = {1.0f  , 0.38f , 0.333f, 0.5f};
float green[4]    = {0.333f, 1.0f  , 0.451f, 0.5f};
float blue[4]     = {0.549f, 0.408f, 1.0f  , 0.5f};
float yellow[4]   = {1.0f  , 0.886f, 0.333f, 0.5f};

int colorSize = sizeof(white);

GLfloat pointA[3] = {-fieldwidth,  fieldheight, -fielddepth};
GLfloat pointB[3] = {fieldwidth,   fieldheight, -fielddepth};
GLfloat pointC[3] = {fieldwidth,  -fieldheight, -fielddepth};
GLfloat pointD[3] = {-fieldwidth, -fieldheight, -fielddepth};
GLfloat pointE[3] = {-fieldwidth,  fieldheight, fielddepth};
GLfloat pointF[3] = {fieldwidth,   fieldheight, fielddepth};
GLfloat pointG[3] = {fieldwidth,  -fieldheight, fielddepth};
GLfloat pointH[3] = {-fieldwidth, -fieldheight, fielddepth};