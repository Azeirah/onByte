#include "Text.h"

GLuint program;
GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;

GLuint vbo;

FT_Library ft;
FT_Face face;

struct point {
    GLfloat x;
    GLfloat y;
    GLfloat s;
    GLfloat t;
};

const char * textVertexShader[1] = {
    "#version 100\n"
    "attribute vec4 coord;\n"
    "varying vec2 texpos;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(coord.xy, 0, 1);\n"
    "  texpos = coord.zw;\n"
    "}"
};

const char * textFragmentShader[1] = {
    "#version 100\n"
    "varying mediump vec2 texpos;\n"
    "uniform sampler2D tex;\n"
    "uniform mediump vec4 color;\n"
    "void main()\n"
    "{\n"
    "  gl_FragColor = vec4(1, 1, 1, texture2D(tex, texpos).a) * color;\n"
    "}"
};

int init_resources() {
    int freetypeInitialised = FT_Init_FreeType(&ft);
    assertS(freetypeInitialised == 0, "Could not init freetype library");
    cout << "freetype initialized = " << freetypeInitialised << endl;

    // Load a font
    int fontLoaded = FT_New_Face(ft, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 0, &face);
    assertS(fontLoaded == 0, "Could not open font");
    cout << "font loaded = " << fontLoaded << endl;

    program = esLoadProgram(*textVertexShader, *textFragmentShader);
    assertS(program != 0, "Font shaders weren't loaded properly");

    attribute_coord = glGetAttribLocation (program, "coord");
    uniform_tex     = glGetUniformLocation(program, "tex");
    uniform_color   = glGetUniformLocation(program, "color");

    assertS(attribute_coord != -1, "Something went wrong with loading attribute 'coord'");
    assertS(uniform_tex != -1, "Something went wrong with loading uniform 'text'");
    assertS(uniform_color != -1, "Something went wrong with loading the uniform 'color'");

    // Create the vertex buffer object
    glGenBuffers(1, &vbo);


    return 1;
}

// I like how well annotated this source is, really nice!end
/**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
void render_text(const char *text, float x, float y, int fontSize, bool absolutePosition) {
    // translating allows you to go from 3d positions (-0.9f to 0.9f) to absolute screen positions (0 to 800)
    if (absolutePosition) {
        x = translate(x, 0, SCREENWIDTH, -fieldwidth,  fieldwidth);
        // y coordinate in opengl starts at the bottom of the screen
        // so I translate upside down as well as from pixel to screen coordinate
        y = translate(y, SCREENHEIGHT, 0, -fieldheight, fieldheight);
    }

    float sx = 2.0 / SCREENWIDTH;
    float sy = 2.0 / SCREENHEIGHT;

    // ESMatrix modelview = mvpMatrix;

    // esTranslate(&modelview, x, y, 0);

    glUseProgram(program);
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glUniform4fv(uniform_color, 1, green);

    const char *p;
    FT_GlyphSlot g = face->glyph;

    /* Create a texture that will be used to hold one "glyph" */
    GLuint tex;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(uniform_tex, 0);

    /* We require 1 byte alignment when uploading texture data */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* Clamping to edges is important to prevent artifacts when scaling */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* Linear filtering usually looks best for text */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Set up the VBO for our vertex data */
    glEnableVertexAttribArray(attribute_coord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

    /* Loop through all characters */
    for (p = text; *p; p++) {
        /* Try to load and render the character */
        if (FT_Load_Char(face, *p, FT_LOAD_RENDER)) {
            continue;
        }

        /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        /* Calculate the vertex and texture coordinates */
        float x2 = x + g->bitmap_left * sx;
        float y2 = -y - g->bitmap_top * sy;
        float w = g->bitmap.width * sx;
        float h = g->bitmap.rows * sy;

        point box[4] = {
            {x2, -y2, 0, 0},
            {x2 + w, -y2, 1, 0},
            {x2, -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };

        /* Draw the character on the screen */
        glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
        // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawElements(GL_TRIANGLE_STRIP, 0, 4);

        /* Advance the cursor to the start of the next character */
        x += (g->advance.x >> 6) * sx;
        y += (g->advance.y >> 6) * sy;
    }

    glDisableVertexAttribArray(attribute_coord);
    glDeleteTextures(1, &tex);
}

void free_resources() {
    glDeleteProgram(program);
}

