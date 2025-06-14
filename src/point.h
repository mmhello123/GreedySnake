#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "tools.h"

class Point
{
public:
    Point(){};
    Point(const int x, const int y) : x(x), y(y) {};

    void Print();
    void PrintCircular();
    void Clear();
    void ChangePosition(const int x, const int y);

    bool operator==(const Point &p) const { return (this->x == p.x && this->y == p.y); }
    int GetX(){ return this->x; }
    int GetY(){ return this->y; }

private:
    int x, y;
};

#endif // POINT_H