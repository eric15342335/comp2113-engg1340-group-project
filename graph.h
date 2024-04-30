/**
 * @file graph.h
 * @brief This file contains the definition of the function that will plot the graph of
 * the stock price history.
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
