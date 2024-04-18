#include "events.h"
#include "random_price.h"
#include "stock.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <string>
#include <vector>

float init_stock_price(int price_profile) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<float> distribution(5.0, 2.0);
  if (price_profile == 2) {
    distribution.param(std::normal_distribution<float>::param_type(50.0, 20.0));
  }
  if (price_profile == 3) {
    distribution.param(
        std::normal_distribution<float>::param_type(150.0, 50.0));
  }
  return abs(distribution(gen));
}

float init_sd(int price_profile) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<float> distribution(0.5, 0.5);
  if (price_profile == 2) {
    distribution.param(std::normal_distribution<float>::param_type(3.0, 1.5));
  }
  if (price_profile == 3) {
    distribution.param(std::normal_distribution<float>::param_type(10.0, 3.0));
  }
  return abs(distribution(gen));
}

float percentage_change_price(Stock &stock) {
  float current_price = stock.return_most_recent_history(1)[0];
  float init_price = stock.return_most_recent_history(99999999)[0];
  unsigned int rounds_passed = stock.get_history_size();
  std::random_device rd;
  std::mt19937 gen(rd());
  if (current_price < init_price / 10) {
    stock.change_mean(current_price * 0.3);
  }
  float temp = 100 * abs(init_price - current_price) / init_price;
  float upper_limit = 50 + (rounds_passed * rounds_passed) / 15 + temp;
  float lower_limit = -1 * (50 + rounds_passed + temp);
  float z_score_upper_limit = (upper_limit - stock.get_attribute(mean)) /
                              stock.get_attribute(standard_deviation);
  float z_score_lower_limit = (lower_limit - stock.get_attribute(mean)) /
                              stock.get_attribute(standard_deviation);
  for (int i = 0; i < 5; i++) {
    if (z_score_lower_limit > 1.3) {
      stock.change_mean(current_price * 0.3);
    }
    if (z_score_upper_limit < -1.3) {
      stock.change_mean(current_price * -0.3);
    }
  }
  std::normal_distribution<float> distribution(
      stock.get_attribute(mean), stock.get_attribute(standard_deviation));

  if (lower_limit < -100) {
    lower_limit = -100;
  }
  while (true) {
    float x = distribution(gen);
    if (x < upper_limit and x > lower_limit) {
      return x;
    }
  }
  // prevent compiler freak out
  return distribution(gen);
}

unsigned int random_integer(unsigned int max_integer) {
  return rand() % max_integer;
}
