#include "DemoMode.h"

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

// DemoMode::DemoMode(string name) {
//     Ball         ball{};
//     GameField    field{};
//     Bat          player1(-fielddepth, red,   1);
//     Bat          player2(fielddepth,  green, 2);
//     BallFollower follow{};

//     this->name = name;

//     this->addEntity((Entity *) &field);
//     this->addEntity((Entity *) &player1);
//     this->addEntity((Entity *) &ball);
//     this->addEntity((Entity *) &player2);
//     this->addEntity((Entity *) &follow);
// }
