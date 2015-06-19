#include "Ball.h"

namespace demo {
    Vector* bounceX = new Vector(-1,  1,  1);
    Vector* bounceY = new Vector( 1, -1,  1);
    Vector* bounceZ = new Vector( 1,  1, -1);

    Vector* speedUp = new Vector( 1,  1,  BALLSPEEDMULTIPLIER);
    Vector* keepXY  = new Vector( 1,  1,  0);

    void Ball::update(float dt, vector<char *> input) {
        Vector scaledVelocity(this->velocity->x, this->velocity->y, this->velocity->z);
        Vector bounceEffect;
        Vector wallBounce;
        // 100 is an empirically chosen value based on the weather, a fortune cookie and a dice roll.
        scaledVelocity.scale(dt * 100);

        this->position->add(&scaledVelocity);

        if (this->position->x > fieldwidth - this->radius) {
            // force a negative value, so it always goes left.
            this->velocity->x = abs(this->velocity->x);
        } else if (this->position->x < -fieldwidth + this->radius) {
            // force positive value, so ball goes right.
            this->velocity->x = -abs(this->velocity->x);
        } else if (this->position->y > fieldheight - this->radius) {
            // force positive value, so ball goes (up?)
            this->velocity->y = abs(this->velocity->y);
        } else if (this->position->y < - fieldheight + this->radius) {
            this->velocity->y = -abs(this->velocity->y);
        }

        if (this->position->x > fieldwidth - this->radius || this->position->x < -fieldwidth + this->radius) {
            this->velocity->multiply(bounceX);
        }

        if (this->position->y > fieldheight - this->radius || this->position->y < -fieldheight + this->radius) {
            this->velocity->multiply(bounceY);
        }

        Bat *bat1 = (Bat *) this->findEntity("bat1", "bat");
        Bat *bat2 = (Bat *) this->findEntity("bat2", "bat");

        // Bat or nearfielddetection
        if (this->position->z > fielddepth) {
            if (checkForBallBatCollision(this, bat1)) {
                bounceEffect.clone(this->position)->add(bat2->position)->multiply(keepXY)->scale(BALLBOUNCEEFFECTSCALE * dt);

                this->velocity->add(&bounceEffect);
                this->velocity->multiply(bounceZ);
                this->velocity->multiply(speedUp);
            } else {
                this->velocity->multiply(bounceZ);
                this->position->x = 0;
                this->position->y = 0;
                this->position->z = 0;

                this->velocity->x = generateFloat(-BALLSTARTSPEEDX, BALLSTARTSPEEDX);
                this->velocity->y = generateFloat(-BALLSTARTSPEEDY, BALLSTARTSPEEDY);
                this->velocity->z = generateFloat(-BALLSTARTSPEEDZ, BALLSTARTSPEEDZ);
            }
        } else if (this->position->z < -fielddepth) {
            if (checkForBallBatCollision(this, bat2)) {
                bounceEffect.clone(this->position)->add(bat1->position)->multiply(keepXY)->scale(BALLBOUNCEEFFECTSCALE * dt);

                this->velocity->add(&bounceEffect);
                this->velocity->multiply(bounceZ);
                this->velocity->multiply(speedUp);

            } else {
                this->velocity->multiply(bounceZ);
                this->position->x = 0;
                this->position->y = 0;
                this->position->z = 0;

                this->velocity->x = generateFloat(-BALLSTARTSPEEDX, BALLSTARTSPEEDX);
                this->velocity->y = generateFloat(-BALLSTARTSPEEDY, BALLSTARTSPEEDY);
                this->velocity->z = generateFloat(-BALLSTARTSPEEDZ, BALLSTARTSPEEDZ);

                this->gameState->game->switchToGameState("handbal");
            }
        }
    }

    Ball::Ball() : Sphere(10, 0.1f) {
        this->name = "ball";
        this->type = "ball";

        this->wireframe = false;

        this->velocity = new Vector(generateFloat(-BALLSTARTSPEEDX, BALLSTARTSPEEDX), generateFloat(-BALLSTARTSPEEDY, BALLSTARTSPEEDY), generateFloat(-BALLSTARTSPEEDZ, BALLSTARTSPEEDZ));
    }
}

