#pragma once

#include <vector>
#include "ESContext.h"
#include "Entity.h"
#include "globals.h"
#include "Game.h"

#define halfEyeWidth 0.01f

class Game;
class Entity;

class GameState {
protected:
	// gamestates need to have a unique name
	bool running;
public:
	Game *game;

	string name;
	std::vector<Entity *> entities;
	// ~GameState();
	//
	void setParentGame(Game* game);

	// game loop functionality
	void update(ESContext*, float deltatime, vector<char *>);
	void render(ESContext*, int);

	// loading shaders (duh..)
	void loadShaders();

    // adding entities to the gamestate
    void addEntity(Entity *entity);

	// controlling gamemode time
	void start();
	void pause();
	void resume();
};
