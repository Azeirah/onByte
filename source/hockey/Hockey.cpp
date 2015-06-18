#include "Hockey.h"

namespace hockey {
    Hockey::Hockey(string name) {
        Ball         * ball         = new Ball{};
        GameField    * field        = new GameField{};
        Bat          * player1_bat1 = new Bat( fielddepth       , red  , 1);
        Bat          * player1_bat2 = new Bat( fielddepth - 0.5f, red  , 1);
        Bat          * player2_bat1 = new Bat(-fielddepth      ,  green, 1);
        Bat          * player2_bat2 = new Bat(-fielddepth + 0.5f, green, 1);
        BallFollower * follow       = new BallFollower{};

        this->name = name;

        this->addEntity(field);
        this->addEntity(player1_bat1);
        this->addEntity(player1_bat2);
        this->addEntity(ball);
        this->addEntity(player2_bat1);
        this->addEntity(player2_bat2);
        this->addEntity(follow);
    }
}
