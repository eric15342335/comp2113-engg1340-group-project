/**
 * @file graph.h
 * @author comet13579
 * @brief Declaration of the graph plotting function.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

/**
 * @brief Plots a graph for a given stock.
 * @param stockname The name of the stock to plot the graph for.
 * @param width The width of the graph.
 * @param height The height of the graph.
 */
void plotGraph(std::string stockname, int width, int height);

#endif
