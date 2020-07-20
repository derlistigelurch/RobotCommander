#ifndef GAMEMANAGER_ROBOT_H
#define GAMEMANAGER_ROBOT_H


#include <string>

#include "Point.h"
#include "Directions.h"
#include "Map.h"

class Robot
{
public:
    Robot(int id, char symbol, const std::string &name, int health, int actionPoints, int damage,
          int attackRadius, const std::string &description, Point position, const std::string &picture);

    virtual ~Robot() = default;

    virtual void Attack(Robot *robot, int dmg) const;

    virtual void Move(Directions direction, int movementCost);

    int GetDamage() const;

    bool IsInRange(Robot *robot) const;

    int id;
    int attackRadius;
    int health;
    int currentHealth;
    int actionPoints;
    int currentActionPoints;

    int damage;

    char symbol;

    Point position;

    std::string name;
    std::string description;
    std::string picture;

    static const int DESTROYED = 36;
};


#endif //GAMEMANAGER_ROBOT_H
