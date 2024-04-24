/**
 * @file random_price.h
 * @brief Header file for random related functions.
 * @author 84ds84d8s
 */

#ifndef RANDOM_PRICE_H
#define RANDOM_PRICE_H

#include "stock.h"

/// @brief Multiplier for mean
const float meanMultiplier = 0.0007;

/// @brief Multiplier for standard deviation
const float sdMultiplier = 3.0;

/**
 * @brief Initialize starting stock price.
 * @details
 * | a | mean | s.d. |
 * |---|------|------|
 * | 1 | 5    | 2    |
 * | 2 | 50   | 20   |
 * | 3 | 150  | 50   |
 * @param a the profile of the stock price
 * @return the initial stock price
 */
float init_stock_price(int a);

/**
 * @brief Initialize the standard deviation of the stock price
 */
float init_sd(void);

/**
 * @brief Calculate the percentage change of the stock price.
 * @return the percentage change of the stock price
 * @param stock the stock to calculate the percentage change
 */
float percentage_change_price(Stock & stock);

/**
 * @brief python randint like function
 * @param max_integer the maximum integer + 1 that can be returned
 * @return a random integer in `[0, max_integer - 1]`
 */
unsigned int random_integer(unsigned int max_integer);

#endif
