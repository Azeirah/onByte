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
    // copy the input to prevent any kinds of weird thread memory read/write violations.
    vector<string> inputCopy;

    for (unsigned int i = 0; i < input.size(); i++) {
        inputCopy.push_back(string(input[i], strlen(input[i])));
    }

    // clear game's input buffer after copying everything inside it.

    context->makeCurrent();

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
}

void GameState::render(ESContext *context, int eye) {
    float aspect;
    ESMatrix perspective;
    ESMatrix modelview = mvpMatrix;

    aspect = (GLfloat) context->window_width / (GLfloat) context->window_height;


    esMatrixLoadIdentity(&perspective);
           esPerspective(&perspective, 50.0f, aspect, 1.0f, 10.0f);
    esMatrixLoadIdentity(&modelview);
             // esTranslate(&modelview, 0.0, 0.0, -5.0);

    if (eye == -1) {
        esTranslate(&modelview, -halfEyeWidth, 0.0, -5.0);
    } else if (eye == 1) {
        esTranslate(&modelview, halfEyeWidth, 0.0, -5.0);
    } else {
        esTranslate(&modelview, 0.0, 0.0, -5.0);
    }

    esMatrixMultiply(&mvpMatrix, &modelview, &perspective);

    if (eye == 1) {
        glColorMask(false, true, true, false);
    } else if (eye == -1) {
        glColorMask(true, false, false, false);
    }

    glViewport(0, 0, context->window_width, context->window_height);
    glClear(GL_COLOR_BUFFER_BIT);

    for (unsigned int i = 0; i < this->entities.size(); i += 1) {
        this->entities[i]->render();
    }
}

void GameState::addEntity(Entity *entity) {
    this->entities.push_back(entity);
    cout << "added " << entity->name << endl;
    entity->setCollection(&this->entities);
    entity->gameState = this;
}

