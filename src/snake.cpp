#include "snake.h"

Snake::Snake()
{
    // 初始化蛇的长度和位置
    snake.emplace_back(Point(14, 8));
    snake.emplace_back(Point(14, 9));
    snake.emplace_back(Point(14, 10));
    direction = Direction::DOWN;
}

void Snake::InitSnake()
{
    // 初始化蛇的长度和位置
    for (auto &point : snake)
    {
        point.PrintCircular();
    }
}

void Snake::Move()
{
    switch (direction)
    {
    case Direction::UP:
        snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() - 1));
        break;

    case Direction::DOWN:
        snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() + 1));
        break;

    case Direction::LEFT:
        snake.emplace_back(Point(snake.back().GetX() - 1, snake.back().GetY()));
        break;

    case Direction::RIGHT:
        snake.emplace_back(Point(snake.back().GetX() + 1, snake.back().GetY()));
        break;

    default:
        break;
    }

    // 使蛇头的颜色和蛇身的颜色一致
    SetColor(14);
    snake.back().PrintCircular();
}

// 正常移动
void Snake::NormalMove()
{
    Move();
    snake.front().Clear();
    snake.pop_front();
}

// 超出边界
bool Snake::OverEdge()
{
    return snake.back().GetX() <= 1 ||
           snake.back().GetX() >= 30 ||
           snake.back().GetY() <= 1 ||
           snake.back().GetY() >= 30;
}

// 是否撞到自身
bool Snake::HitSelf()
{
    const Point &head = snake.back();
    for (auto it = snake.begin(); it != snake.end() - 1; ++it)
    {
        if (*it == head)
            return true;
    }
    return false;
}

// 改变方向
bool Snake::ChangeDirection()
{
    char ch;
    if (kbhit())
    {
        // 当按下方向键时，getch()先返回-32，再使用getch()才能获取方向键的值。F1~F12的值是先返回0
        ch = getch();
        switch (ch)
        {
            case -32:
            {
                ch = getch();
                switch (ch)
                {
                    case 72:
                        if (direction != Direction::DOWN) // 不能反方向走
                            direction = Direction::UP;
                        break;
                    case 80:
                        if (direction != Direction::UP)
                            direction = Direction::DOWN;
                        break;
                    case 75:
                        if (direction != Direction::RIGHT)
                            direction = Direction::LEFT;
                        break;
                    case 77:
                        if (direction != Direction::LEFT)
                            direction = Direction::RIGHT;
                        break;
                    default:
                        break;
                }
                return true;
            }

            case 27: // ESC键退出
                return false;

            default:
                return true;
        }
    }
    return true;
}

bool Snake::GetFood(Food &food)
{
    Point snake_head_point = snake.back();
    Point food_point(food.x, food.y);
    return snake_head_point == food_point;
}

bool Snake::GetBigFood(Food &food)
{
    Point snake_head_point = snake.back();
    Point food_point(food.big_x, food.big_y);
    if (snake_head_point == food_point)
    {
        SetCursorPosition(food.big_x, food.big_y);
        std::cout << "● ";
        food.big_flag = false;
        food.big_x = 0;
        food.big_y = 0;
        SetCursorPosition(1, 0);
        std::cout << "                                                            ";
        return true;
    }
    else return false;
}