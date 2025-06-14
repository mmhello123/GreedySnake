#include "startInterface.h"

StartInterface::StartInterface() : speed(35)
{
    startsnake.emplace_back(Point(0, 14)); // Éß
    startsnake.emplace_back(Point(1, 14));
    startsnake.emplace_back(Point(2, 15));
    startsnake.emplace_back(Point(3, 16));
    startsnake.emplace_back(Point(4, 17));
    startsnake.emplace_back(Point(5, 18));
    startsnake.emplace_back(Point(6, 17));
    startsnake.emplace_back(Point(7, 16));
    startsnake.emplace_back(Point(8, 15));
    startsnake.emplace_back(Point(9, 14));

    textsnake.emplace_back(Point(-26, 14)); // S
    textsnake.emplace_back(Point(-25, 14));
    textsnake.emplace_back(Point(-27, 15));
    textsnake.emplace_back(Point(-26, 16));
    textsnake.emplace_back(Point(-25, 17));
    textsnake.emplace_back(Point(-27, 18));
    textsnake.emplace_back(Point(-26, 18));

    textsnake.emplace_back(Point(-23, 14)); // N
    textsnake.emplace_back(Point(-23, 15));
    textsnake.emplace_back(Point(-23, 16));
    textsnake.emplace_back(Point(-23, 17));
    textsnake.emplace_back(Point(-23, 18));
    textsnake.emplace_back(Point(-22, 15));
    textsnake.emplace_back(Point(-21, 16));
    textsnake.emplace_back(Point(-20, 17));
    textsnake.emplace_back(Point(-19, 14));
    textsnake.emplace_back(Point(-19, 15));
    textsnake.emplace_back(Point(-19, 16));
    textsnake.emplace_back(Point(-19, 17));
    textsnake.emplace_back(Point(-19, 18));

    textsnake.emplace_back(Point(-17, 18)); // A
    textsnake.emplace_back(Point(-16, 17));
    textsnake.emplace_back(Point(-15, 16));
    textsnake.emplace_back(Point(-14, 15));
    textsnake.emplace_back(Point(-14, 16));
    textsnake.emplace_back(Point(-13, 14));
    textsnake.emplace_back(Point(-13, 16));
    textsnake.emplace_back(Point(-12, 15));
    textsnake.emplace_back(Point(-12, 16));
    textsnake.emplace_back(Point(-11, 16));
    textsnake.emplace_back(Point(-10, 17));
    textsnake.emplace_back(Point(-9, 18));

    textsnake.emplace_back(Point(-7, 14)); // K
    textsnake.emplace_back(Point(-7, 15));
    textsnake.emplace_back(Point(-7, 16));
    textsnake.emplace_back(Point(-7, 17));
    textsnake.emplace_back(Point(-7, 18));
    textsnake.emplace_back(Point(-6, 16));
    textsnake.emplace_back(Point(-5, 15));
    textsnake.emplace_back(Point(-5, 17));
    textsnake.emplace_back(Point(-4, 14));
    textsnake.emplace_back(Point(-4, 18));

    textsnake.emplace_back(Point(-2, 14)); // E
    textsnake.emplace_back(Point(-2, 15));
    textsnake.emplace_back(Point(-2, 16));
    textsnake.emplace_back(Point(-2, 17));
    textsnake.emplace_back(Point(-2, 18));
    textsnake.emplace_back(Point(-1, 14));
    textsnake.emplace_back(Point(-1, 16));
    textsnake.emplace_back(Point(-1, 18));
    textsnake.emplace_back(Point(0, 14));
    textsnake.emplace_back(Point(0, 16));
    textsnake.emplace_back(Point(0, 18));
}

void StartInterface::PrintFirst()
{
    for (auto& point : startsnake)
    {
        point.Print();
        Sleep(speed);
    }
}

//  蛇从左向右移动的过程
void StartInterface::PrintSecond()
{
    for (int i = 10; i != 40; ++i) //蛇头需要从10移动到40
    {
        /*计算蛇头的下一个位置，并将其压入startsnake中，绘制出来，将蛇尾去掉*/
        int j = ( ((i-2)%8) < 4 )?( 15 + (i-2)%8 ) : ( 21 - (i-2)%8 );
        startsnake.emplace_back( Point(i, j) );
        startsnake.back().Print();
        startsnake.front().Clear();
        startsnake.pop_front();
        Sleep(speed);
    }
}

void StartInterface::PrintThird()//蛇从接触右边到消失的过程
{
    while ( !startsnake.empty() || textsnake.back().GetX() < 33 ) //当蛇还没消失或文字没移动到指定位置
    {
        if ( !startsnake.empty() ) //如果蛇还没消失，继续移动
        {
            startsnake.front().Clear();
            startsnake.pop_front();
        }
        ClearText();//清除已有文字
        PrintText();//绘制更新位置后的文字
        Sleep(speed);
    }
}

void StartInterface::PrintText()
{
    for (auto& point : textsnake)
    {
        if (point.GetX() >= 0)
            point.Print();
    }
}

void StartInterface::ClearText()
{
    for (auto& point : textsnake) //清除的同时将文字整体向右移动一格
    {
        if (point.GetX() >= 0)
            point.Clear();
        point.ChangePosition(point.GetX() + 1, point.GetY());
    }
}

void StartInterface::Action()
{
    PrintFirst();
    PrintSecond();
    PrintThird();
}