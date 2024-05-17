/// @file controls.h
/// (Declarations of) human-computer interactions functions.
/*
This program is free software: you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this
program. If not, see <https://www.gnu.org/licenses/>.
*/

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
    std::vector<Stock> & stocks, const std::vector<Stock_event> & events,
    bool & viewMode, bool & advance, bool & overlayEvent, bool & flush,
    bool & gameQuit);

int integerInput(int row, int col, const std::string & message);

void buyStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & flush);

void sellStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & flush);

void toggleView(bool & viewMode, bool & flush);

void advanceConfirmation(int row, int col, bool & advance, bool & flush);

void quitConfirmation(int row, int col, bool & flush, bool & gameQuit);

#endif