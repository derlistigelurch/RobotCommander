#include "../include/Enemy.h"

Enemy::Enemy(int id, char symbol, const std::string &name, int health, int actionPoints, int damage,
             int attackRadius, const std::string &description, Point position, const std::string &picture)
        : Robot(id, symbol, name, health, actionPoints, damage, attackRadius, description, position, picture)
{

}