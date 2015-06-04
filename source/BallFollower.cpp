#include "BallFollower.h"

int BallFollower::generateGeometry(float scale) {
  int i;
  int numVertices = 24;
  int numIndices = 8;

  GLfloat cubeVerts[] = {
      pointA[0],
      pointA[1],
      0,
      pointB[0],
      pointB[1],
      0,
      pointC[0],
      pointC[1],
      0,
      pointD[0],
      pointD[1],
      0,
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

  this->vertices = new GLfloat[3 * numVertices];
  memcpy(this->vertices, cubeVerts, sizeof(cubeVerts));

  for (i = 0; i < numVertices * 3; i++) {
    this->vertices[i] *= scale;
  }

  unsigned char cubeIndices[] = {
      0, 1, 1, 2, 2, 3, 3, 0,
  };

  this->indices = new GLuint[numIndices];
  memcpy(this->indices, cubeIndices, sizeof(cubeIndices));

  return numIndices;
}

void BallFollower::update(float dt) {
    this->position->z = *this->positionToTrack;
}

BallFollower::BallFollower(GLfloat scale, GLfloat* positionToTrack) {
    this->fill            = false;
    this->wireframe       = true;
    this->numIndices      = this->generateGeometry(scale);

    this->name            = "ballfollower";
    this->type            = "ballfollower";

    this->position->x     = 0;
    this->position->y     = 0;
    this->position->z     = *positionToTrack;

    this->positionToTrack = positionToTrack;

    memcpy(this->color, blue, sizeof(blue));

}
