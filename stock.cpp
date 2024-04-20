/**
 * @file stock.cpp
 * @author eric15342335
 * @brief Implementation of the Stock class.
 */
#include "stock.h"
#include "names.h"
#include "random_price.h"

float Stock::purchase(float & balance, unsigned int amount, float trading_fees_percent) {
    float total_cost = price * amount * (1 + trading_fees_percent);
    // Check if the player has enough balance to buy the stock
    if (total_cost > balance && price <= 0) {
        return -1;
    }
    // Update the balance, quantity, and spentMoney
    balance -= total_cost;
    quantity += amount;
    spentMoney += total_cost;
    return total_cost;
}

float Stock::sell(float & balance, unsigned int amount, float trading_fees_percent) {
    // Check if the player has enough stocks to sell
    if (quantity < amount && price <= 0) {
        return -1;
    }
    // Calculate the total revenue
    float total_revenue = price * amount * (1 - trading_fees_percent);
    balance += total_revenue;
    quantity -= amount;
    // spentMoney -= total_revenue;
    return total_revenue;
}

std::string Stock::getCategoryName(void) { return CategoryList[category]; }

unsigned int Stock::getAffordableQuantity(float balance, float trading_fees_percent) {
    float value = balance / (price * (1 + trading_fees_percent));
    return value < 0 ? 0 : (unsigned int)value;
}

void Stock::updatePriceHistory(void) {
    /** We use vector now! */
    history.push_back(price);
}

std::vector<float> Stock::returnMostRecentHistory(unsigned int rounds) {
    std::vector<float> recent_history;
    if (rounds >= history.size()) {
        return history;
    }
    for (unsigned int i = history.size() - rounds; i < history.size(); i++) {
        recent_history.push_back(history[i]);
    }
    return recent_history;
}

float Stock::deltaPrice(void) {
    // Stock prices are stored in the history array
    if (history.size() < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
    }
    // Return the change of the last two prices
    return history[history.size() - 1] - history[history.size() - 2];
}

float Stock::deltaPercentagePrice(void) {
    if (history.size() < 2 || history[history.size() - 1] < 0 || history[history.size() - 2] < 0) {
        /** If there are less than two prices in the history array, return 0
         * If the last two prices are negative, return 0, as it is not possible to
         * calculate the percentage change
         */
        return 0;
    }
    return deltaPrice() / history[history.size() - 2];
}

void Stock::addEvent(Stock_event event) {
    if (!canAddEvent(event)) {
        // If the event is mutually exclusive with ongoing events,
        // ignore it and do nothing.
        return;
    }
    // If the event does not exist, add it to the std::list of events
    // Otherwise, update the duration of the event by deleting the old one and add the new one.
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        if (*event_itr == event) {
            event_itr = events.erase(event_itr);
        }
        else {
            event_itr++;
        }
    }
    events.push_back(event);
}

bool Stock::canAddEvent(Stock_event event) {
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        if (event_itr->mutually_exclusive_events.size() > 0) {
            for (unsigned int i = 0; i < event_itr->mutually_exclusive_events.size(); i++) {
                if (event_itr->mutually_exclusive_events[i] == event.event_id) {
                    return false;
                }
            }
        }
        event_itr++;
    }
    return true;
}

void Stock::removeObseleteEvent(void) {
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        if (event_itr->duration <= 0) {
            event_itr = events.erase(event_itr);
        }
        else {
            event_itr++;
        }
    }
}

float Stock::sumEventModifiersAttribute(stock_modifiers attribute) {
    float sum = 0;
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        sum += event_itr->modifiers[attribute];
        event_itr++; // Bug fix: infinite loop
    }
    return sum;
}

Stock::Stock(void) {
    category = py_random::randint(0, sizeofCategoryList - 1);
    name = generateName(category, 1)[0];
    /** The distribution of initial stock price will be consistent across same categories
     * Note that the value '3' is because currently initStockPrice has 3 possible input values.
     */
    price = initStockPrice(category % 3 + 1);
    quantity = 0;
    spentMoney = 0;
    attributes[standard_deviation] = initStandardDeviation();
    attributes[mean] = 0;
    attributes[lower_limit] = -40;
    attributes[upper_limit] = 40;
    updatePriceHistory();
}

void Stock::gotoNextRound(void) {
    // Update the price of the stock.
    price += price * percentageChangePrice(*this) / 100;
    // Reduce all events duration by one.
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        event_itr->duration--;
        event_itr++;
    }
    removeObseleteEvent();
    updatePriceHistory();
}
