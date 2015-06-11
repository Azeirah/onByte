#include "Ball.h"

Vector* bounceX = new Vector(-1,  1,  1);
Vector* bounceY = new Vector( 1, -1,  1);
Vector* bounceZ = new Vector( 1,  1, -1);

void Ball::update(float dt, vector<Json::Value*> input) {
    Vector scaledVelocity(this->velocity->x, this->velocity->y, this->velocity->z);
    scaledVelocity.scale(dt * 100);

    this->position->add(&scaledVelocity);

    if (this->position->x > fieldwidth - this->radius || this->position->x < -fieldwidth + this->radius) {
        this->velocity->multiply(bounceX);
    }

    if (this->position->y > fieldheight - this->radius || this->position->y < -fieldheight + this->radius) {
        this->velocity->multiply(bounceY);
    }

    Bat *bat1 = (Bat *) this->findEntity("bat1", "bat");
    Bat *bat2 = (Bat *) this->findEntity("bat2", "bat");

    // Bat or nearfielddetection
    if (this->position->z > fielddepth                    &&
        this->position->x > bat2->position->x - batwidth  &&
        this->position->x < bat2->position->x + batwidth  &&
        this->position->y > bat2->position->y - batheight &&
        this->position->y < bat2->position->y + batheight
    ) {
      this->velocity->multiply(bounceZ);
    } else if (this->position->z < -fielddepth                   &&
               this->position->x > bat1->position->x - batwidth  &&
               this->position->x < bat1->position->x + batwidth  &&
               this->position->y > bat1->position->y - batheight &&
               this->position->y < bat1->position->y + batheight
    ) {
      this->velocity->multiply(bounceZ);
    } else if (this->position->z > fielddepth || this->position->z < -fielddepth) {
      this->velocity->multiply(bounceZ);
      this->position->x = 0;
      this->position->y = 0;
      this->position->z = 0;

      this->velocity->x = generateFloat(0, 0.01f);
      this->velocity->y = generateFloat(0, 0.01f);
    }
}

Ball::Ball() : Sphere(10, 0.1f) {
    this->name = "ball";
    this->type = "ball";
}
