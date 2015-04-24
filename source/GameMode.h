#pragma once

#include "string.h"
#include "GameState.h"

class GameMode {
public:
	string name;
	GameState* gameState;
};
