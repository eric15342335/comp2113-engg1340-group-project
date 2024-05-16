/// @file draw.h
/// Function declarations for drawing/display of various elements
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