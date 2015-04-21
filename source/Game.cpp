#include "Game.h"

Game::Game() {
    // player 1
    this->context1 = new ESContext(true);

    // // player 2
    this->context2 = new ESContext(false);

    this->context1->createWindow(SCREENNAME1, SCREENWIDTH, SCREENHEIGHT, ES_WINDOW_ALPHA);
    this->context2->createWindow(SCREENNAME2, SCREENWIDTH, SCREENHEIGHT, ES_WINDOW_ALPHA);

    this->context1->makeCurrent();
    this->context2->makeCurrent();
}
