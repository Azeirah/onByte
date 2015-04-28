#include "TestGame.h"

TestGame::TestGame (string name) {
	Sphere *ball    = new Sphere(50, 0.2f);
	Field *field    = new Field(1.0f);

	this->gameState = new GameState(name);
	this->name      = name;

	this->gameState->entities.push_back(field);
	this->gameState->entities.push_back(ball);
}
