#pragma once

#include <string>
#include "../globals.h"
#include "../GameState.h"

#include "Ball.h"
#include "GameField.h"
#include "Bat.h"
#include "BallFollower.h"

class DemoMode : public GameState {
public:
    DemoMode(string);
};
