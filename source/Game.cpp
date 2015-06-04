#include "Game.h"

Game::Game() {
    // player 1
    this->context1 = new ESContext(true);
    this->context1->createWindow(SCREENNAME1, SCREENWIDTH, SCREENHEIGHT, ES_WINDOW_ALPHA);
    this->context1->makeCurrent();

    //this->channel = new SocketServer(1337);
}

// is blocking so should definitely run in a thread
void Game::receiveInput () {
  Json::Value *receive;

    while (true) {
        // create a new JsonValue object on the heap to receive inputs with
        // push these values onto the input buffer, which will then be distributed over the right Entities.
        // After distribution, the buffer will be cleared
        // This loop of receive -> distribute -> clear will be executed on every game tick
        receive = new Json::Value();
        this->channel->receive(receive);
        this->inputBuffer.push_back(receive);
    }
}

void Game::clearInputBuffer () {
    for (unsigned int i = 0; i < this->inputBuffer.size(); i++) {
        Json::Value value = this->inputBuffer[i];
        value.clear();
    }
}

void Game::startGameLoop () {
	struct timeval t1, t2;
	struct timezone tz;
	float deltatime;

	float totaltime     = 0.0f;
	unsigned int frames = 0;

	gettimeofday(&t1, &tz);

	while (! (this->context1->userInterrupt())) {
		// calculate delta time
		gettimeofday(&t2, &tz);
		deltatime = (float) (t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
		t1 = t2;

		this->context1->makeCurrent();
		this->currentState->update(this->context1, deltatime);
		this->currentState->render(this->context1);
		this->context1->swapBuffer();

		totaltime += deltatime;
		frames    += 1;

		// display framerate
		if (totaltime > 4.0f) {
			cout << frames << " frames rendered in " << totaltime << " seconds -> FPS=" << frames/totaltime << endl;
			totaltime -= 4.0f;
			frames    = 0;
		}
	}
}

void Game::addGameMode(GameMode* gameMode) {
	assertS(gameMode != NULL, "Gamemode should be initialized");
	this->gameStates.insert(pair<string, GameState*>(gameMode->name, gameMode->gameState));
}

void Game::switchToGameState(string name) {
	this->currentState = this->gameStates.at(name);
	cout << "switching to gameState " << name << endl;

	// load shaders per context
	this->context1->makeCurrent();
	this->currentState->loadShaders();
}
