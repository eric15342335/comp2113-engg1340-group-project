#include "random_price.h"

#include "events.h"

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
    std::normal_distribution<float> distribution(0.5, 0.5);
    return std::abs(distribution(gen));
}

unsigned int random_integer(unsigned int max_integer) {
    // Discrete uniform distribution
    // like python randint
    // Moved up; this decision will be justified at about line 128 where it is used
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> distribution(0, max_integer - 1);
    return distribution(gen);
}

float percentage_change_price(Stock & stock) {
    float current_price = stock.return_most_recent_history(1)[0];
    float init_price = stock.return_most_recent_history(99999999)[0];
    // Attention: The mean has been multiplied by 0.0007 and s.d. multiplied by 3.0
    // which is the configuration I use to prevent shitcoin behaviour.
    // This is as of events by 2024-04-23. These mearures to account for the systematic error
    // will be inappropriate in case of anyone tweaking the mean and sd of events.cpp
    // If you change those stuff please notify it before we discover
    // the stock prices traverse between heaven and hell or as invariant as John F. Kenedy's heart rate.
    float offset = 0.0007 * (stock.get_attribute(mean) + stock.sum_attribute(mean));
    float sd = 3.0 * (stock.get_attribute(standard_deviation) +
                      stock.sum_attribute(standard_deviation));
    unsigned int rounds_passed = stock.get_history_size();
    std::random_device rd;
    std::mt19937 gen(rd());
    if (current_price < init_price / 10) {
        // Previous Note By Eric:
        // Jeremy will fix the issue of current_price being too low e.g. 0
        // This action will have negligible effect on the stock price
        // I recommend to change the mean of the stock price
        // and add a new event "stock price rescue operation" via the add_event function
        // to push up the mean temporarily.
        // Note by Jeremy:
        // this code was originally stock.change_mean(current_price * 0.3);
        // Now we use another way to solve this problem:
        // Force the return of a significantly higher mean normal dist, by a bit over doubling the price.
        std::normal_distribution<float> distribution(offset + 200, sd);
        float u = distribution(gen);
        // Attempt to return it 5 times. If it still fail to show above -100 we dismiss the return.
        for (int w = 0; w < 5; w++) {
            if (u > -100) {
                return u / pow(2, stock.get_split_count());
            }
        }
    }
    else if (current_price < init_price / 7) {
        std::normal_distribution<float> distribution(offset + 100, sd);
        float u = distribution(gen);
        // This piece of code is triggered for a less catastrophic disaster,
        // now given that we are less shitcoin.
        // Still quite a bit of adjustment though at 100 %
        for (int w = 0; w < 5; w++) {
            if (u > -100) {
                return u / pow(2, stock.get_split_count());
            }
        }
    }
    float temp = 100 * abs(init_price - current_price) / init_price;
    // The unprocessed limits defined to make the lines look shorter w/o need to scroll
    // The names of variables here cannot be lower_limit as the stock attribute
    // lower_limit and upper_limit would crash with the float lower_ and upper_ limits
    // defined by the line 7x. So these variables and lines are of justified reason of existence.
    float unprocessed_upper_lim = stock.get_attribute(upper_limit) + stock.sum_attribute(upper_limit);
    float unprocessed_lower_lim = stock.get_attribute(lower_limit) + stock.sum_attribute(lower_limit);
    float upper_lim = unprocessed_upper_lim + rounds_passed / 3 + temp;
    float lower_lim = -1 * (unprocessed_lower_lim + rounds_passed / 3 + temp);
    float z_score_upper_limit = (upper_limit - offset) / sd;
    float z_score_lower_limit = (lower_limit - offset) / sd;
    std::normal_distribution<float> distribution(offset, sd);
    for (int i = 0; i < 10; i++) {
        if (z_score_lower_limit > 1.3) {
            // Very likely to fail lower_limit; about 90.32%; which means it is too low and should realize at higher value;
            distribution.param(std::normal_distribution<float>::param_type(offset + 0.1, sd));
            z_score_lower_limit = (lower_limit - offset - 0.1) / sd;
        }
        if (z_score_upper_limit < -1.3) { // converse
            // Reason: for N(0,1), probability of exceeed 1.3 is less that 10%
            distribution.param(std::normal_distribution<float>::param_type(offset - 0.1, sd));
            z_score_upper_limit = (upper_limit - offset + 0.1) / sd;
        }
    }

    if (lower_lim < -100) {
        lower_lim = -100;
    }
    // Prevents circular lower_limit and upper_limit
    // For good practive only (first layer of defense against infinite loop)
    if (lower_lim > -5) {
        lower_lim = -5;
    }
    if (upper_lim < 5) {
        upper_lim = 5;
    }
    // Debug line here:
    // std::cout << offset << " " << sd << " " << lower_lim << " " << upper_lim << std::endl;
    // Implementing a max loop here so will not be infinite if there is a fault.
    int max_loop = 0;
    while (true) {
        float x = distribution(gen);
        max_loop++;
        if (x > lower_lim && x < upper_lim) {
            return x / pow(2, stock.get_split_count());
        }
        else if (max_loop > 1000) {
            // This is wanted because I need to still have some stocastic behavour even against a fault
            // so that it kind of works. This is the second and final defense against any infinite loops.
            unsigned int i = random_integer(12);
            float stocastics[12] = {0.95507, -0.74162, 1.642, -0.94774, -0.80314, 1.7885,
            -0.09846, 1.4693, 0.19288, -1.70222, 1.20933, -0.71088};
            return stocastics[i];
        }
    }
}
