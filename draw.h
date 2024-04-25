#ifndef DRAW_H
#define DRAW_H

#include <string>

void drawLogo(int row, int col);

void drawRoundInfo(int row, int col, int round, float balance, std::string player, float indexHSI);

void drawEventBar(int row, int col);

void listEvents(int row, int col);

void drawButton(int row, int col);

#endif