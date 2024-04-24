#ifndef CONTROLS_H
#define CONTROLS_H

#include "stock.h"

#include <vector>

void optionsInput(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks);

int integerInput(int row, int col, std::string message);

void buyStocks(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks);

void sellStocks(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks);

void quitConfirmation(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks);

#endif