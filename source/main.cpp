#include "Game.h"
#include "demoMode/DemoMode.h"
#include "handbal/Handbal.h"
#include "hockey/Hockey.h"
#include "GameState.h"
#include "globals.h"

int main(int argc, char const *argv[]) {
	Game game;
	demo::DemoMode *testGame = new demo::DemoMode("demo");
	handbal::Handbal  *handbal  = new handbal::Handbal("handbal");
    hockey::Hockey *hockey = new hockey::Hockey("hockey");

    game.addGameMode(handbal);
    game.addGameMode(testGame);
    game.addGameMode(hockey);

    game.switchToGameState("handbal");
    game.startGameLoop();

    return 0;
}
