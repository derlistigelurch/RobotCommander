#ifndef GAMEMANAGER_ENEMY_H
#define GAMEMANAGER_ENEMY_H


#include "Robot.h"

class Enemy : public Robot
{
public:
    Enemy(int id, char symbol, const std::string &name, int health, int actionPoints, int damage, int attackRadius,
          const std::string &description, Point position, const std::string &picture);

    ~Enemy() = default;
};


#endif //GAMEMANAGER_ENEMY_H
