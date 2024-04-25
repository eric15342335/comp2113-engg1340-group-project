#ifndef CONTROLS_H
#define CONTROLS_H

#include "draw.h"
#include "format.h"
#include "graph.h"
#include "stock.h"

#include <ios>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

void optionsInput(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, std::vector<Stock_event> events, bool & viewMode,
    bool & advance, bool & gameQuit, bool & optionsQuit);

int integerInput(int row, int col, std::string message);

void buyStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & optionsQuit);

void sellStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & optionsQuit);

void toggleView(bool & viewMode, bool & optionsQuit);

void advanceConfirmation(int row, int col, bool & advance, bool & optionsQuit);

void quitConfirmation(int row, int col, bool & gameQuit, bool & optionsQuit);

#endif