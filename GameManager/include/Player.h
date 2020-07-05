#ifndef GAMEMANAGER_PLAYER_H
#define GAMEMANAGER_PLAYER_H


#include "Robot.h"

class Player : public Robot
{
public:
    Player() = default;

    Player(int id, char symbol, const std::string& name, int health, int movementSpeed, int damage, int attackRadius,
           const std::string& description);

    ~Player();
};


#endif //GAMEMANAGER_PLAYER_H
