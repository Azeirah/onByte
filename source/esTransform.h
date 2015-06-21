#pragma once

#ifndef ES_TRANSFORM_H
#define ES_TRANSFORM_H

#include "string.h"
#include "globals.h"

void esScale(ESMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz);
void esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
void esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void esFrustum(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
void esPerspective(ESMatrix *result, float fovy, float aspect, float nearZ, float farZ);
void esOrtho(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
void esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB);
void esMatrixLoadIdentity(ESMatrix *result);

#endif // ES_TRANSFORM_H
