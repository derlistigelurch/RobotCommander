#ifndef GAMEMANAGER_PLAYER_H
#define GAMEMANAGER_PLAYER_H


#include "Robot.h"

class Player : public Robot
{
public:
    Player(int id, char symbol, const std::string& name, int health, int actionPoints, int damage, int attackRadius,
           const std::string& description, Point position, const std::string &picture);

    ~Player() = default;
};


#endif //GAMEMANAGER_PLAYER_H
