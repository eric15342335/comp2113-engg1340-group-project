#include <string>
#include "stock.h"
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
    switch (category) {
        case 0:
            return "tech";
        case 1:
            return "finance";
        case 2:
            return "healthcare";
        case 3:
            return "consumer";
        case 4:
            return "energy";
        default:
            return "unknown";
    }
}

void Stock::init(void) {
    // Assign a random price, standard deviation, skewness, and category to the stock
    // Generate a name based on the category
}
