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

        // Entity* ball = this->findEntity("ball", "ball");

        // this->position->x += dt * 7 * (ball->position->x - this->position->x);
        // this->position->y += dt * 7 * (ball->position->y - this->position->y);


        for (int i = 0; i < input.size(); i++) {
            string player = "bat" + SSTR(input[i][0]);

            int separatorPos = input[i].find(":");
            string sdx = input[i].substr(1, separatorPos);
            string sdy = input[i].substr(separatorPos + 1, input[i].length() - 1);

            try {
                float dx = stof(sdx);
                float dy = stof(sdy);
                cout << "received in bat (" << dx << ", " << dy << ")" << endl;

                cout << "playername '" << this->name << "' == '" << player << "'?" << "input[i][0] = '" << input[i][0] << "'" << endl;

                if (dx < 1 && dy < 1 && this->name == player) {
                    this->position->x += dx;
                    this->position->y += dy;
                }
            } catch(int e) {

            }
        }

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
