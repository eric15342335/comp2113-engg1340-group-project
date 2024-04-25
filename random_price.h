/**
 * @file random_price.h
 * @brief Header file for random related functions.
 * @author 84ds84d8s
 */

#ifndef RANDOM_PRICE_H
#define RANDOM_PRICE_H

#include "events.h"
#include "stock.h"

/// @brief Multiplier for mean
const float meanMultiplier = 0.05;

/// @brief Multiplier for standard deviation
const float sdMultiplier = 3.0;

/// @brief Lower limit multiplier
const float lowerLimitMultiplier = 0.2;

/// @brief Upper limit multiplier
const float upperLimitMultiplier = 0.2;

/// @brief Default lower limit
const float defaultLowerLimit = -5/lowerLimitMultiplier;

/// @brief Default upper limit
const float defaultUpperLimit = 5/upperLimitMultiplier;

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
 * @brief Get the processed modifiers for the stock.
 * @param stock the stock to get the processed modifiers
 * @return the processed modifiers
 * @note the values of the processed modifiers are final values that will be used to
 * calculate the percentage change of the stock price
 */
std::map<stock_modifiers, float> getProcessedModifiers(Stock & stock);

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
