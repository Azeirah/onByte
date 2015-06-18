#pragma once

#include <string>
#include "../globals.h"
#include "../GameState.h"

#include "Ball.h"
#include "GameField.h"
#include "Bat.h"
#include "BallFollower.h"

namespace demo {
    class DemoMode : public GameState {
    public:
        DemoMode(string);
    };
}
