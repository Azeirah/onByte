#pragma once

#include <string>
#include "../globals.h"
#include "../GameState.h"

#include "Ball.h"
#include "GameField.h"
#include "Bat.h"
#include "BallFollower.h"

namespace handbal {
	class Handbal : public GameState {
	public:
	    Handbal(string);
	};
}

