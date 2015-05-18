#include "GameState.h"

GameState::GameState(string name) {
	this->name = name;
}

void GameState::start() {
	assertS(this->running == false, "don't start " + this->name + " game that's already running");
	this->running = true;
}

void GameState::pause() {
	assertS(this->running == true, this->name + " is already paused...");
	this->running = false;
}

void GameState::resume() {
	assertS(this->running == false, "don't start " + this->name + " game that's already running");
	this->running = true;
}

void GameState::loadShaders() {
	cout << "loading in shaders" << endl;
	for (int i = 0; i < this->entities.size(); i += 1) {
		this->entities[i]->loadShaders();
	}
}

void GameState::update(ESContext *context, float deltatime) {
	ESMatrix perspective;
	ESMatrix modelview;
	float aspect;

	context->makeCurrent();

	aspect = (GLfloat) context->window_width / (GLfloat) context->window_height;

	// eye love you <3
	for (int i = 0; i < this->entities.size(); i += 1) {
		this->entities[i]->update(deltatime);
	}

	esMatrixLoadIdentity(&perspective);
	       esPerspective(&perspective, 50.0f, aspect, 1.0f, 10.0f);
	esMatrixLoadIdentity(&modelview);
	         esTranslate(&modelview, 0.0, 0.0, -5.0);

	if (context->isPlayerOne == false) {
		esRotate(&modelview, 180, 0.0, 1.0, 0.0);
	}

	esMatrixMultiply(&mvpMatrix, &modelview, &perspective);
}

void GameState::render(ESContext *context) {
	glViewport(0, 0, context->window_width, context->window_height);
	glClear(GL_COLOR_BUFFER_BIT);


    if (context->isPlayerOne) {
    	for (int i = 0; i < this->entities.size(); i += 1) {
    		this->entities[i]->render();
    	}
    } else {
        for (int i = this->entities.size() - 1; i > -1; i -= 1) {
            this->entities[i]->render();
        }
    }
}

void GameState::addEntity(Entity *entity) {
    this->entities.push_back(entity);
    cout << "added " << entity->name << endl;
    entity->setCollection(&this->entities);
}
