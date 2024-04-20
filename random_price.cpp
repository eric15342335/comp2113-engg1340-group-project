/**
 * @file random_price.cpp
 * @author 84ds84d8s
 * @brief Definitions of random stock price generation functions.
 */

#include "events.h"
#include "random_price.h"
#include <cstdlib>
#include <random>

float initStockPrice(int price_profile = 1) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> distribution(5.0, 2.0);
    if (price_profile == 2) {
        distribution.param(std::normal_distribution<float>::param_type(50.0, 20.0));
    }
    if (price_profile == 3) {
        distribution.param(std::normal_distribution<float>::param_type(150.0, 50.0));
    } // else price_profile == 1
    // The stock price is always positive
    return abs(distribution(gen));
}

float initStandardDeviation(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> distribution(0.5, 0.5);
    // The standard deviation is always positive
    return abs(distribution(gen));
}

float percentageChangePrice(Stock & stock) {
    // Get the values from the stock object
    float current_price = stock.returnMostRecentHistory(1)[0];
    float init_price = stock.returnMostRecentHistory(99999999)[0];
    float offset = stock.getStockAttribute(mean) + stock.sumEventModifiersAttribute(mean);
    float sd = stock.getStockAttribute(standard_deviation) + stock.sumEventModifiersAttribute(standard_deviation);
    unsigned int rounds_passed = stock.getSizeOfHistory();

    // Generate the percentage change in the stock price.
    std::random_device rd;
    std::mt19937 gen(rd());
    if (current_price < init_price / 10) {
        // If the stock price is only `10%` or `less` of the initial price, increase the mean.
        stock.changeMean(current_price * 0.3);
    }
    float temp = 100 * abs(init_price - current_price) / init_price;
    float upper_limit = 50 + (rounds_passed * rounds_passed) / 15 + temp;
    float lower_limit = -1 * (50 + rounds_passed + temp);
    float z_score_upper_limit = (upper_limit - offset) / sd;
    float z_score_lower_limit = (lower_limit - offset) / sd;
    for (int i = 0; i < 5; i++) {
        if (z_score_lower_limit > 1.3) {
            stock.changeMean(current_price * 0.3);
        }
        if (z_score_upper_limit < -1.3) {
            stock.changeMean(current_price * -0.3);
        }
    }
    std::normal_distribution<float> distribution(offset, sd);

    // Ensure that the lower limit is not too low
    if (lower_limit < -100) {
        lower_limit = -100;
    }
    while (true) {
        float x = distribution(gen);
        // Ensure that the percentage change falls within the bounds
        if (x < upper_limit and x > lower_limit) {
            return x;
        }
    }
}

int py_random::randint(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}
