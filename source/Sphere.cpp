#include "Sphere.h"

Vector* bounceX = new Vector(-1,  1,  1);
Vector* bounceY = new Vector( 1, -1,  1);
Vector* bounceZ = new Vector( 1,  1, -1);

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

void Sphere::update(float dt) {
    // static float totalTime = 0;
    // totalTime += dt;
    // this->position->z = sin(totalTime);

    this->position->add(this->velocity);

    if (this->position->x > fieldwidth - this->radius || this->position->x < -fieldwidth + this->radius) {
        this->velocity->multiply(bounceX);
    }

    if (this->position->y > fieldheight - this->radius || this->position->y < -fieldheight + this->radius) {
        this->velocity->multiply(bounceY);
    }

    Bat *bat1 = (Bat *) this->findEntity("bat1", "bat");
    Bat *bat2 = (Bat *) this->findEntity("bat2", "bat");

    // Bat or nearfielddetection
    if (this->position->z > fielddepth                    &&
        this->position->x > bat2->position->x - batwidth  &&
        this->position->x < bat2->position->x + batwidth  &&
        this->position->y > bat2->position->y - batheight &&
        this->position->y < bat2->position->y + batheight
    ) {
      this->velocity->multiply(bounceZ);
    } else if (this->position->z < -fielddepth                   &&
               this->position->x > bat1->position->x - batwidth  &&
               this->position->x < bat1->position->x + batwidth  &&
               this->position->y > bat1->position->y - batheight &&
               this->position->y < bat1->position->y + batheight
    ) {
      this->velocity->multiply(bounceZ);
    } else if (this->position->z > fielddepth || this->position->z < -fielddepth) {
      this->velocity->multiply(bounceZ);
      this->position->x = 0;
      this->position->y = 0;
      this->position->z = 0;

      this->velocity->x = generateFloat(0, 0.01f);
      this->velocity->y = generateFloat(0, 0.01f);
    }
}

void Sphere::printInfo() {
    Entity::printInfo();
    cout << "velocity" << endl;
    this->velocity->printInfo();
}

Sphere::Sphere(int numSlices, float radius) {
  cout << "creating sphere object, it has " << numSlices << " slices and a radius of " << radius << endl;

  this->radius      = radius;

  this->fill        = true;
  this->wireframe   = true;
  this->numIndices  = this->generateGeometry(numSlices, radius);
  this->angle       = 90.0f;

  this->name        = "ball";
  this->type        = "ball";

  this->velocity    = new Vector(generateFloat(0, 0.01f), generateFloat(0, 0.01f), -0.01f);

  this->position->x = 0;
  this->position->y = 0;
  this->position->z = 0;

  memcpy(this->color, yellow, sizeof(yellow));
}
