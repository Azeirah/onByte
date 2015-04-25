#include "TestGame.h"

TestGame::TestGame (string name) {
	Sphere *s = new Sphere(20, 5);

	this->gameState = new GameState(name);
	this->name = name;

	this->gameState->entities.push_back(s);
}
