#pragma once

#include <vector>
#include "onByte.h"
#include "ESContext.h"
#include "Entity.h"

class GameState {
private:
	// gamestates need to have a unique name
	string name;
	bool running;
public:
	std::vector<Entity *> entities;
	GameState(string);
	// ~GameState();

	void update(ESContext*, float deltatime);
	void render(ESContext*);

	void start();
	void pause();
	void resume();
};
