Code wordt alleen in de main branch toegelaten wanneer:

1. Het compilet op de banana pi
2. De nieuwe code en het gedrag is bekeken en goedgekeurd door een groepsgenoot
3. Het gecompilet is zonder warnings, en natuurlijk ook geen errors.
4. De code goed geformat is (clang format)

Het compilen gaat vanaf dag een met

Nieuwe versie van c++
-std=c++11

Optimizer op niveau 3
-O3

Warnings op max
-Wall en -Wextra


## Dependencies:

- Freetype

sudo apt-get install freetype*

- X11
- Mesa
- OpenGL (gl.h)
- FreeType2
- FTGL

## ftgl installeren:

```bash
wget http://files.martijnbrekelmans.com/cdn/ftgl-2.1.3-rc5.tar.gz
./configure
make
sudo make install
```

Gebruik (moet waarschijnlijk een volledig pad naar het font geven):
```c++
FTGLPixmapFont font("Arial.ttf");
font.FaceSize(72);
font.Render("Hello World!");
```
