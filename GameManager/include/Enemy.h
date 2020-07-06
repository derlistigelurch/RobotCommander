#ifndef GAMEMANAGER_ENEMY_H
#define GAMEMANAGER_ENEMY_H


#include "Robot.h"

class Enemy : public Robot
{
public:
    Enemy(int id, char symbol, const std::string &name, int health, int movementSpeed, int damage, int attackRadius,
          const std::string &description, Point position);

    ~Enemy() = default;
};


#endif //GAMEMANAGER_ENEMY_H
