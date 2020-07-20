#ifndef GAMEMANAGER_ENEMY_H
#define GAMEMANAGER_ENEMY_H


#include "Robot.h"
#include "Map.h"

class Enemy : public Robot
{
public:
    Enemy(int id, char symbol, const std::string &name, int health, int actionPoints, int damage, int attackRadius,
          const std::string &description, Point position, const std::string &picture);

    ~Enemy() = default;

    void GetPathToPlayer(Robot *enemy, Map *map);
};


#endif //GAMEMANAGER_ENEMY_H
