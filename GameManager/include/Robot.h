#ifndef GAMEMANAGER_ROBOT_H
#define GAMEMANAGER_ROBOT_H


#include <string>

#include "Point.h"
#include "Directions.h"

class Robot
{
public:
    Robot(int id, char symbol, const std::string &name, int health, int actionPoints, int damage,
          int attackRadius, const std::string &description, Point position);

    virtual ~Robot() = default;

    virtual void Attack(Robot &robot) const;

    void Move(Directions direction);

    std::string ToString() const;

    int id;
    int attackRadius;
    int health;
    int actionPoints;
    int currentActionPoints;
    int damage;

    char symbol;

    Point position;

    std::string name;
    std::string description;
};


#endif //GAMEMANAGER_ROBOT_H
