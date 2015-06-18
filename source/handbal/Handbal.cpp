#include "Handbal.h"

namespace handbal {
    Handbal::Handbal(string name) {
        Ball         * ball    = new Ball();
        GameField    * field   = new GameField();
        Bat          * player1 = new Bat(fielddepth, red, 1);
        BallFollower * follow  = new BallFollower();

        this->name = name;

        this->addEntity(field);
        this->addEntity(ball);
        this->addEntity(player1);
        this->addEntity(follow);
    }
}
