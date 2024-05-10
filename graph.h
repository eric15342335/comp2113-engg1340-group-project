/// @file graph.h
/// @brief Declaration of graph plotting function.
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

#ifndef GRAPH_H
#define GRAPH_H
#include <string>

/** @brief Plot the graph of the stock price history to std::cout.
 * @param player the name of the player
 * @param stocknum the stock number of the stock, -1 for HSI
 * @param width the width of the graph
 * @param height the height of the graph
 */
void graph_plotting(std::string player, int stocknum, int width, int height);

#endif
