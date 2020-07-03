#include "../include/Robot.h"

#include <utility>

Robot::Robot(int id, std::string name, char symbol, Point *position)
{
    this->id = id;
    this->name = std::move(name);
    this->symbol = symbol;
    this->position = position;
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
