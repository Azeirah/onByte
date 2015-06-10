#include "esUtil.h"

GLuint esLoadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);

    if (shader == 0) {
        return 0;
    }

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char* infoLog = (char *) malloc(sizeof(char) * infoLen);

            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            cout << "Error compiling shader " << infoLog << endl;

            free(infoLog);
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc) {
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = esLoadShader(GL_VERTEX_SHADER, vertShaderSrc);
    if (vertexShader == 0) {
       return 0;
    }

    fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fragShaderSrc);
    if (fragmentShader == 0) {
       glDeleteShader(vertexShader);
       return 0;
    }

    // Create the program object
    programObject = glCreateProgram();

    if (programObject == 0) {
       return 0;
    }

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Link the program
    glLinkProgram(programObject);

    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked) {
      GLint infoLen = 0;

      glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

      if (infoLen > 1) {
         char* infoLog = (char *) malloc (sizeof(char) * infoLen);

         glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
         cout << "Error linking program: " << infoLog << endl;

         free(infoLog);
      }

      glDeleteProgram(programObject);
      return 0;
    }

    // Free up no longer needed shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programObject;
}

void esLogMessage(const char *formatStr, ...) {
    cout << "er is een error! Ik hoop dat dit er nooit komt te staan." <<
    " Dit is namelijk geen duidelijke error beschrijving, lekker Martijn!" <<
    endl;
    // va_list params;
    // char buf[BUFSIZ];
    //
    // va_start (params, formatStr);
    // vsprintf (buf, formatStr, params);
    //
    // printf ("%s", buf);
    //
    // va_end (params);
}

const char *defaultFragmentShader[6] = {
     "precision mediump float;                    \n"
     "uniform vec4 color;                         \n"
     "void main()                                 \n"
     "{                                           \n"
     "  gl_FragColor = color;                     \n"
     "}                                           \n"
};

const char *defaultVertexShader[6] = {
     "uniform mat4 u_mvpMatrix;                   \n"
     "attribute vec4 a_position;                  \n"
     "void main()                                 \n"
     "{                                           \n"
     "   gl_Position = u_mvpMatrix * a_position;  \n"
     "}                                           \n"
};
