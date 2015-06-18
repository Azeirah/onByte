#include "collisionDetection.h"

bool checkForBallBatCollision(Entity* ball, Entity* bat) {
    Vector* ballp = ball->position;
    Vector* batp = bat->position;

    cout << "I am in fact checking for collision! It is no imposer" << endl;

    return ballp->x > batp->x - batwidth  &&
           ballp->x < batp->x + batwidth  &&
           ballp->y > batp->y - batheight &&
           ballp->y < batp->y + batheight;
}
