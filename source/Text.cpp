// #include "Text.h"

// FTGLFontManager::FTGLFontManager() {

// }

// FTGLFontManager::~FTGLFontManager() {
//     FontIter font;

//     for(font = fonts.begin(); font != fonts.end(); font++) {
//         delete (*font).second;
//     }

//     fonts.clear();
// }

// FTGLFontManager& FTGLFontManager::Instance() {
//     static FTGLFontManager tm;
//     return tm;
// }

// FTFont* FTGLFontManager::GetFont(const char *filename, int size) {
//     char buf[256];
//     sprintf(buf, "%s%i", filename, size);
//     string fontKey = string(buf);
//     FontIter result = fonts.find(fontKey);

//     if (result != fonts.end()) {
//         cout << "Found font " << filename << " in list" << endl;
//         return result->second;
//     }

//     string fullname = ("/usr/share/fonts/truetype/freefont/" + string(filename));

//     FTFont* font = new FTTextureFont(fullname.c_str());
//     cout << "Font is " << "/usr/share/fonts/truetype/freefont/" + string(filename) << endl;

//     if (!font) {
//         cout << "Font " << fullname << " failed to open" << endl;
//         delete font;
//         return NULL;
//     }

//     if (font->Error()) {
//         cout << "Unknown font error!" << endl;
//         return NULL;
//     }

//     if (!font->FaceSize(size)) {
//         cout << "Font " << fullname << " failed to set size" << size << endl;
//         delete font;
//         return NULL;
//     }

//     fonts[fontKey] = font;
//     return font;
// }

// FTFont* myFont = FTGLFontManager::Instance().GetFont("FreeSerif.ttf", 72);
