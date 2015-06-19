#include "collisionDetection.h"

bool checkForBallBatCollision(Entity* ball, Entity* bat) {
    Vector* ballp = ball->position;
    Vector* batp = bat->position;

    return ballp->x > batp->x - batwidth  &&
           ballp->x < batp->x + batwidth  &&
           ballp->y > batp->y - batheight &&
           ballp->y < batp->y + batheight;
}
