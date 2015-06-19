#pragma once

#include "Entity.h"
#include <iostream>

#define COLLISION_FRONT true
#define COLLISION_BACK  false

bool checkForBallBatCollision(Entity* ball, Entity* bat);
