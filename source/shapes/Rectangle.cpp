#include "Rectangle.h"

int Rectangle::generateGeometry(GLfloat width, GLfloat height, GLfloat depth) {
  int numVertices = 24;
  int numIndices  = 36;

  GLfloat cubeVerts[] = {
      -width, -height, -depth,  // A
      -width, -height, depth,  //
      width,  -height, depth,  width,  -height, -depth,
      -width, height,  -depth, -width, height,  depth,
      width,  height,  depth,  width,  height,  -depth,
      -width, -height, -depth, -width, height,  -depth,
      width,  height,  -depth, width,  -height, -depth,
      -width, -height, depth,  -width, height,  depth,
      width,  height,  depth,  width,  -height, depth,
      -width, -height, -depth, -width, -height, depth,
      -width, height,  depth,  -width, height,  -depth,
      width,  -height, -depth, width,  -height, depth,
      width,  height,  depth,  width,  height,  -depth,
  };


  // GLfloat cubeNormals[] = {
  //     0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
  //     0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
  //     1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
  //     0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
  //     1.0f, 0.0f,  0.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
  //     0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
  //     1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
  // };
  //
  // GLfloat cubeTex[] = {
  //     0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
  //     0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  //     0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
  //     1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  // };

  // Allocate memory for buffers
  this->vertices = new GLfloat[3 * numVertices];
  memcpy(this->vertices, cubeVerts, sizeof(cubeVerts));

  unsigned char cubeIndices[] = {
      0,  2,  1,  0,  3,  2,  4,  5,  6,  4,  6,  7,  8,  9,  10, 8,  10, 11,
      12, 15, 14, 12, 14, 13, 16, 17, 18, 16, 18, 19, 20, 23, 22, 20, 22, 21
  };

  this->indices = new GLuint[numIndices];

  memcpy(this->indices, cubeIndices, sizeof(cubeIndices));

  return numIndices;
}

Rectangle::Rectangle(float width, float height, float depth) {
  this->fill        = true;
  this->wireframe   = false;
  this->numIndices  = this->generateGeometry(width, height, depth);
}
