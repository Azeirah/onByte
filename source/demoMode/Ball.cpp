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

        bounceOffWall(this, this->radius, this->velocity);

        Bat *bat1 = (Bat *) this->findEntity("bat1", "bat");
        Bat *bat2 = (Bat *) this->findEntity("bat2", "bat");

        // Bat or nearfielddetection
        if (this->position->z > fielddepth) {
            if (checkForBallBatCollision(this, bat1)) {
                bounceEffect.clone(this->position)->add(bat2->position)->multiply(keepXY)->scale(BALLBOUNCEEFFECTSCALE);

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
                this->velocity->z = BALLSTARTSPEEDZ * (generateFloat(0.0f, 1.0f) > 0.5f? 1.0f : -1.0f);
            }
        } else if (this->position->z < -fielddepth) {
            if (checkForBallBatCollision(this, bat2)) {
                bounceEffect.clone(this->position)->add(bat1->position)->multiply(keepXY)->scale(BALLBOUNCEEFFECTSCALE);

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
                this->velocity->z = BALLSTARTSPEEDZ * (generateFloat(0.0f, 1.0f) > 0.5f? 1.0f : -1.0f);

                this->gameState->game->switchToGameState("handbal");
            }
        }
    }

    Ball::Ball() : Sphere(10, 0.1f) {
        this->name = "ball";
        this->type = "ball";

        this->wireframe = false;

        this->velocity = new Vector();

        this->velocity->x = generateFloat(-BALLSTARTSPEEDX, BALLSTARTSPEEDX);
        this->velocity->y = generateFloat(-BALLSTARTSPEEDY, BALLSTARTSPEEDY);
        this->velocity->z = BALLSTARTSPEEDZ * (generateFloat(0.0f, 1.0f) > 0.5f? 1.0f : -1.0f);
    }
}

