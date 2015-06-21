#include "Ball.h"

namespace handbal {
    Vector* speedUp = new Vector( 1,  1,  1.04f);
    Vector* keepXY  = new Vector( 1,  1,  0);
    Vector* stop    = new Vector( 0,  0,  0);

    void Ball::update(float dt, vector<char *> input) {
        for (int i = 0; i < input.size(); i++) {
            cout << "In ball, got: '" << input[i] << "'" << endl;
        }

        Vector scaledVelocity(this->velocity->x, this->velocity->y, this->velocity->z);
        Vector bounceEffect;
        scaledVelocity.scale(dt * 100);

        this->position->add(&scaledVelocity);

        bounceOffWall(this, this->radius, this->velocity);

        Bat *bat1 = (Bat *) this->findEntity("bat1", "bat");

        if (this->position->z < -fielddepth) {
            this->velocity->z = abs(this->velocity->z);
        }

        if (this->position->z > fielddepth) {
            if (checkForBallBatCollision(this, bat1)) {
                bounceEffect.clone(this->position)->add(bat1->position)->multiply(keepXY)->scale(BALLBOUNCEEFFECTSCALE);

                this->velocity->add(&bounceEffect);
                this->velocity->z = -abs(this->velocity->z);
                this->velocity->multiply(speedUp);
            } else {
                this->position->x = 0;
                this->position->y = 0;
                this->position->z = 0;

                this->velocity->x = generateFloat(-BALLSTARTSPEEDX, BALLSTARTSPEEDX);
                this->velocity->y = generateFloat(-BALLSTARTSPEEDY, BALLSTARTSPEEDY);
                this->velocity->z = BALLSTARTSPEEDZ * (generateFloat(0.0f, 1.0f) > 0.5f? 1.0f : -1.0f);

                this->gameState->game->switchToGameState("hockey");
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

        cout << this->velocity->z << endl;
    }
}
