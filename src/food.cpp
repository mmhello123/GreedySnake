#include "food.h"

// 画食物
void Food::DrawFood(Snake& csnake)
{
    while (true)
    {
        int tmp_x = rand() % 30;
        int tmp_y = rand() % 30;
        if(tmp_x < 2) tmp_x += 2;
        if(tmp_y < 2) tmp_y += 2;

        bool is_food_ok = true;
        Point point_food(tmp_x, tmp_y);
        Point point_big_food(big_x, big_y);
        // 当前食物与特殊食物重合时重新生成
        if (point_food == point_big_food) continue;
        // 当前食物与蛇身重合时重新生成
        for (auto point : csnake.snake)
        {
            if (point == point_food)
            {
                is_food_ok = false;
                break;
            }
        }

        if (!is_food_ok) continue;

        x = tmp_x;
        y = tmp_y;
        SetCursorPosition(x, y);
        SetColor(13);
        //std::cout << "★";
        ++cnt;
        cnt %= 5;

        if (cnt == 0) DrawBigFood(csnake);
        break;
    }
}

void Food::DrawBigFood(Snake& csnake)
{
    SetCursorPosition(5, 0);
    SetColor(11);
    std::cout << "------------------------------------------" ;//进度条
    progress_bar = 42;

    while (true)
    {
        int tmp_x = rand() % 30;
        int tmp_y = rand() % 30;
        if(tmp_x < 2) tmp_x += 2;
        if(tmp_y < 2) tmp_y += 2;

        bool is_big_food_ok = true;
        Point point_food = Point(tmp_x, tmp_y);
        Point point_big_food = Point(big_x, big_y);
        // 当前食物与特殊食物重合时重新生成
        if (point_food == point_big_food) continue;
        // 当前食物与蛇身重合时重新生成
        for (auto point : csnake.snake)
        {
            if (point == point_food)
            {
                is_big_food_ok = false;
                break;
            }
        }

        if (!is_big_food_ok) continue;

        big_x = tmp_x;
        big_y = tmp_y;
        SetCursorPosition(big_x, big_y);
        SetColor(18);
        //std::cout << "■" ;
        big_flag = true;
        flash_flag = true;
        break;
    }
}

int Food::GetCnt()
{
    return cnt;
}

// 闪烁限时食物
void Food::FlashBigFood()
{
    SetCursorPosition(big_x, big_y);
    SetColor(18);
    if (flash_flag)
    {
        std::cout << "  ";
        flash_flag = false;
    }
    else
    {
        //std::cout << "■" ;
        flash_flag = true;
    }

    SetCursorPosition(26, 0);
    SetColor(11);
    // 进度条缩短
    for (int i = 42; i >= progress_bar; --i) std::cout << "\b \b" ;
    --progress_bar;
    if (progress_bar == 0) {
        SetCursorPosition(big_x, big_y);
        std::cout << "  " ;
        big_flag = false;
        big_x = 0;
        big_y = 0;
    }
}

bool Food::GetBigFlag()
{
    return big_flag;
}

int Food::GetProgressBar()
{
    return progress_bar;
}
