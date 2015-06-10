#pragma once

#include "esTransform.h"
#include "onByte.h"

GLuint esLoadShader(GLenum type, const char *shaderSrc);
GLuint esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc);
void   esLogMessage(const char *formatStr, ...);

extern const char *defaultFragmentShader[6];
extern const char *defaultVertexShader[6];
