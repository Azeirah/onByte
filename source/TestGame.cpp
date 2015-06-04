#include "TestGame.h"

TestGame::TestGame(string name) {
    Sphere *ball         = new Sphere(10, 0.1f);
    Field *field         = new Field(1.0f);
    Bat *player1         = new Bat(1.0f, -fielddepth, red,   1);
    Bat *player2         = new Bat(1.0f,  fielddepth, green, 2);
    BallFollower *follow = new BallFollower(1.0f, &ball->position->z);

    this->name           = name;

	this->addEntity(field);
    this->addEntity(player1);
    this->addEntity(ball);
    this->addEntity(player2);
    this->addEntity(follow);

    cout << "Field:" << endl;
    field->printInfo();
    cout << endl;
    cout << "Ball:" << endl;
    ball->printInfo();
    cout << endl;
    cout << "Player1:" << endl;
    player1->printInfo();
    cout << endl;
    cout << "Player2:" << endl;
    player2->printInfo();
    cout << endl;
    cout << "follower:" << endl;
    follow->printInfo();
    cout << endl;
}
