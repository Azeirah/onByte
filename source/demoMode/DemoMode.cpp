#include "DemoMode.h"

namespace demo {
    DemoMode::DemoMode(string name) {
        Ball         * ball    = new Ball();
        GameField    * field   = new GameField();
        Bat          * player1 = new Bat(-fielddepth, red,   1);
        Bat          * player2 = new Bat(fielddepth,  green, 2);
        BallFollower * follow  = new BallFollower();

        this->name = name;

        this->addEntity(field);
        this->addEntity(player1);
        this->addEntity(ball);
        this->addEntity(player2);
        this->addEntity(follow);
    }
}
