#ifndef CONTROLS_H
#define CONTROLS_H

#include "stock.h"

#include <vector>

void optionsInput(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks, bool& advance, bool& gameQuit, bool& optionsQuit);

int integerInput(int row, int col, std::string message);

void buyStocks(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks);

void sellStocks(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks);

void advanceConfirmation(int row, int col, bool& advance, bool& optionsQuit);

void quitConfirmation(
    int row, int col, bool& gameQuit, bool& optionsQuit);

#endif