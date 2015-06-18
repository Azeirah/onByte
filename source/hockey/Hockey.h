#pragma once

#include <string>
#include "../globals.h"
#include "../GameState.h"

#include "Ball.h"
#include "GameField.h"
#include "Bat.h"
#include "BallFollower.h"

namespace hockey {
	class Hockey : public GameState {
	public:
	    Hockey(string);
	};
}

