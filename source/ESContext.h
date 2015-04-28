#pragma once

#include "onByte.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>

// RGB color buffer
#define ES_WINDOW_RGB 0
// ALPHA color buffer
#define ES_WINDOW_ALPHA 1
// depth buffer
#define ES_WINDOW_DEPTH 2
// stencil buffer
#define ES_WINDOW_STENCIL 4
// multi-sample buffer
#define ES_WINDOW_MULTISAMPLE 8

class ESContext {
  private:
    EGLNativeWindowType hWnd;
    EGLSurface          eglSurface;
    // ??
    // GameObject ;

    EGLBoolean createEGLContext(EGLint[15]);
  public:
    Display*            x_display;
    EGLDisplay          eglDisplay;
    EGLContext          eglContext;
    GLboolean           isPlayerOne;
    GLint               window_width;
    GLint               window_height;

    ESContext(GLboolean);
    void createWindow(string, GLint, GLint, GLuint);
    EGLBoolean winCreate(string);
    EGLBoolean userInterrupt();
    void makeCurrent();
    void swapBuffer();
};
