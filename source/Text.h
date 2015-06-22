// #pragma once

// #define FONT_SMALL             24
// #define FONT_MEDIUM            36
// #define FONT_ABSOLUTE_POSITION false
// #define FONT_3D_POSITION       true

// #include "onByte.h"
// #include <map>
// #include <string>
// #include <FTGL/ftgl.h>
// #include <FTGL/FTGLTextureFont.h>
// #include <ft2build.h>
// #include FT_FREETYPE_H

// extern FTFont* myFont;

// using namespace std;
// typedef map<string, FTFont*> FontList;
// typedef FontList::const_iterator FontIter;

// class FTGLFontManager {
//     public:
//         static FTGLFontManager& Instance();
//         ~FTGLFontManager();
//         FTFont* GetFont(const char *filename, int size);
//     private:
//         FontList fonts;

//         FTGLFontManager();
//         FTGLFontManager(const FTGLFontManager&);
//         FTGLFontManager& operator = (const FTGLFontManager&){ return *this; };
// };
