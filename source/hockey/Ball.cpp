#include "Ball.h"

#include <sstream>
#define SSTR(x) dynamic_cast< std::ostringstream & >( \
        (std::ostringstream() << std::dec << x)).str()

namespace hockey {
    Vector* bounceX = new Vector(-1,  1,  1);
    Vector* bounceY = new Vector( 1, -1,  1);
    Vector* bounceZ = new Vector( 1,  1, -1);

    Vector* speedUp = new Vector( 1,  1,  BALLSPEEDMULTIPLIER);
    Vector* keepXY  = new Vector( 1,  1,  0);
    Vector* stop    = new Vector( 0,  0,  0);

    void Ball::update(float dt, vector<string> input) {
        static int bounces = 0;

        Vector scaledVelocity(this->velocity->x, this->velocity->y, this->velocity->z);
        Vector bounceEffect;
        scaledVelocity.scale(dt * 100);

        this->position->add(&scaledVelocity);

        bounceOffWall(this, this->radius, this->velocity);

        Bat *bat1 = (Bat *) this->findEntity("bat1", "bat");

        if (this->position->z < -fielddepth) {
            this->velocity->z = abs(this->velocity->z);
            bounces += 1;
            if (bounces % 5 == 0) {
                this->velocity->multiply(speedUp);
            }
        }

        if (this->position->z > fielddepth) {
            if (checkForBallBatCollision(this, bat1)) {
                bounceEffect.clone(this->position)->add(bat1->position)->multiply(keepXY)->scale(0.014f);

                this->velocity->add(&bounceEffect);
                this->velocity->z = -abs(this->velocity->z);
            } else {
                this->position->x = 0;
                this->position->y = 0;
                this->position->z = 0;

                this->velocity->x = generateFloat(-BALLSTARTSPEEDX, BALLSTARTSPEEDX);
                this->velocity->y = generateFloat(-BALLSTARTSPEEDY, BALLSTARTSPEEDY);
                this->velocity->z = generateFloat(-BALLSTARTSPEEDZ, BALLSTARTSPEEDZ);

                bounces = 0;

                this->gameState->game->switchToGameState("demo");
            }
        }

        // server.send("p,ball" + SSTR(this->position->x) + "," + SSTR(this->position->y) + "," + SSTR(this->position->z) + ",g");
    }

    Ball::Ball() : Sphere(10, 0.1f) {
        this->name = "ball";
        this->type = "ball";

        this->wireframe = false;

        this->velocity = new Vector(generateFloat(0, 0.01f), generateFloat(0, 0.01f), generateFloat(0.04f, 0.09f));
    }
}
