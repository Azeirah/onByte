#include "GameState.h"

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
    for (unsigned int i = 0; i < this->entities.size(); i += 1) {
        this->entities[i]->loadShaders();
    }
}

void GameState::update(ESContext *context, float deltatime, vector<char *> input) {
    ESMatrix perspective;
    ESMatrix modelview;
    float aspect;

    // copy the input to prevent any kinds of weird thread memory read/write violations.
    vector<string> inputCopy;

    for (unsigned int i = 0; i < input.size(); i++) {
        inputCopy.push_back(string(input[i], strlen(input[i])));
    }

    // clear game's input buffer after copying everything inside it.

    context->makeCurrent();

    aspect = (GLfloat) context->window_width / (GLfloat) context->window_height;

    string sendToUnity[5] = {"0,-5,0", "0,-5,0", "0,-5,0", "0,-5,0", "0,-5,0"};
    string order[5] = {"bat1", "bat2", "bat3", "bat4", "ball"};

    // eye love you <3
    for (unsigned int i = 0; i < this->entities.size(); i += 1) {
        Entity* entity = this->entities[i];
        entity->update(deltatime, inputCopy);
        for (unsigned int j = 0; j < 5; j++) {
            if (order[j] == entity->name) {
                sendToUnity[j] = SSTR(entity->position->x) + "," + SSTR(entity->position->y) + "," + SSTR(entity->position->z);
            }
        }
    }

    this->game->clearInputBuffer();

    // string totalSend = "";
    // for (int i = 0; i < 5; i++) {
    //     totalSend += sendToUnity[i] + (i == 5? "": ",");
    // }
    // totalSend[totalSend.length() - 1] = '\0';

    // if (server.sendString(totalSend) == -1) {
    //     // client has disconnected
    //     server.stop();
    //     server = SocketServer(9001);
    // }

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

    // glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);


    if (context->isPlayerOne) {
        for (unsigned int i = 0; i < this->entities.size(); i += 1) {
            this->entities[i]->render();
        }
    }
	/*else {
        for (unsigned int i = this->entities.size() - 1; i >= 0; i -= 1) {
            this->entities[i]->render();
        }
    }*/
}

void GameState::addEntity(Entity *entity) {
    this->entities.push_back(entity);
    cout << "added " << entity->name << endl;
    entity->setCollection(&this->entities);
    entity->gameState = this;
}

