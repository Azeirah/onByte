#include "Field.h"

#define fieldwidth  0.9f
#define fieldheight 0.9f
#define fielddepth  3.0f

int Field::generateGeometry(float scale) {
    int i;
    int numVertices = 8;
    int numIndices = 24;

    GLfloat cubeVerts[] = {
        pointA[0], pointA[1], pointA[2],
        pointB[0], pointB[1], pointB[2],
        pointC[0], pointC[1], pointC[2],
        pointD[0], pointD[1], pointD[2],
        pointE[0], pointE[1], pointE[2],
        pointF[0], pointF[1], pointF[2],
        pointG[0], pointG[1], pointG[2],
        pointH[0], pointH[1], pointH[2],
    };

    GLfloat cubeNormals[] = {
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    GLfloat cubeTex[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };

    this->vertices = new GLfloat[numVertices * 3];
    memcpy(this->vertices, cubeVerts, sizeof(cubeVerts));
    for (i = 0; i < numVertices * 3; i++) {
        this->vertices[i] *= scale;
    }

    unsigned char cubeIndices[] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        3, 7
    };

    this->indices = new GLuint[numIndices * 2];
    memcpy(this->indices, cubeIndices, sizeof(cubeIndices));

    return numIndices;
}

Field::Field (float scale) {
	cout << "creating field object, with scale " << scale << endl;

    this->numIndices  = this->generateGeometry(scale);
    this->angle       = 90.0f;
    this->position->x = 0;
    this->position->y = 0;
    this->position->z = 0;
    this->wireframe   = true;
    this->fill        = false;

    memcpy(this->color, white, sizeof(white));
}
