#include "Sphere.h"
#include "globals.h"

void Sphere::generateGeometry(int numSlices, float radius) {
  int i;
  int j;
  int numParallels = numSlices / 2;
  int numVertices = (numParallels + 1) * (numSlices + 1);
  int numIndices = numParallels * numSlices * 6;
  float angleStep = (2.0f * PI) / ((float)numSlices);

  for (i = 0; i < numParallels + 1; i++) {
    for (j = 0; j < numSlices + 1; j++) {
      int vertex = (i * (numSlices + 1) + j) * 3;

      if (this->vertices) {
        this->vertices[vertex + 0] =
            radius * sinf(angleStep * (float)i) * sinf(angleStep * (float)j);
        this->vertices[vertex + 1] = radius * cosf(angleStep * (float)i);
        this->vertices[vertex + 2] =
            radius * sinf(angleStep * (float)i) * cosf(angleStep * (float)j);
      }
    }
  }

  // Generate the indices
  if (indices != NULL) {
    //      GLuint *indexBuf = (*indices);
    unsigned char indexBuf* = indices;
    for (i = 0; i < numParallels; i++) {
      for (j = 0; j < numSlices; j++) {
        *indexBuf++ = i * (numSlices + 1) + j;
        *indexBuf++ = (i + 1) * (numSlices + 1) + j;
        *indexBuf++ = (i + 1) * (numSlices + 1) + (j + 1);

        *indexBuf++ = i * (numSlices + 1) + j;
        *indexBuf++ = (i + 1) * (numSlices + 1) + (j + 1);
        *indexBuf++ = i * (numSlices + 1) + (j + 1);
      }
    }
  }

  return numIndices;
}

Sphere::Sphere(int numSlices, float radius) {
  this->generateGeometry(numSlices, radius);
}
