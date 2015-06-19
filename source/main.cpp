#include "Game.h"
#include "demoMode/DemoMode.h"
#include "handbal/Handbal.h"
#include "GameState.h"
#include "globals.h"

int main(int argc, char const *argv[]) {
	Game game;
	demo::DemoMode *testGame = new demo::DemoMode("demo");
	handbal::Handbal  *handbal  = new handbal::Handbal("handbal");

    game.addGameMode(handbal);
    game.addGameMode(testGame);

    game.switchToGameState("handbal");
    game.startGameLoop();

    return 0;
}
