#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <deque>
#include <conio.h>
#include "point.h"
#include "tools.h"
#include "food.h"

class Food;
class Snake
{
public:    
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Snake();

    void InitSnake();
    void Move();
    void NormalMove();
    bool OverEdge();
    bool HitSelf();
    bool ChangeDirection();
    bool GetFood(Food &food);
    bool GetBigFood(Food &food);

private:
    std::deque<Point> snake;    // 双端队列，一种容器，可以在队列的两端快速地插入或删除元素。
    Direction direction;
    friend class Food;  //将Food类置为友元，以便访问其私有元素 
};


#endif // SNAKE_H