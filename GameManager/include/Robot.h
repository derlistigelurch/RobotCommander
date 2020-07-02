#ifndef GAMEMANAGER_ROBOT_H
#define GAMEMANAGER_ROBOT_H


#include <string>

#include "Point.h"
#include "Directions.h"

class Robot
{
public:
    Robot(int id, std::string name, char symbol, Point *position);

    virtual ~Robot() = default;

    int Attack(Robot robot);

    int Move(Directions direction);

    int id;
    int attackRadius;
    int health;
    int movementSpeed;
    Point *position;
    char symbol;
    std::string name;
    std::string description;
};


#endif //GAMEMANAGER_ROBOT_H
