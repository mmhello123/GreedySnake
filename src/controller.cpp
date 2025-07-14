#include "controller.h"

// 开始界面
void Controller::ShowStartUI()
{
    SetWindowSizeAndTitle(41, 32); // 设置窗口大小
    SetColor(2);                   // 设置开始动画颜色
    StartInterface start;
    start.Action(); // 开始界面

    /*设置关标位置，并输出提示语，等待任意键输入结束*/
    SetCursorPosition(13, 26);
    std::cout << "按任意键开始游戏... " ;
    SetCursorPosition(13, 27);
    system("pause");
}

// 选择界面
void Controller::ShowModeSelectUI()
{
    /*初始化界面选项*/
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          ";
    SetCursorPosition(13, 27);
    std::cout << "                               ";
    SetCursorPosition(6, 21);
    //std::cout << "请选择游戏难度：";
    SetCursorPosition(6, 22);
    std::cout << "(上下键选择,回车确认)";

    // 默认选择简单模式
    key = 1;
    showModeSelectionText(key);
    score = 0;

    // 选择难度
    int ch;
    bool isPressEnter = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        // 上方向键
        case 72:
            if (key == 1)
                key = 4;
            else
                --key;
            showModeSelectionText(key);
            break;

        // 下方向键
        case 80:
            if (key == 4)
                key = 1;
            else
                ++key;
            showModeSelectionText(key);
            break;

        // 回车键
        case 13:
            isPressEnter = true;
            break;

        default:
            break;
        }

        if (isPressEnter)
            break;

        SetCursorPosition(0, 31); // 将光标置于左下角，避免关标闪烁影响游戏体验
    }

    // 根据用户选择设置难度
    updateDifficultyByKey(key);
}

// 绘制游戏界面
void Controller::DrawGame()
{
    system("cls"); // 清屏

    /*绘制地图*/
    SetColor(3);
    Map init_map;
    init_map.PrintInitmap();

    /*绘制侧边栏*/
    SetColor(3);
    SetCursorPosition(34, 10);
    std::cout << "Greedy Snake（贪吃蛇）";
    SetCursorPosition(34, 12);
    std::cout << "难度：";
    SetCursorPosition(38, 12);
    switch (key)
    {
    case 1:
        std::cout << "简单模式";
        break;
    case 2:
        std::cout << "普通模式";
        break;
    case 3:
        std::cout << "困难模式";
        break;
    case 4:
        std::cout << "炼狱模式";
        break;
    default:
        break;
    }

    SetCursorPosition(34, 14);
    std::cout << "得分：";
    SetCursorPosition(39, 14);
    std::cout << "     0";
    SetCursorPosition(34, 16);
    std::cout << "操作：方向键移动";
    SetCursorPosition(34, 18);
    std::cout << "ESC键暂停";
}

// 游戏二级循环
int Controller::PlayGame()
{
    Snake csnake;
    Food cfood;

    SetColor(6);
    csnake.InitSnake();

    // 设置随机数种子，如果没有 食物的出现位置将会固定
    srand((unsigned)time(NULL));
    cfood.DrawFood(csnake);

    while (!csnake.OverEdge() && !csnake.HitSelf())
    {
        // 玩家按下Esc键，暂停游戏
        if (!csnake.ChangeDirection())
        {
            int choice = ShowMenu();
            if (choice != 1) return choice;
        }

        if (cfood.GetBigFlag()) cfood.FlashBigFood();

        // 吃到普通食物
        if (csnake.GetFood(cfood))
        {

            csnake.Move();  // 蛇增长
            UpdateScore(1); // 更新分数，1为分数权重
            RewriteScore(); // 重绘分数
            cfood.DrawFood(csnake);   //绘制新食物
        }
        else csnake.NormalMove();

        // 吃到限时食物
        if (csnake.GetBigFood(cfood))
        {
            csnake.Move();  // 蛇增长
            UpdateScore(cfood.GetProgressBar()/5); // 分数根据限时食物进度条确定
            RewriteScore(); // 重绘分数
        }

        Sleep(speed);   //制造蛇的移动效果
    }

    return GameOver(); // 游戏结束
}

// 更新分数
void Controller::UpdateScore(const int &scoreWeight)
{
    score += key * 10 * scoreWeight;
}

// 重绘分数
void Controller::RewriteScore()
{
    SetCursorPosition(39, 14);
    SetColor(11);
    std::cout << std::setw(6) << std::setfill(' ') << score; // 输出："   123"
}

// 选择菜单
int Controller::ShowMenu()
{
    int choice = 1;
    SetColor(11);
    SetCursorPosition(34, 20);
    std::cout << "菜单：";
    showMenuText(choice);

    int ch;
    bool isPressEnter = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 72:
            if (choice == 1)
                choice = 3;
            else
                --choice;
            showMenuText(choice);
            break;

        case 80:
            if (choice == 3)
                choice = 1;
            else
                ++choice;
            showMenuText(choice);
            break;

        case 13:
            isPressEnter = true;
            break;

        default:
            break;
        }

        if (isPressEnter)
            break;
        SetCursorPosition(0, 31);
    }

    if (choice == 1)
        clearMenuText();
    return choice;
}

// 游戏结束界面
int Controller::GameOver()
{
    Sleep(500);
    SetColor(11);
    SetCursorPosition(5, 8);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    Sleep(30);
    SetCursorPosition(4, 9);
    std::cout << " ┃               Game Over !!!              ┃";
    Sleep(30);
    SetCursorPosition(4, 10);
    std::cout << " ┃                                          ┃";
    Sleep(30);
    SetCursorPosition(4, 11);
    std::cout << " ┃              很遗憾！你挂了              ┃";
    Sleep(30);
    SetCursorPosition(4, 12);
    std::cout << " ┃                                          ┃";
    Sleep(30);
    SetCursorPosition(4, 13);
    std::cout << " ┃             你的分数为：                 ┃";
    SetCursorPosition(19, 13);
    std::cout << score;
    Sleep(30);
    SetCursorPosition(4, 14);
    std::cout << " ┃                                          ┃";
    Sleep(30);
    SetCursorPosition(4, 15);
    std::cout << " ┃    是否再来一局？                        ┃";
    Sleep(30);
    SetCursorPosition(4, 16);
    std::cout << " ┃                                          ┃";
    Sleep(30);
    SetCursorPosition(4, 17);
    std::cout << " ┃                                          ┃";
    Sleep(30);
    SetCursorPosition(4, 18);
    std::cout << " ┃    嗯，好的        不了，还是学习有意思  ┃";
    Sleep(30);
    SetCursorPosition(4, 19);
    std::cout << " ┃                                          ┃";
    Sleep(30);
    SetCursorPosition(4, 20);
    std::cout << " ┃                                          ┃";
    Sleep(30);
    SetCursorPosition(5, 21);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

    Sleep(100);
    SetCursorPosition(7, 18);
    SetBackColor();
    std::cout << "嗯，好的";
    SetCursorPosition(0, 31);

    int ch;
    int choice = 1;
    bool isPressEnter = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        // left
        case 75:
            if (choice == 1) choice = 2;
            else --choice;
            showGameOverText(choice);
            break;

        // right
        case 77:
            if (choice == 2) choice = 1;
            else ++choice;
            showGameOverText(choice);
            break;

        case 13://Enter
            isPressEnter = true;
            break;

        default:
            break;
        }

        if (isPressEnter) break;
        SetCursorPosition(0, 31);
    }

    SetColor(11);
    return choice;
}

// 进行游戏
void Controller::Game()
{
    SetConsoleOutputCP(65001);  // 设置控制台输出为UTF-8
    ShowStartUI();    // 显示开始界面
    
    while (true)
    {
        if (!isRestartGame) ShowModeSelectUI();
        DrawGame();

        int choice = PlayGame();
        // 重新开始
        if (choice == 2) isRestartGame = true;
        // 退出至菜单
        if (choice == 3) isRestartGame = false;
        
        // 清屏
        system("cls");
        continue;
    }
}


void Controller::showModeSelectionText(int level)
{
    switch (key)
    {
    case 1:
        SetCursorPosition(27, 22);
        SetBackColor();
        std::cout << "简单模式";
        SetCursorPosition(27, 24);
        SetColor(3);
        std::cout << "普通模式";
        SetCursorPosition(27, 26);
        SetColor(3);
        std::cout << "困难模式";
        SetCursorPosition(27, 28);
        SetColor(3);
        std::cout << "炼狱模式";
        break;

    case 2:
        SetCursorPosition(27, 22);
        SetColor(3);
        std::cout << "简单模式";
        SetCursorPosition(27, 24);
        SetBackColor();
        std::cout << "普通模式";
        SetCursorPosition(27, 26);
        SetColor(3);
        std::cout << "困难模式";
        SetCursorPosition(27, 28);
        SetColor(3);
        std::cout << "炼狱模式";
        break;

    case 3:
        SetCursorPosition(27, 22);
        SetColor(3);
        std::cout << "简单模式";
        SetCursorPosition(27, 24);
        SetColor(3);
        std::cout << "普通模式";
        SetCursorPosition(27, 26);
        SetBackColor();
        std::cout << "困难模式";
        SetCursorPosition(27, 28);
        SetColor(3);
        std::cout << "炼狱模式";
        break;

    case 4:
        SetCursorPosition(27, 22);
        SetColor(3);
        std::cout << "简单模式";
        SetCursorPosition(27, 24);
        SetColor(3);
        std::cout << "普通模式";
        SetCursorPosition(27, 26);
        SetColor(3);
        std::cout << "困难模式";
        SetCursorPosition(27, 28);
        SetBackColor();
        std::cout << "炼狱模式";
        break;

    default:
        break;
    }
}

// 根据用户选择设置难度，speed值越小，速度越快
void Controller::updateDifficultyByKey(int level)
{
    switch (key)
    {
    case 1:
        speed = 135;
        break;
    case 2:
        speed = 100;
        break;
    case 3:
        speed = 60;
        break;
    case 4:
        speed = 30;
        break;
    default:
        break;
    }
}

// 显示菜单界面
void Controller::showMenuText(int choice)
{
    switch (choice)
    {
    case 1:
        SetCursorPosition(38, 22);
        SetBackColor();
        std::cout << "继续游戏";
        SetCursorPosition(38, 24);
        SetColor(3);
        std::cout << "重新开始";
        SetCursorPosition(38, 26);
        SetColor(3);
        std::cout << "退出游戏";
        break;

    case 2:
        SetCursorPosition(38, 22);
        SetColor(3);
        std::cout << "继续游戏";
        SetCursorPosition(38, 24);
        SetBackColor();
        std::cout << "重新开始";
        SetCursorPosition(38, 26);
        SetColor(3);
        std::cout << "退出游戏";
        break;

    case 3:
        SetCursorPosition(38, 22);
        SetColor(3);
        std::cout << "继续游戏";
        SetCursorPosition(38, 24);
        SetColor(3);
        std::cout << "重新开始";
        SetCursorPosition(38, 26);
        SetBackColor();
        std::cout << "退出游戏";
        break;
    }
}

// 清除菜单界面
void Controller::clearMenuText()
{
    SetCursorPosition(38, 18);
    std::cout << "          ";
    SetCursorPosition(38, 20);
    std::cout << "          ";
    SetCursorPosition(38, 22);
    std::cout << "          ";
}

// 清除菜单界面
void Controller::showGameOverText(int choice)
{
    switch (choice)
    {
    case 1:
        SetCursorPosition(7, 18);
        SetBackColor();
        std::cout << "嗯，好的";
        SetCursorPosition(15, 18);
        SetColor(11);
        std::cout << "不了，还是学习有意思";
        break;

    case 2:
        SetCursorPosition(7, 18);
        SetColor(11);
        std::cout << "嗯，好的";
        SetCursorPosition(15, 18);
        SetBackColor();
        std::cout << "不了，还是学习有意思";
        break;

    default:
        break;
    }
}
