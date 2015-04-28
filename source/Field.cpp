#include "Field.h"

#define fieldwidth  0.9f
#define fieldheight 0.9f
#define fielddepth  3.0f

GLfloat pointA[] = {-fieldwidth, fieldheight, -fielddepth};
GLfloat pointB[] = {fieldwidth, fieldheight, -fielddepth};
GLfloat pointC[] = {fieldwidth, -fieldheight, -fielddepth};
GLfloat pointD[] = {-fieldwidth, -fieldheight, -fielddepth};

GLfloat pointE[] = {-fieldwidth, fieldheight, fielddepth};
GLfloat pointF[] = {fieldwidth, fieldheight, fielddepth};
GLfloat pointG[] = {fieldwidth, -fieldheight, fielddepth};
GLfloat pointH[] = {-fieldwidth, -fieldheight, fielddepth};

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

	cout << "we get here" << endl;
    this->vertices = new GLfloat[numVertices * 3];
    memcpy(this->vertices, cubeVerts, sizeof(cubeVerts));
    for (i = 0; i < numVertices * 3; i++) {
        this->vertices[i] *= scale;
    }

    // if (normals != NULL) {
    //     *normals = malloc (sizeof(GLfloat) * 3 * numVertices);
    //     memcpy(*normals, cubeNormals, sizeof(cubeNormals));
    // }

    // if (texCoords != NULL) {
    //     *texCoords = malloc (sizeof(GLfloat) * 2 * numVertices);
    //     memcpy(*texCoords, cubeTex, sizeof(cubeTex)) ;
    // }

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

    this->loadShaders();

    this->numIndices    = this->generateGeometry(scale);
    this->angle         = 0.0f;

    cout << "number of indices " << this->numIndices << endl;

    for (int i = 0; i < 12; i++) {
    	cout << "indice: ";
    	for (int j = 0; j < 2; j++) {
    		cout << this->indices[i * 2 + j] << " ";
    	}
    	cout << endl;
    }

    this->position->x = 0;
    this->position->y = 0;
    this->position->z = 0;

    memcpy(this->color, yellow, sizeof(yellow));
}
