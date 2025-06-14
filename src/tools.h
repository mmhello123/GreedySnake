#ifndef TOOLS_H
#define TOOLS_H

#include <Windows.h>
#include <string>
#include <format>

void SetWindowSizeAndTitle(int cols, int lines);
void SetCursorPosition(const int x, const int y);
void SetColor(int colorID);
void SetBackColor();

#endif // TOOLS_H