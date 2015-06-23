#include "Bat.h"
#include <sstream>

// #include <FTGL/ftgl.h>

// #include <GLES2/gl2.h>
// #include <EGL/egl.h>

namespace handbal {
    void Bat::update(float dt, vector<string> input) {
        static float totaltime = 0;

        totaltime += dt;
        this->angle += 0.1;

        Entity* ball = this->findEntity("ball", "ball");

        this->position->x += dt * 7 * (ball->position->x - this->position->x);
        this->position->y += dt * 7 * (ball->position->y - this->position->y);
    }


    // void Bat::render() {
    //     myFont->Render("abcdefghijklmnopqrstuvwxyz");
    // }

    Bat::Bat(GLfloat position, float color[4], int batNumber) : Rectangle(batwidth, batheight, batdepth) {
        this->name        = "bat" + SSTR(batNumber);
        this->type        = "bat";
        this->position->z = position;

        memcpy(this->color, color, colorSize);
  }
}
