#include "Bat.h"
#include <sstream>

#define SSTR(x) dynamic_cast< std::ostringstream & >( \
        (std::ostringstream() << std::dec << x)).str()

namespace hockey {
    void Bat::update(float dt, vector<string> input) {
        static float totaltime = 0;

        totaltime += dt;
        this->angle += 0.1;

        Entity* ball = this->findEntity("ball", "ball");

        this->position->x += dt * 7 * (ball->position->x - this->position->x);
        this->position->y += dt * 7 * (ball->position->y - this->position->y);

        // server.send("p," + this->name + "," + SSTR(this->position->x) + "," + SSTR(this->position->y) + "," + SSTR(this->position->z) + ",g");
    }


    // void Bat::render() {
    //     render_text("bat!", this->position->x, this->position->y, FONT_MEDIUM, FONT_ABSOLUTE_POSITION);
    // }

    Bat::Bat(GLfloat position, float color[4], int batNumber) : Rectangle(batwidth, batheight, batdepth) {
        this->name        = "bat" + SSTR(batNumber);
        this->type        = "bat";
        this->position->z = position;

        memcpy(this->color, color, colorSize);
  }
}
