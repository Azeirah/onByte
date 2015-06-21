#pragma once

#include "onByte.h"
#include "Entity.h"
#include "Vector.h"

bool checkForBallBatCollision(Entity* ball, Entity* bat);
bool bounceOffWall(Entity*, float, Vector*);
