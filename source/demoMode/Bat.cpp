#include "Bat.h"

#include <sstream>

#define SSTR(x) dynamic_cast< std::ostringstream & >( \
        (std::ostringstream() << std::dec << x)).str()

void Bat::update(float dt, vector<Json::Value*> input) {
    static float totaltime = 0;
    totaltime += dt;
    this->position->y = sin(totaltime) * fieldheight;
    this->angle += 0.1;
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
