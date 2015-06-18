#include "Sphere.h"

int Sphere::generateGeometry(int numSlices, float radius) {
    int i;
    int j;
    int numParallels = numSlices / 2;
    int numVertices = ( numParallels + 1 ) * ( numSlices + 1 );
    int numIndices = numParallels * numSlices * 6;
    float angleStep = TAU / ((float) numSlices);


    this->vertices = new GLfloat[3 * numVertices];
    this->indices  = new GLuint[numIndices];

    for (i = 0; i < numParallels + 1; i++) {
        for (j = 0; j < numSlices + 1; j++) {
            int vertex = (i * (numSlices + 1) + j) * 3;

            this->vertices[vertex + 0] =
              radius * sinf(angleStep * (float)i) * sinf(angleStep * (float)j);
            this->vertices[vertex + 1] = radius * cosf(angleStep * (float)i);
            this->vertices[vertex + 2] =
              radius * sinf(angleStep * (float)i) * cosf(angleStep * (float)j);

        }
    }

    unsigned char *indexBuffer = (unsigned char *) this->indices;
    for (i = 0; i < numParallels; i += 1) {
        for (j = 0; j < numSlices; j += 1) {
            *indexBuffer++ = i * (numSlices + 1) + j;
            *indexBuffer++ = (i + 1) * (numSlices + 1) + j;
            *indexBuffer++ = (i + 1) * (numSlices + 1) + (j + 1);

            *indexBuffer++ = i * (numSlices + 1) + j;
            *indexBuffer++ = (i + 1) * (numSlices + 1) + (j + 1);
            *indexBuffer++ = i * (numSlices + 1) + (j + 1);
        }
    }

  return numIndices;
}

void Sphere::printInfo() {
    Entity::printInfo();
    cout << "velocity" << endl;
    this->velocity->printInfo();
}

Sphere::Sphere(int numSlices, float radius) {
  this->radius      = radius;

  this->fill        = true;
  this->wireframe   = true;
  this->numIndices  = this->generateGeometry(numSlices, radius);
  this->angle       = 90.0f;

  this->position->x = 0;
  this->position->y = 0;
  this->position->z = 0;

  memcpy(this->color, yellow, sizeof(yellow));
}
