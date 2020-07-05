#include "../include/Robot.h"

Robot::Robot(int id, char symbol, const std::string &name, int health, int movementSpeed, int damage, int attackRadius,
             const std::string &description)
{
    this->id = id;
    this->symbol = symbol;
    this->name = name;
    this->health = health;
    this->movementSpeed = movementSpeed;
    this->damage = damage;
    this->attackRadius = attackRadius;
    this->description = description;
}

void Robot::Attack(Robot &robot) const
{
    robot.health - this->damage;
}

void Robot::Move(Directions direction) const
{
    switch(direction)
    {
        case Directions::NORTH:
            this->position->y++;
            break;

        case Directions::EAST:
            this->position->x++;
            break;

        case Directions::SOUTH:
            this->position->y--;
            break;

        case Directions::WEST:
            this->position->x--;
            break;
    }
}
