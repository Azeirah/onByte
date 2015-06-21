#include "collisionDetection.h"

bool checkForBallBatCollision(Entity* ball, Entity* bat) {
    Vector* ballp = ball->position;
    Vector* batp = bat->position;

    return ballp->x > batp->x - batwidth  &&
           ballp->x < batp->x + batwidth  &&
           ballp->y > batp->y - batheight &&
           ballp->y < batp->y + batheight;
}

bool bounceOffWall(Entity* ball, float radius, Vector* velocity) {
    bool bounced = false;

    if (ball->position->x > fieldwidth - radius) {
        // force a negative value, so it always goes left.
        velocity->x = -abs(velocity->x);
        bounced = true;
    } else if (ball->position->x < -fieldwidth + radius) {
        // force positive value, so ball goes right.
        velocity->x = abs(velocity->x);
        bounced = true;
    } else if (ball->position->y > fieldheight - radius) {
        // force positive value, so ball goes (up?)
        velocity->y = -abs(velocity->y);
        bounced = true;
    } else if (ball->position->y < - fieldheight + radius) {
        velocity->y = abs(velocity->y);
        bounced = true;
    }

    return bounced;
}
