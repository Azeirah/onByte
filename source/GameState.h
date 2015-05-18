#pragma once

#include <vector>
#include "onByte.h"
#include "ESContext.h"
#include "Entity.h"
#include "globals.h"

class GameState {
private:
	// gamestates need to have a unique name
	string name;
	bool running;
public:
	std::vector<Entity *> entities;
	GameState(string);
	// ~GameState();

	// game loop functionality
	void update(ESContext*, float deltatime);
	void render(ESContext*);

	// loading shaders (duh..)
	void loadShaders();

    // adding entities to the gamestate
    void addEntity(Entity *entity);

	// controlling gamemode time
	void start();
	void pause();
	void resume();
};
