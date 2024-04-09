// code related to randomness
#include "random_price.h"
#include <cstdlib>
#include <iostream>
#include <random>

double init_stock_price(int a) {
  std::random_device rd;
  // Merssane Twister
  std::mt19937 gen(rd());
  if (a == 2) {
    std::normal_distribution<double> distribution(50.0, 20.0);
    return distribution(gen);
  } else {
    if (a == 3) {
      std::normal_distribution<double> distribution(150.0, 50.0);
      return distribution(gen);
    } else {
      std::normal_distribution<double> distribution(5.0, 2.0);
      return distribution(gen);
    }
  }
  return 0.00;
}
double random_sd(float price) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<double> d(0.03 * price, 0.02 * price);
  return abs(d(gen));
}
double random_stock(float &mean, float &sd, float &upper_limit,
                    float &lower_limit) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<double> distribution(mean, sd);
  float price = distribution(gen);
  // for mean > temp i.e. falling prices
  if ((mean - price) > (lower_limit * mean)) {
    mean = price;
  }
  // rising prices
  if ((price - mean) > (upper_limit * mean)) {
    mean = price;
  }
  sd = random_sd(price);
  return price;
}
unsigned int random_integer(unsigned int max_integer) {
  return rand() % max_integer;
}
