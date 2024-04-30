/**
 * @file random_price.cpp
 * @brief Random price generator for stock market simulation
 * @author 84ds84d8s
 */

#include "random_price.h"

#include <algorithm>
#include <cstdlib>
#include <random>
// Included iostream for debugging uses.
#include <iostream>

float init_stock_price(int price_profile) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> distribution(5.0, 2.0);
    if (price_profile == 2) {
        distribution.param(std::normal_distribution<float>::param_type(50.0, 20.0));
    }
    if (price_profile == 3) {
        distribution.param(std::normal_distribution<float>::param_type(150.0, 50.0));
    }
    return std::abs(distribution(gen));
}

float init_sd(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // The old distribution was 0.5, 0.5.
    // After applying std::abs(), the distribution is not symmetric anymore.
    std::normal_distribution<float> distribution(0, 0.5);
    return std::abs(distribution(gen)) + 0.5;
}

unsigned int random_integer(unsigned int max_integer) {
    // Discrete uniform distribution
    // like python randint
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> distribution(0, max_integer - 1);
    return distribution(gen);
}

std::map<stock_modifiers, float> getProcessedModifiers(Stock stock) {
    float trueMean = meanMultiplier * (stock.getTotalAttribute(mean));
    float trueSD = sdMultiplier * (stock.getTotalAttribute(standard_deviation));
    unsigned int rounds_passed = stock.get_history_size();
    if (stock.get_price() < stock.get_initial_price() / 10) {
        // Force the return of a significantly higher mean normal dist, by a bit over
        // doubling the price.
        trueMean += 200;
    }
    else if (stock.get_price() < stock.get_initial_price() / 7) {
        trueMean += 100;
    }
    /* There is a upper limit and lower limit that the realisation of the % change must
     * fall between. As each round pass we allow for more and more chaotic behaviour by
     * making the bounds less tight.
     * Just for fun (chaotic evil smirk). Upon devastating events which leads to
     * a stock price only 10 % left of it's initial, we increase mean to prevent a game
     * over. Upon we are 90.32% sure the bounds would be wrong we bump the mean.
     */
    // temp is the percentage difference between the initial price and the current price
    // of the stock.
    float temp = 100 * std::abs(stock.get_initial_price() - stock.get_price()) /
                 stock.get_price();
    float upper_lim = stock.get_attribute(upper_limit) +
                      stock.sum_attribute(upper_limit) * upperLimitMultiplier +
                      rounds_passed / 3 + temp;
    float lower_lim = stock.get_attribute(lower_limit) +
                      stock.sum_attribute(lower_limit) * lowerLimitMultiplier -
                      rounds_passed / 3 - temp;
    // Standardize the upper and lower limit
    float zScoreUpLimit = (upper_limit - trueMean) / trueSD;
    float zScoreLowLimit = (lower_limit - trueMean) / trueSD;
    for (int i = 0; i < 10; i++) {
        if (zScoreLowLimit > 1.3) {
            // Very likely to fail lower_limit; about 90.32%; which means it is too low
            // and should realize at higher value;
            trueMean += meanMultiplier;
            zScoreLowLimit = (lower_limit - trueMean - 0.1) / trueSD;
        }
        if (zScoreUpLimit < -1.3) {
            // Converse
            // Reason: for N(0,1), probability of exceeed 1.3 is less that 10%
            trueMean -= meanMultiplier;
            zScoreUpLimit = (upper_limit - trueMean + 0.1) / trueSD;
        }
    }
    // -100% is not applicable for a stock price, so we set it to -90%.
    if (lower_lim < -90) {
        lower_lim = -90;
    }
    else if (lower_lim > defaultLowerLimit) {
        lower_lim = defaultLowerLimit;
    }
    if (upper_lim < defaultUpperLimit) {
        upper_lim = defaultUpperLimit;
    }
    return {{standard_deviation, trueSD}, {mean, trueMean}, {lower_limit, lower_lim},
        {upper_limit, upper_lim}};
}

float percentage_change_price(Stock stock) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<stock_modifiers, float> _modifiers = getProcessedModifiers(stock);
    std::normal_distribution<float> distribution(
        _modifiers[mean], _modifiers[standard_deviation]);
    // std::cout << offset << " " << sd << " " << lower_lim << " " << upper_lim <<
    // std::endl; Implementing a max loop here so will not be infinite if there is a
    // fault.
    for (unsigned int max_loop = 0; max_loop < 100; max_loop++) {
        float x = distribution(gen);
        if (x > _modifiers[lower_limit] && x < _modifiers[upper_limit]) {
            return x / std::pow(2, stock.get_split_count());
        }
    }
    // Need to have some stocastic behavour against a fault.
    float stocastics[12] = {0.95507, -0.74162, 1.642, -0.94774, -0.80314, 1.7885,
        -0.09846, 1.4693, 0.19288, -1.70222, 1.20933, -0.71088};
    return stocastics[random_integer(12)];
}
