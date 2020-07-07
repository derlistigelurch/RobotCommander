#include "../include/Point.h"

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point Point::operator+(const Point &point) const
{
    return Point(this->x + point.x, this->y + point.y);
}

Point Point::operator-(const Point &point) const
{
    return Point(this->x - point.x, this->y - point.y);
}

Point Point::operator+(const int &number) const
{
    return Point(this->x + number, this->y + number);
}

Point Point::operator-(const int &number) const
{
    return Point(this->x - number, this->y - number);
}

std::string Point::ToString() const
{
    return "(" + std::to_string(this->x)
            .append("|")
            .append(std::to_string(this->y))
            .append(")");
}
