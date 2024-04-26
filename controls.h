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
    bool & advance, bool & overlayEvent, bool & gameQuit, bool & flush);

int integerInput(int row, int col, std::string message);

void buyStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & flush);

void sellStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & flush);

void toggleView(bool & viewMode, bool & flush);

void advanceConfirmation(int row, int col, bool & advance, bool & flush);

void quitConfirmation(int row, int col, bool & gameQuit, bool & flush);

#endif