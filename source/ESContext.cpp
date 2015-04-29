#include "ESContext.h"

void ESContext::makeCurrent() {
    eglMakeCurrent(this->eglDisplay, this->eglSurface, this->eglSurface, this->eglContext);
}

void ESContext::swapBuffer() {
	eglSwapBuffers(this->eglDisplay, this->eglSurface);
}

EGLBoolean ESContext::createEGLContext (EGLint attribList[]) {
   EGLint     numConfigs;
   EGLint     majorVersion;
   EGLint     minorVersion;
   EGLDisplay display;
   EGLContext context;
   EGLSurface surface;
   EGLConfig  config;
   EGLint     contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Get Display
   display = eglGetDisplay((EGLNativeDisplayType) this->x_display);
   assertS(display != EGL_NO_DISPLAY, "Creating display failed ESContext.cpp:22");
   if (display == EGL_NO_DISPLAY) {
       return EGL_FALSE;
   }

   // Initialize EGL
   GLint eglInitialized = eglInitialize(display, &majorVersion, &minorVersion);
   assertS(eglInitialized, "Initializing egl failed ESContext.cpp:29");
   if (!eglInitialized) {
   	   cout << "EGL fail code was " << eglInitialized << endl;
       return EGL_FALSE;
   }

   // Get configs
   GLint configsGotten = eglGetConfigs(display, NULL, 0, &numConfigs);
   assertS(configsGotten, "Failed at getting configs ESContext.cpp:36");
   if (!configsGotten) {
       return EGL_FALSE;
   }

   // Choose config
   GLint configChosen = eglChooseConfig(display, attribList, &config, 1, &numConfigs);
   assertS(configChosen, "Failed at choosing config ESContext.cpp:43");
   if (!configChosen) {
       return EGL_FALSE;
   }

   // Create a surface
   surface = eglCreateWindowSurface(display, config, this->hWnd, NULL);
   assertS(surface != EGL_NO_SURFACE, "Failed at creating window surface ESContext.cpp:50");
   if (surface == EGL_NO_SURFACE) {
       return EGL_FALSE;
   }

   // Create a GL context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
   assertS(context != EGL_NO_CONTEXT, "Failed at creating creating context ESContext.cpp:57");
   if (context == EGL_NO_CONTEXT) {
       return EGL_FALSE;
   }

   // Make the context current
   GLint madeCurrent = eglMakeCurrent(display, surface, surface, context);
   assertS(madeCurrent, "Failed at making the context current ESContext.cpp:64");
   if (!madeCurrent) {
       return EGL_FALSE;
   }

   this->eglDisplay = display;
   this->eglSurface = surface;
   this->eglContext = context;

   return EGL_TRUE;
}

EGLBoolean ESContext::userInterrupt() {
	XEvent xev;
    KeySym key;
    GLboolean userinterrupt = GL_FALSE;
    char text;

    // Pump all messages from X server. Keypresses are directed to keyfunc (if defined)
    while (XPending(this->x_display)) {
        XNextEvent(this->x_display, &xev);

        if (xev.type == KeyPress) {
            if (XLookupString(&xev.xkey, &text, 1, &key, 0) == 1) {
            	// TODO: keyfunc callback
                // if (this->keyFunc != NULL) {
                //     this->keyFunc(this, text, 0, 0);
                // }
            }
        } else if (xev.type == DestroyNotify) {
            userinterrupt = GL_TRUE;
        } else if (xev.type == ConfigureNotify) {
            XConfigureEvent xce = xev.xconfigure;

            // This event type is generated for a variety of happenings, so check whether the window has been resized.
            if (xce.width != this->window_width || xce.height != this->window_height) {
                this->window_width = xce.width;
                this->window_height = xce.height;
            }
        }
    }

    return userinterrupt;
}

EGLBoolean ESContext::winCreate(string title) {
    Window               root;
    XSetWindowAttributes swa;
    XSetWindowAttributes xattr;
    Atom                 wm_state;
    Atom                 x11_fs_atom;
    XWMHints             hints;
    XEvent               xev;
    EGLConfig            ecfg;
    EGLint               num_config;
    Window               win;

    /*
     * X11 native display initialization
     */

    this->x_display = XOpenDisplay(NULL);
    if (this->x_display == NULL) {
        return EGL_FALSE;
    }

    root = DefaultRootWindow(this->x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask | StructureNotifyMask;
    win = XCreateWindow(
               this->x_display, root,
               0, 0, this->window_width, this->window_height, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa);

    xattr.override_redirect = false;
    XChangeWindowAttributes (this->x_display, win, CWOverrideRedirect, &xattr);

    hints.input = true;
    hints.flags = InputHint;
    XSetWMHints(this->x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow(this->x_display, win);
    XStoreName(this->x_display, win, title.c_str());

    // get identifiers for the provided atom name strings
    wm_state    = XInternAtom (this->x_display, "_NET_WM_STATE", false);
    x11_fs_atom = XInternAtom( this->x_display, "_NET_WM_STATE_FULLSCREEN", false);

    // dit zou eigenlijk ook een classe moeten zijn lijkt me...
    memset(&xev, 0, sizeof(xev));
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = (FULLSCREEN) ? x11_fs_atom : false;
    XSendEvent(
       this->x_display,
       DefaultRootWindow (this->x_display),
       false,
       SubstructureNotifyMask,
       &xev);

    this->hWnd = (EGLNativeWindowType) win;
    return EGL_TRUE;
}

ESContext::ESContext (GLboolean isPlayerOne) {
    this->isPlayerOne = isPlayerOne;

    // hoeft volgens mij voor de rest niets te doen
    // de originele esContextInit functie maakt alleen ruimte vrij
    // voor de context
    // dat doet cpp automatisch.
}

void ESContext::createWindow(string title, GLint width, GLint height, GLuint flags) {
    EGLint attributeList[] = {
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     6,
        EGL_BLUE_SIZE,      5,
        EGL_ALPHA_SIZE,     (flags & ES_WINDOW_ALPHA)       ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (flags & ES_WINDOW_DEPTH)       ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (flags & ES_WINDOW_STENCIL)     ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    // ...
    assert(this != NULL);

    this->window_width  = width;
    this->window_height = height;

    assert(this->winCreate(title));
    assertS(this->createEGLContext(attributeList), "creating window failed..");
}
