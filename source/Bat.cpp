#include "Bat.h"

#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

int Bat::generateGeometry(float scale) {
  int i;
  int numVertices = 24;
  int numIndices  = 36;

  GLfloat cubeVerts[] = {
      -batwidth, -batheight, -batdepth,  // A
      -batwidth, -batheight, batdepth,  //
      batwidth,  -batheight, batdepth,  batwidth,  -batheight, -batdepth,
      -batwidth, batheight,  -batdepth, -batwidth, batheight,  batdepth,
      batwidth,  batheight,  batdepth,  batwidth,  batheight,  -batdepth,
      -batwidth, -batheight, -batdepth, -batwidth, batheight,  -batdepth,
      batwidth,  batheight,  -batdepth, batwidth,  -batheight, -batdepth,
      -batwidth, -batheight, batdepth,  -batwidth, batheight,  batdepth,
      batwidth,  batheight,  batdepth,  batwidth,  -batheight, batdepth,
      -batwidth, -batheight, -batdepth, -batwidth, -batheight, batdepth,
      -batwidth, batheight,  batdepth,  -batwidth, batheight,  -batdepth,
      batwidth,  -batheight, -batdepth, batwidth,  -batheight, batdepth,
      batwidth,  batheight,  batdepth,  batwidth,  batheight,  -batdepth,
  };

  GLfloat cubeNormals[] = {
      0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
      0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
      1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
      0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
      1.0f, 0.0f,  0.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
      0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
      1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
  };

  GLfloat cubeTex[] = {
      0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  };

  // Allocate memory for buffers
  this->vertices = new GLfloat[3 * numVertices];
  memcpy(this->vertices, cubeVerts, sizeof(cubeVerts));

  for (i = 0; i < numVertices * 3; i++) {
    this->vertices[i] *= scale;
  }

  unsigned char cubeIndices[] = {
      0,  2,  1,  0,  3,  2,  4,  5,  6,  4,  6,  7,  8,  9,  10, 8,  10, 11,
      12, 15, 14, 12, 14, 13, 16, 17, 18, 16, 18, 19, 20, 23, 22, 20, 22, 21
  };

  this->indices = new GLuint[numIndices];

  memcpy(this->indices, cubeIndices, sizeof(cubeIndices));

  return numIndices;
}

void Bat::update(float dt) {
    static float totaltime = 0;
    totaltime += dt;
    this->position->y = sin(totaltime) * fieldheight;
    this->angle += 0.1;
}

Bat::Bat(float scale, GLfloat position, float color[4], int batNumber) {
  this->fill        = true;
  this->wireframe   = false;
  this->numIndices  = this->generateGeometry(scale);

  this->name        = "bat" + SSTR(batNumber);
  this->type        = "bat";

  this->position->x = 0;
  this->position->y = 0;
  this->position->z = position;

  cout << "creating a bat with a transparency of " << color[3] << endl;

  memcpy(this->color, color, sizeof(color));
}
