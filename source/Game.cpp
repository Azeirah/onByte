#include "Game.h"

Game::Game() {

    // player 1
    this->context1 = new ESContext(true);
    this->context1->createWindow(SCREENNAME1, SCREENWIDTH, SCREENHEIGHT, ES_WINDOW_ALPHA);
    this->context1->makeCurrent();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // this is blocking, sorry :(
    // you'll need to connect to an input client before the game can run.
    this->channel         = new SocketServer(1338);
    thread * receiveInput = new thread(&Game::receiveInput, this);
}

// is blocking so should definitely run in a thread
void Game::receiveInput () {
    while (true) {
        char * receive = new char[32];
        memset(receive, 0, sizeof(receive) - 1);
        // create a new buffer object on the heap to receive inputs with
        // push these values onto the input buffer, which will then be distributed over the right Entities.
        // After distribution, the buffer will be cleared
        // This loop of receive -> distribute -> clear will be executed on every game tick
        this->channel->receive(receive);
        this->inputBuffer.push_back(receive);
    }
}

void Game::clearInputBuffer() {
    for (unsigned int i = 0; i < this->inputBuffer.size(); i++) {
        delete this->inputBuffer[i];
    }
    this->inputBuffer.clear();
}

void Game::startGameLoop() {
    struct timeval t1, t2;
    struct timezone tz;
    float deltatime;

    float totaltime     = 0.0f;
    unsigned int frames = 0;

    gettimeofday(&t1, &tz);

    while (! (this->context1->userInterrupt())) {
        // calculate delta time
        gettimeofday(&t2, &tz);
        // this->channel->send("1:1");
        deltatime = (float) (t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
        t1 = t2;

        // glViewport(0, 0, this->context1->window_width, this->context1->window_height);
        // glClear(GL_COLOR_BUFFER_BIT);

        this->context1->makeCurrent();
        this->currentState->update(this->context1, deltatime, this->inputBuffer);
        this->currentState->render(this->context1, -1);
        this->currentState->render(this->context1,  1);
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

void Game::addGameMode(GameState* gameState) {
    assertS(gameState != NULL, "Gamemode should be initialized");
    this->gameStates.insert(pair<string, GameState*>(gameState->name, gameState));

    gameState->game = this;
}

void Game::switchToGameState(string name) {
    // if (this->currentStateName != "") {
    //     delete this->gameStates[this->currentStateName];
    //     this->gameStates[this->currentStateName] = NULL;
    // }

    assertS(this->gameStates[name] != NULL, "Tried to enter an undefined gamestate, either misspelled it in game.switchToGameState, or didn't add it in game.addGameMode");

    // cout << "address of state" << this->gameStates[name] << endl;

    // if (this->gameStates[name] == NULL) {
    //     cout << "Initialize the state" << endl;
    //     new this->gameStates[name](name);
    // }
    this->currentState     = this->gameStates[name];
    this->currentStateName = name;
    cout << "switched to gameState " << name << endl;

    // server.send("g," + name);

    // load shaders per context
    this->context1->makeCurrent();
    this->currentState->loadShaders();
}
