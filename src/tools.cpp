#include "tools.h"

void SetWindowSizeAndTitle(int cols, int lines)
{
    //SetConsoleTitleW(L"贪吃蛇"); // 设置窗口标题
    std::string cmd = std::format("mode con cols={} lines={}", cols * 2, lines);    //  一个图形■占两个字符，故宽度乘以2
    system(cmd.c_str());    //  system(mode con cols=88 lines=88)设置cmd.exe窗口宽度和高度   
}

// 设置光标位置
void SetCursorPosition(const int x, const int y)
{
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

//设置文本颜色
void SetColor(int colorID)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

//设置文本背景色
void SetBackColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                            BACKGROUND_BLUE |
                            BACKGROUND_GREEN |
                            BACKGROUND_RED );
}
