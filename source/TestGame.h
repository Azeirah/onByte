#pragma once

#include <string>
#include "globals.h"
#include "Sphere.h"
#include "Field.h"
#include "Bat.h"
#include "BallFollower.h"
#include "GameState.h"

class TestGame : public GameState {
public:
	TestGame(string);
};
