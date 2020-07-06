#include "../include/Enemy.h"

Enemy::Enemy(int id, char symbol, const std::string &name, int health, int movementSpeed, int damage,
             int attackRadius, const std::string &description, Point position)
        : Robot(id, symbol, name, health, movementSpeed, damage, attackRadius, description, position)
{

}