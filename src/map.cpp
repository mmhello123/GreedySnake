#include "map.h"

Map::Map()
{
    for (int i = 1;i <= MapConstants::HEIGHT;i++)
    {
        for (int j = 1; j <= MapConstants::WIDTH;j++)
        {
            if (i == 1 || i == MapConstants::HEIGHT || j == 1 || j == MapConstants::WIDTH) initmap.emplace_back(Point(j, i));
        }
    }
}

// 绘制初始地图
void Map::PrintInitmap()
{
    for (auto& point : initmap)
    {
        point.Print();
        if(point.GetY() != 1 || point.GetY() != MapConstants::HEIGHT) Sleep(10);  // 调用Sleep函数可营造动画效果
    }
}    