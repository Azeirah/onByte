#include "Game.h"
#include "demoMode/DemoMode.h"
#include "GameState.h"

int main() {
    Game game;
    DemoMode * testGame = new DemoMode("test");

    game.addGameMode(testGame);
    game.switchToGameState("test");
    game.startGameLoop();

    return 0;
}
