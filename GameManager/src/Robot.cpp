#include "../include/Robot.h"

Robot::Robot(int id, std::string name, char symbol, Point *position)
{
    this->id = id;
    this->name = name;
    this->symbol = symbol;
    this->position = position;
}

int Robot::Attack(Robot robot)
{
    return 0;
}

int Robot::Move(Directions direction)
{
    return 0;
}
