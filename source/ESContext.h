#include "onByte.h"

#include <GLES2/gl2.h>
#include <EGL/egl.h>
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
    GLboolean           isPlayerOne;
    GLint               window_width;
    GLint               window_height;
    EGLNativeWindowType hWnd;
    EGLDisplay          eglDisplay;
    EGLContext          eglContext;
    EGLSurface          eglSurface;
    Display*            x_display;
    // ??
    // GameObject ;


    EGLBoolean createEGLContext(EGLint[15]);
  public:
    ESContext(GLboolean);

    void createWindow(string, GLint, GLint, GLuint);

    EGLBoolean winCreate(string);
};