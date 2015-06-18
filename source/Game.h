#pragma once

#include <map>
#include "onByte.h"
#include "ESContext.h"
#include "GameState.h"
// for framerate and dt
#include <sys/time.h>

#include "Text.h"

// for socket server, used for input
#include "server/server.h"
#include <vector>
#include <thread>

class GameState;

// Game is the startpoint for the whole game project
// It contains the main game loop as well as the current game state
// The game state can be used to switch from the menu to the settings or a gamemode
// The game loop renders and updates all components for both screens
class Game {
  private:
    GameState*     currentState;
    string         currentStateName;
    ESContext*     context1;
    SocketServer*  channel;
    vector<char *> inputBuffer;

    void receiveInput();
    void clearInputBuffer();
  public:
  	map<string, GameState *> gameStates;
    Game();

    void addGameMode(GameState*);
    void switchToGameState(string);
    void startGameLoop();
};
