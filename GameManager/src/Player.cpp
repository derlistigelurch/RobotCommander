#include "../include/Player.h"

#include <utility>

Player::Player(int id, std::string name, char symbol, Point *position) : Robot(id, std::move(name), symbol, position)
{
    this->id = id;
    this->name = name;
    this->symbol = symbol;
    this->position = position;
}
