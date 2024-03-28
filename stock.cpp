// the class Stock definition
#include <string>
#include "stock.h"
#include "names.h"
#include "random_price.h"
using namespace std;

double Stock::purchase(double &balance, unsigned int amount) {
    // Purchase a number of stocks
    // Return the total cost of the purchase
    // If the player does not have enough balance, return -1
    // Otherwise, update the balance and quantity of the stock
    double total_cost = price * amount;
    if (total_cost > balance) {
        return -1;
    }
    balance -= total_cost;
    quantity += amount;
    return total_cost;
}

double Stock::sell(double &balance, unsigned int amount) {
    // Sell a number of stocks
    // Return the total revenue of the sale
    // If the player does not have enough stocks, return -1
    // Otherwise, update the balance and quantity of the stock
    if (quantity < amount) {
        return -1;
    }
    double total_revenue = price * amount;
    balance += total_revenue;
    quantity -= amount;
    return total_revenue;
}

string Stock::category_name(void) {
    // Return the name of the category
    return category_list[category];
}

unsigned int Stock::num_stocks_affordable(double balance) {
    // Return the number of stocks that the player can afford
    return (unsigned int) balance / price;
}


void Stock::init(void) {
    // Assign a random price, standard deviation, skewness, and category to the stock
    category = random_integer(category_list_size);

    // Generate a name based on the category
    name = generate_name(category);
}
