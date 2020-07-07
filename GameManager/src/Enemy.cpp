#include "../include/Enemy.h"

Enemy::Enemy(int id, char symbol, const std::string &name, int health, int actionPoints, int damage,
             int attackRadius, const std::string &description, Point position)
        : Robot(id, symbol, name, health, actionPoints, damage, attackRadius, description, position)
{

}