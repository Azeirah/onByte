#include "ESContext.h"

EGLBoolean ESContext::winCreate(string title) {
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    Atom  x11_fs_atom;
    XWMHints hints;
    XEvent xev;
    EGLConfig ecfg;
    EGLint num_config;
    Window win;

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
    x11_fs_atom = XInternAtom( this->x_display, "_NET_WM_STATE_FULLSCREEN", False );

    // dit zou eigenlijk ook een classe moeten zijn lijkt me...
    memset(&xev, 0, sizeof(xev));
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = (FULLSCREEN) ? x11_fs_atom : false;
    XSendEvent (
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
        EGL_ALPHA_SIZE,     (flags & ES_WINDOW_ALPHA) ?       8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (flags & ES_WINDOW_DEPTH) ?       8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (flags & ES_WINDOW_STENCIL) ?     8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    // ...
    assert(this != NULL);

    this->window_width  = width;
    this->window_height = height;

    cout << "CREATING WINDOW";

    assert(this->winCreate(title));
}