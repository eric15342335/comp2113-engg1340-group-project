// code related to randomness
#include "random_price.h"
#include <cstdlib>
#include <iostream>
#include <random>

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
    return abs(distribution(gen));
}

float stock_change(int mode) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> distribution(0, 0.5);
    if (mode == 1) {
        distribution.param(std::normal_distribution<float>::param_type(0.5, 0.5));
    }
    if (mode == 2) {
        distribution.param(std::normal_distribution<float>::param_type(-0.5, 0.5));
    }
    if (mode == 3) {
        distribution.param(std::normal_distribution<float>::param_type(2, 1));
    }
    if (mode == 4) {
        distribution.param(std::normal_distribution<float>::param_type(-2, 1));
    }
    if (mode == 5) {
        distribution.param(std::normal_distribution<float>::param_type(10, 3));
    }
    if (mode == 6) {
        distribution.param(std::normal_distribution<float>::param_type(-10, 3));
    }
    if (mode == 7) {
        distribution.param(std::normal_distribution<float>::param_type(0.5, 3));
    }
    if (mode == 8) {
        distribution.param(std::normal_distribution<float>::param_type(-0.5, 3));
    }
    if (mode == 9) {
        distribution.param(std::normal_distribution<float>::param_type(0, 3));
    }
    float x = distribution(gen);
    if (x < -100) {
        x = -100;
    }
    return x;
}
unsigned int random_integer(unsigned int max_integer) {
    return rand() % max_integer;
}
