#ifndef MAP_H
#define MAP_H

#include <vector>
#include "point.h"

namespace MapConstants {
    constexpr int WIDTH = 30;
    constexpr int HEIGHT = 30;
}

class Map
{
public:
    Map();
    void PrintInitmap();    //绘制初始地图

private:
    std::vector<Point> initmap;//保存初始地图
    /*Map类可自定义多种地图，只需将表示地图的各个点保存在相应的map中，并在Snake类中增加相应判断撞墙函数即可
    std::vector<Point> map1;
    std::vector<Point> map2;
    */
};

#endif // MAP_H