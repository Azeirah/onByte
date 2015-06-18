#include "Bat.h"

#include <sstream>

namespace demo {
    #define SSTR(x) dynamic_cast< std::ostringstream & >( \
            (std::ostringstream() << std::dec << x)).str()

    void Bat::update(float dt, vector<char *> input) {
        static float totaltime = 0;
        totaltime += dt;
        // this->position->y = sin(totaltime) * fieldheight;
        this->angle += 0.1;

        Entity* ball = this->findEntity("ball", "ball");

        this->position->x += dt * 7 * (ball->position->x - this->position->x);
        this->position->y += dt * 7 * (ball->position->y - this->position->y);

        // this->position->y += this->findEntity("ball", "ball")->position->y * .1;
        // this->position->x += this->findEntity("ball", "ball")->position->x * .1;

        // for (unsigned int i = 0; i < input.size(); i++) {
        //     cout << "Received input: " << input[i] << endl;
        // }
        //
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
