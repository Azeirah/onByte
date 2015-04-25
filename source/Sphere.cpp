#include "Sphere.h"

int Sphere::generateGeometry(int numSlices, float radius) {
  int i;
  int j;
  int numParallels = numSlices / 2;
  int numVertices  = (numParallels + 1) * (numSlices + 1);
  int numIndices   = numParallels * numSlices * 6;
  float angleStep  = TAU / (float) numSlices;

  // lekker op zijn c's

  this->vertices = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);
  this->indices  = (GLuint *)  malloc(sizeof(GLuint ) *     numIndices);

  for (i = 0; i < numParallels + 1; i += 1) {
    for (j = 0; j < numSlices + 1; j += 1) {
      int vertex = (i * (numSlices + 1) + j) * 3;
      if (vertices) {
        this->vertices[vertex + 0] = radius * sinf (angleStep * (float) i) *
                                              sinf (angleStep * (float) j);

        this->vertices[vertex + 1] = radius * cosf (angleStep * (float) i);

        this->vertices[vertex + 2] = radius * sinf (angleStep * (float) i) *
                                              cosf (angleStep * (float) j);
      }
    }
  }

  // this doesn't even make a copy of the indices, why copy the pointer? ;/
  GLuint *indexBuffer = this->indices;

  for (i = 0; i < numParallels; i += 1) {
    for (j = 0; j < numSlices; j += 1) {
      indexBuffer[0] = i * (numSlices + 1) + j;
      indexBuffer[1] = (i + 1) * (numSlices + 1) + j;
      indexBuffer[2] = (i + 1) * (numSlices + 1) + (j + 1);

      indexBuffer[3] = i * (numSlices + 1 + j);
      indexBuffer[4] = (i + 1) * (numSlices + 1) + (j + 1);
      indexBuffer[5] = i * (numSlices + 1 + j + 1);
    }
  }

  return numIndices;
}

void Sphere::update(float dt) {
  cout << "drawing sphere" << endl;
}

Sphere::Sphere(int numSlices, float radius) {
  cout << "creating sphere object" << endl;

  this->loadShaders();

  this->numIndices    = this->generateGeometry(10, radius);
  this->angle         = 90.0f;

  this->position->x = 0;
  this->position->y = 0;
  this->position->z = 0;

  memcpy(this->color, yellow, sizeof(yellow));
}
