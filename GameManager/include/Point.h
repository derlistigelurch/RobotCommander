#ifndef GAMEMANAGER_POINT_H
#define GAMEMANAGER_POINT_H


class Point
{
public:
    Point(int x, int y);

    ~Point() = default;

    Point operator+(const Point &point) const;

    Point operator-(const Point &point) const;

    Point operator+(const int &number) const;

    Point operator-(const int &number) const;

    int x;
    int y;

};


#endif //GAMEMANAGER_POINT_H