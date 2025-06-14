#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iomanip>
#include "tools.h"
#include "startInterface.h"
#include "snake.h"
#include "food.h"
#include "map.h"

class Controller
{
public:
    Controller() : speed(200), key(1), score(0), isRestartGame(false) {};

    void ShowStartUI();
    void ShowModeSelectUI();
    void DrawGame();
    int  PlayGame();
    void UpdateScore(const int& scoreWeight);
    void RewriteScore();
    int  ShowMenu();
    int  GameOver();
    void Game();

private:
    void showModeSelectionText(int level);
    void updateDifficultyByKey(int level);
    void showMenuText(int choice);
    void clearMenuText();
    void showGameOverText(int choice);

private:
    int speed;
    int key;
    int score;
    bool isRestartGame;
};

#endif // CONTROLLER_H