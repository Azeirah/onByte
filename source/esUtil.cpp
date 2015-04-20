// //
// // Book:      OpenGL(R) ES 2.0 Programming Guide
// // Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// // ISBN-10:   0321502795
// // ISBN-13:   9780321502797
// // Publisher: Addison-Wesley Professional
// // URLs:      http://safari.informit.com/9780321563835
// //            http://www.opengles-book.com
// //

// // ESUtil.c
// //
// //    A utility library for OpenGL ES.  This library provides a
// //    basic common framework for the example applications in the
// //    OpenGL ES 2.0 Programming Guide.
// //

// ///
// //  Includes
// //
// //
// #include "onByte.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdarg.h>
// #include <sys/time.h>
// #include <GLES2/gl2.h>
// #include <EGL/egl.h>
// #include "esUtil.h"

// #include  <X11/Xlib.h>
// #include  <X11/Xatom.h>
// #include  <X11/Xutil.h>

// // X11 related local variables
// //static Display *x_display = NULL;

// #define FULLSCREEN FALSE
// #define ANA3D FALSE


// ///
// // CreateEGLContext()
// //
// //    Creates an EGL rendering context and all associated elements
// //
// EGLBoolean CreateEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
//                               EGLContext* eglContext, EGLSurface* eglSurface,
//                               EGLint attribList[], ESContext *esContext)
// {
//    EGLint numConfigs;
//    EGLint majorVersion;
//    EGLint minorVersion;
//    EGLDisplay display;
//    EGLContext context;
//    EGLSurface surface;
//    EGLConfig config;
//    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

//    // Get Display
//    display = eglGetDisplay((EGLNativeDisplayType)esContext->x_display);
//    if ( display == EGL_NO_DISPLAY )
//    {
//       return EGL_FALSE;
//    }

//    // Initialize EGL
//    if ( !eglInitialize(display, &majorVersion, &minorVersion) )
//    {
//       return EGL_FALSE;
//    }

//    // Get configs
//    if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
//    {
//       return EGL_FALSE;
//    }

//    // Choose config
//    if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
//    {
//       return EGL_FALSE;
//    }

//    // Create a surface
//    surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
//    if ( surface == EGL_NO_SURFACE )
//    {
//       return EGL_FALSE;
//    }

//    // Create a GL context
//    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
//    if ( context == EGL_NO_CONTEXT )
//    {
//       return EGL_FALSE;
//    }

//    // Make the context current
//    if ( !eglMakeCurrent(display, surface, surface, context) )
//    {
//       return EGL_FALSE;
//    }

//    *eglDisplay = display;
//    *eglSurface = surface;
//    *eglContext = context;
//    return EGL_TRUE;
// }


// ///
// //  WinCreate()
// //
// //      This function initialized the native X11 display and window for EGL
// //
// EGLBoolean WinCreate(ESContext *esContext, const char *title)
// {
//     Window root;
//     XSetWindowAttributes swa;
//     XSetWindowAttributes  xattr;
//     Atom wm_state;
//     Atom  x11_fs_atom;
//     XWMHints hints;
//     XEvent xev;
//     EGLConfig ecfg;
//     EGLint num_config;
//     Window win;

//     /*
//      * X11 native display initialization
//      */

//     esContext->x_display = XOpenDisplay(NULL);
//     if ( esContext->x_display == NULL )
//     {
//         return EGL_FALSE;
//     }

//     root = DefaultRootWindow(esContext->x_display);

//     swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask | StructureNotifyMask;
//     win = XCreateWindow(
//                esContext->x_display, root,
//                0, 0, esContext->width, esContext->height, 0,
//                CopyFromParent, InputOutput,
//                CopyFromParent, CWEventMask,
//                &swa );

//     xattr.override_redirect = FALSE;
//     XChangeWindowAttributes ( esContext->x_display, win, CWOverrideRedirect, &xattr );

//     hints.input = TRUE;
//     hints.flags = InputHint;
//     XSetWMHints(esContext->x_display, win, &hints);

//     // make the window visible on the screen
//     XMapWindow (esContext->x_display, win);
//     XStoreName (esContext->x_display, win, title);

//     // get identifiers for the provided atom name strings
//     wm_state = XInternAtom (esContext->x_display, "_NET_WM_STATE", FALSE);
//     x11_fs_atom   = XInternAtom( esContext->x_display, "_NET_WM_STATE_FULLSCREEN", False );

//     memset ( &xev, 0, sizeof(xev) );
//     xev.type                 = ClientMessage;
//     xev.xclient.window       = win;
//     xev.xclient.message_type = wm_state;
//     xev.xclient.format       = 32;
//     xev.xclient.data.l[0]    = 1;
//     xev.xclient.data.l[1]    = (FULLSCREEN) ? x11_fs_atom : FALSE;
//     XSendEvent (
//        esContext->x_display,
//        DefaultRootWindow ( esContext->x_display ),
//        FALSE,
//        SubstructureNotifyMask,
//        &xev );

//     esContext->hWnd = (EGLNativeWindowType) win;
//     return EGL_TRUE;
// }


// ///
// //  userInterrupt()
// //
// //      Reads from X11 event loop and interrupt program if there is a keypress, or
// //      window close action.
// //
// GLboolean userInterrupt(ESContext *esContext)
// {
//     XEvent xev;
//     KeySym key;
//     GLboolean userinterrupt = GL_FALSE;
//     char text;

//     // Pump all messages from X server. Keypresses are directed to keyfunc (if defined)
//     while ( XPending ( esContext->x_display) )
//     {
//         XNextEvent( esContext->x_display, &xev );
//         if ( xev.type == KeyPress )
//         {
//             if (XLookupString(&xev.xkey,&text,1,&key,0)==1)
//             {
//                 if (esContext->keyFunc != NULL)
//                     esContext->keyFunc(esContext, text, 0, 0);
//             }
//         }
//         if ( xev.type == DestroyNotify )
//             userinterrupt = GL_TRUE;

//         if (xev.type == ConfigureNotify) {
//             XConfigureEvent xce = xev.xconfigure;

//             /* This event type is generated for a variety of
//                happenings, so check whether the window has been
//                resized. */

//             if (xce.width != esContext->width ||
//                 xce.height != esContext->height) {
//                 esContext->width = xce.width;
//                 esContext->height = xce.height;
//             }
//         }
//     }
//     return userinterrupt;
// }


// //////////////////////////////////////////////////////////////////
// //
// //  Public Functions
// //
// //

// ///
// //  esInitContext()
// //
// //      Initialize ES utility context.  This must be called before calling any other
// //      functions.
// //
// void ESUTIL_API esInitContext ( ESContext *esContext )
// {
//    if ( esContext != NULL )
//    {
//       memset( esContext, 0, sizeof( ESContext) );
//    }
// }


// ///
// //  esCreateWindow()
// //
// //      title - name for title bar of window
// //      width - width of window to create
// //      height - height of window to create
// //      flags  - bitwise or of window creation flags
// //          ES_WINDOW_ALPHA       - specifies that the framebuffer should have alpha
// //          ES_WINDOW_DEPTH       - specifies that a depth buffer should be created
// //          ES_WINDOW_STENCIL     - specifies that a stencil buffer should be created
// //          ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
// //
// GLboolean ESUTIL_API esCreateWindow ( ESContext *esContext, const char* title, GLint width, GLint height, GLuint flags )
// {
//    EGLint attribList[] =
//    {
//        EGL_RED_SIZE,       5,
//        EGL_GREEN_SIZE,     6,
//        EGL_BLUE_SIZE,      5,
//        EGL_ALPHA_SIZE,     (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
//        EGL_DEPTH_SIZE,     (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
//        EGL_STENCIL_SIZE,   (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
//        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
//        EGL_NONE
//    };

//    if ( esContext == NULL )
//    {
//       return GL_FALSE;
//    }

//    esContext->width = width;
//    esContext->height = height;

//    if ( !WinCreate ( esContext, title) )
//    {
//       return GL_FALSE;
//    }

//    //ESContext *esContext
//    if ( !CreateEGLContext ( esContext->hWnd,
//                             &esContext->eglDisplay,
//                             &esContext->eglContext,
//                             &esContext->eglSurface,
//                             attribList, esContext) )
//    {
//       return GL_FALSE;
//    }


//    return GL_TRUE;
// }


// ///
// //  esMainLoop()
// //
// //    Start the main loop for the OpenGL ES application
// //

// // void ESUTIL_API esMainLoop ( ESContext *esContext, ESContext *esContext2 )
// // {
// //     struct timeval t1, t2;
// //     struct timezone tz;
// //     float deltatime;
// //     float totaltime = 0.0f;
// //     unsigned int frames = 0;

// //     gettimeofday ( &t1 , &tz );

// //     int baldir = 1;
// //     float balspeed = 0.0001f;

// //     while(userInterrupt(esContext) == GL_FALSE && userInterrupt(esContext2) == GL_FALSE)
// //     {
// //         gettimeofday(&t2, &tz);
// //         deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
// //         t1 = t2;

// //         moveBall();

// //     eglMakeCurrent(esContext->eglDisplay, esContext->eglSurface, esContext->eglSurface, esContext->eglContext);

// //       if (ANA3D) {
// //         if (esContext->updateFunc != NULL)
// //             esContext->updateFunc(esContext, deltatime, -1);
// //         if (esContext->drawFunc != NULL)
// //             esContext->drawFunc(esContext, deltatime);

// //         if (esContext->updateFunc != NULL)
// //             esContext->updateFunc(esContext, deltatime, 1);
// //         if (esContext->drawFunc != NULL)
// //             esContext->drawFunc(esContext, deltatime);
// //         } else {
// //           if (esContext->updateFunc != NULL)
// //             esContext->updateFunc(esContext, deltatime, 0);
// //         if (esContext->drawFunc != NULL)
// //             esContext->drawFunc(esContext, deltatime);
// //         }



// //         eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);



// //     eglMakeCurrent(esContext2->eglDisplay, esContext2->eglSurface, esContext2->eglSurface, esContext2->eglContext);

// //       if (ANA3D) {
// //         if (esContext2->updateFunc != NULL)
// //             esContext2->updateFunc(esContext2, deltatime, -1);
// //         if (esContext2->drawFunc != NULL)
// //             esContext2->drawFunc(esContext2, deltatime);

// //         if (esContext2->updateFunc != NULL)
// //             esContext2->updateFunc(esContext2, deltatime, 1);
// //         if (esContext2->drawFunc != NULL)
// //             esContext2->drawFunc(esContext2, deltatime);
// //         } else {
// //           if (esContext2->updateFunc != NULL)
// //             esContext2->updateFunc(esContext2, deltatime, 0);
// //         if (esContext2->drawFunc != NULL)
// //             esContext2->drawFunc(esContext2, deltatime);
// //         }

// //         eglSwapBuffers(esContext2->eglDisplay, esContext2->eglSurface);




// //         totaltime += deltatime;
// //         frames++;
// //         if (totaltime >  4.0f)
// //         {
// //             printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames/totaltime);
// //             totaltime -= 4.0f;
// //             frames = 0;
// //         }
// //     }
// // }


// ///
// //  esRegisterDrawFunc()
// //
// void ESUTIL_API esRegisterDrawFunc ( ESContext *esContext, void (ESCALLBACK *drawFunc) (ESContext*, float ) )
// {
//    esContext->drawFunc = drawFunc;
// }


// ///
// //  esRegisterUpdateFunc()
// //
// void ESUTIL_API esRegisterUpdateFunc ( ESContext *esContext, void (ESCALLBACK *updateFunc) ( ESContext*, float, int ) )
// {
//    esContext->updateFunc = updateFunc;
// }


// ///
// //  esRegisterKeyFunc()
// //
// void ESUTIL_API esRegisterKeyFunc ( ESContext *esContext,
//                                     void (ESCALLBACK *keyFunc) (ESContext*, unsigned char, int, int ) )
// {
//    esContext->keyFunc = keyFunc;
// }


// ///
// // esLogMessage()
// //
// //    Log an error message to the debug output for the platform
// //
// void ESUTIL_API esLogMessage ( const char *formatStr, ... )
// {
//     va_list params;
//     char buf[BUFSIZ];

//     va_start ( params, formatStr );
//     vsprintf ( buf, formatStr, params );

//     printf ( "%s", buf );

//     va_end ( params );
// }


// ///
// // esLoadTGA()
// //
// //    Loads a 24-bit TGA image from a file. This is probably the simplest TGA loader ever.
// //    Does not support loading of compressed TGAs nor TGAa with alpha channel. But for the
// //    sake of the examples, this is sufficient.
// //

// char* ESUTIL_API esLoadTGA ( char *fileName, int *width, int *height )
// {
//     char *buffer = NULL;
//     FILE *f;
//     unsigned char tgaheader[12];
//     unsigned char attributes[6];
//     unsigned int imagesize;

//     f = fopen(fileName, "rb");
//     if(f == NULL) return NULL;

//     if(fread(&tgaheader, sizeof(tgaheader), 1, f) == 0)
//     {
//         fclose(f);
//         return NULL;
//     }

//     if(fread(attributes, sizeof(attributes), 1, f) == 0)
//     {
//         fclose(f);
//         return 0;
//     }

//     *width = attributes[1] * 256 + attributes[0];
//     *height = attributes[3] * 256 + attributes[2];
//     imagesize = attributes[4] / 8 * *width * *height;
//     buffer = (char *) malloc(imagesize);
//     if (buffer == NULL)
//     {
//         fclose(f);
//         return 0;
//     }

//     if(fread(buffer, 1, imagesize, f) != imagesize)
//     {
//         free(buffer);
//         return NULL;
//     }
//     fclose(f);
//     return buffer;
// }