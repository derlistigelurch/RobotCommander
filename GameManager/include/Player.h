#ifndef GAMEMANAGER_PLAYER_H
#define GAMEMANAGER_PLAYER_H


#include "Robot.h"

class Player : public Robot
{
    Player(int id, std::string name, char symbol, Point *position);


};


#endif //GAMEMANAGER_PLAYER_H
