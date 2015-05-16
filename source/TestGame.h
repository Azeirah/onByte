#pragma once

#include "TestGame.h"
#include <string>
#include "globals.h"
#include "GameMode.h"
#include "Sphere.h"
#include "Field.h"
#include "Bat.h"
#include "BallFollower.h"

class TestGame : public GameMode {
public:
	TestGame(string);
};
