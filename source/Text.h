#pragma once

#include "onByte.h"
#include "esUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globals.h"

#include <ft2build.h>
#include FT_FREETYPE_H

int  init_resources();
void free_resources();
void render_text(const char *text, float x, float y, int fontsize, bool absolute);

#define FONT_SMALL             24
#define FONT_MEDIUM            36
#define FONT_ABSOLUTE_POSITION false
#define FONT_3D_POSITION       true
