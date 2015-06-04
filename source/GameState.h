#pragma once

#include <vector>
#include "onByte.h"
#include "ESContext.h"
#include "Entity.h"
#include "globals.h"

class GameState {
protected:
	// gamestates need to have a unique name
	bool running;
public:
	string name;
	std::vector<Entity *> entities;
	// ~GameState();

	// game loop functionality
	void update(ESContext*, float deltatime, vector<Json::Value*>);
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
