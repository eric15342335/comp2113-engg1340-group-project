#ifndef DRAW_H
#define DRAW_H

#include "format.h"
#include "stock.h"

#include <iostream>
#include <string>
#include <tuple> // for std::ignore
#include <vector>

void drawLogo(int row, int col);

void drawRoundInfo(
    int row, int col, int round, float balance, std::string player, float indexHSI);

void drawEventBar(int row, int col);

void listEvents(int row, int col, std::vector<Stock_event> events);

void drawButton(int row, int col);

#endif