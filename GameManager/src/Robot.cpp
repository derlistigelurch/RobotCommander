#include <random>

#include "../include/Robot.h"

Robot::Robot(int id, char symbol, const std::string &name, int health, int actionPoints, int damage,
             int attackRadius, const std::string &description, Point position) : position(position)
{
    this->id = id;
    this->symbol = symbol;
    this->name = name;
    this->health = health;
    this->currentHealth = health;
    this->actionPoints = actionPoints;
    this->currentActionPoints = actionPoints;
    this->damage = damage;
    this->attackRadius = attackRadius;
    this->description = description;
}

int Robot::Attack(Robot *robot) const
{
    if(!this->IsInRange(robot))
    {
        return ERR_NOT_IN_RANGE;
    }

    robot->currentHealth -= this->damage;
    if(robot->currentHealth <= 0)
    {
        return DESTROYED;
    }
}

void Robot::Move(Directions direction, int movementCost)
{
    this->currentActionPoints -= movementCost;

    switch(direction)
    {
        case Directions::NORTH:
            this->position.y--;
            break;

        case Directions::EAST:
            this->position.x++;
            break;

        case Directions::SOUTH:
            this->position.y++;
            break;

        case Directions::WEST:
            this->position.x--;
            break;
    }
}

int Robot::GetDamage() const
{
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, 2);
    int amount = 0;

    for(int i = 0; i < this->damage; i++)
    {
        amount += distribution(generator);
    }

    return amount;
}

bool Robot::IsInRange(Robot *robot) const
{
    for(int i = 0; i < this->attackRadius; ++i)
    {
        if(this->position + Point(0, i) == robot->position)
        {
            return true;
        }

        if(this->position + Point(0, -i) == robot->position)
        {
            return true;
        }

        if(this->position + Point(i, 0) == robot->position)
        {
            return true;
        }

        if(this->position + Point(-i, 0) == robot->position)
        {
            return true;
        }
    }

    return false;
}
