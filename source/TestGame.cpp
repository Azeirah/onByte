#include "TestGame.h"

TestGame::TestGame (string name) {
    Sphere *ball         = new Sphere(10, 0.1f);
    Field *field         = new Field(1.0f);
    Bat *player1         = new Bat(1.0f, -fielddepth, red,   1);
    Bat *player2         = new Bat(1.0f,  fielddepth, green, 2);
    BallFollower *follow = new BallFollower(1.0f, &ball->position->z);

    this->gameState      = new GameState(name);
    this->name           = name;

	this->gameState->entities.push_back(field);
	this->gameState->entities.push_back(ball);
    this->gameState->entities.push_back(player1);
    this->gameState->entities.push_back(player2);
    this->gameState->entities.push_back(follow);
}
