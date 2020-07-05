#include "../include/Enemy.h"

Enemy::Enemy(int id, char symbol, const std::string &name, int health, int movementSpeed, int damage,
             int attackRadius, const std::string &description)
        : Robot(id, symbol, name, health, movementSpeed, damage, attackRadius, description)
{

}

Enemy::~Enemy()
{
    delete this->position;
}
