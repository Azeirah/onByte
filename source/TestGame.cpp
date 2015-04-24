#include "TestGame.h"

TestGame::TestGame (string name) {
	this->gameState = new GameState(name);
	this->name = name;
}
