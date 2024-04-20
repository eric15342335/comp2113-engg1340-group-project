/**
 * @file random_price.h
 * @author 84ds84d8s
 * @brief Declarations of random stock price generation functions.
 */

#ifndef RANDOM_PRICE_H
#define RANDOM_PRICE_H

/*
#ifndef
#define are to prevent double include the header
*/
#include "stock.h"

/**
 * @brief Generates an initial stock price based on the given parameter.
 * @details
 * This function generates an initial stock price based on the given parameter `a`.
 * The parameter `a` determines the initial stock price as follows:
 * | a | Mean | Standard Deviation |
 * |---|------|--------------------|
 * | 1 | 5    | 2                  |
 * | 2 | 50   | 20                 |
 * | 3 | 150  | 50                 |
 *
 * @param a The parameter that determines the initial stock price.
 * @return The generated initial stock price.
 */
float initStockPrice(int a);

/**
 * @brief Initializes a reasonable standard deviation for generating random stock prices.
 * @return The initialized standard deviation.
 */
float initStandardDeviation(void);

/**
 * @brief Calculates the percentage change in the stock price based on the given stock object.
 * @details
 * There is a upper limit and lower limit that the realisation of the % change must fall between.
 * - All data is taken from a stock class.
 * As each round pass we allow for more and more chaotic behaviour by making the bounds less tight.
 * - Where n is number of rounds.
 * - The rate this happens is `n^2/15` for upper bound.
 * - And `n` for lower bound before lower bound reach `-100`.
 * - Just for fun (`chaotic evil smirk`). Upon devastating events which leads to
 * A stock price only `10%` left of it's initial, we increase mean to prevent a game over.
 * Upon we are 90.32% sure the bounds would be wrong we bump the mean.
 *
 * @param stock The stock object from which the percentage change is calculated.
 * @return The calculated percentage change in the stock price.
 */
float percentageChangePrice(Stock & stock);

class py_random {
    public:
        /**
         * @brief Generates a random integer within the range `[min, max]`.
         * @note This function is equivalent to the following code snippets:
         * @code {.cpp}
         * std::cout << py_random::randint(-5, 5) << std::endl; @endcode
         * @code {.py}
         * from random import randint
         * print(randint(-5, 5))
         * @endcode
         * @param min The lower bound for the random integer generation.
         * @param max The upper bound for the random integer generation.
         * @return The generated random integer.
         */
        static int randint(int min, int max);
};

#endif
