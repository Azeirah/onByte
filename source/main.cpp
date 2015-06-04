#include "Game.h"
#include "TestGame.h"
#include "GameState.h"

int main() {
    Game game;
    TestGame *testGame = new TestGame("test");

    game.addGameMode(testGame);
    game.switchToGameState("test");
    game.startGameLoop();

    return 0;
}
