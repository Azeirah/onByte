#include "Ball.h"

Vector* bounceX = new Vector(-1,  1,  1);
Vector* bounceY = new Vector( 1, -1,  1);
Vector* bounceZ = new Vector( 1,  1, -1);

Vector* speedUp = new Vector( 1,  1,  1.04f);
Vector* keepXY  = new Vector( 1,  1,  0);

void Ball::update(float dt, vector<char *> input) {
    Vector scaledVelocity(this->velocity->x, this->velocity->y, this->velocity->z);
    Vector bounceEffect;
    scaledVelocity.scale(dt * 100);

    this->color[3] = translate(this->velocity->z, -0.2f, 0.2f, 0.0, 1.0f);

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
        bounceEffect.clone(this->position)->add(bat2->position)->multiply(keepXY)->scale(0.014f);

        this->velocity->add(&bounceEffect);
        this->velocity->multiply(bounceZ);
        this->velocity->multiply(speedUp);

    } else if (this->position->z < -fielddepth                   &&
               this->position->x > bat1->position->x - batwidth  &&
               this->position->x < bat1->position->x + batwidth  &&
               this->position->y > bat1->position->y - batheight &&
               this->position->y < bat1->position->y + batheight
    ) {
        bounceEffect.clone(this->position)->add(bat1->position)->multiply(keepXY)->scale(0.014f);

        this->velocity->add(&bounceEffect);
        this->velocity->multiply(bounceZ);
        this->velocity->multiply(speedUp);

    } else if (this->position->z > fielddepth || this->position->z < -fielddepth) {
        this->velocity->multiply(bounceZ);
        this->position->x = 0;
        this->position->y = 0;
        this->position->z = 0;

        this->velocity->x = generateFloat(0, 0.01f);
        this->velocity->y = generateFloat(0, 0.01f);
        this->velocity->z = generateFloat(0.04f, 0.09f);
    }
}

Ball::Ball() : Sphere(10, 0.1f) {
    this->name = "ball";
    this->type = "ball";

    this->wireframe = false;

    this->velocity = new Vector(generateFloat(0, 0.01f), generateFloat(0, 0.01f), generateFloat(0.04f, 0.09f));
}
