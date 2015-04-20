#include "onByte.h"

enum GameState {
    TEST,
    MAIN_MENU,
    SETTINGS
};

// Game is the startpoint for the whole game project
// It contains the main game loop as well as the current game state
// The game state can be used to switch from the menu to the settings or a gamemode
// The game loop renders and updates all components for both screens
class Game {
  private:
    GameState gameState;
    ESContext context1;
    ESContext context2;
  public:
    Game();

    void switchToGameState(GameState);
    void startGameLoop();
};