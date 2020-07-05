#include "../include/Player.h"

Player::Player(int id, char symbol, const std::string &name, int health, int movementSpeed, int damage,
               int attackRadius, const std::string &description)
        : Robot(id, symbol, name, health, movementSpeed, damage, attackRadius, description)
{

}

Player::~Player()
{
    delete this->position;
}