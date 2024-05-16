/// @file random_price.h
/// Header file for random related functions.
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

#ifndef RANDOM_PRICE_H
#define RANDOM_PRICE_H

#include "events.h"
#include "stock.h"

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
std::map<stock_modifiers, float> getProcessedModifiers(Stock stock);

/**
 * @brief Calculate the percentage change of the stock price.
 * @return the percentage change of the stock price
 * @param stock the stock to calculate the percentage change
 */
float percentage_change_price(Stock stock);

/**
 * @brief python randint like function
 * @param max_integer the maximum integer + 1 that can be returned
 * @return a random integer in `[0, max_integer - 1]`
 */
unsigned int random_integer(unsigned int max_integer);

#endif
