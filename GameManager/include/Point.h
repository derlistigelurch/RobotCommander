#ifndef GAMEMANAGER_POINT_H
#define GAMEMANAGER_POINT_H

#include <string>

class Point
{
public:
    Point(int x, int y);

    ~Point() = default;

    bool operator==(const Point &point) const;

    Point operator+(const Point &point) const;

    Point operator-(const Point &point) const;

    Point operator+(const int &number) const;

    Point operator-(const int &number) const;

    std::string ToString() const;

    int x;
    int y;

};


#endif //GAMEMANAGER_POINT_H
