/**
 * @file stock.cpp
 * @brief Implementation of the Stock class
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
    // Update the balance, quantity, and money_spent
    balance -= total_cost;
    quantity += amount;
    money_spent += total_cost;
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
    // money_spent -= total_revenue;
    return total_revenue;
}

std::string Stock::category_name(void) {
    return category_list[category];
}

unsigned int Stock::num_stocks_affordable(float balance, float trading_fees_percent) {
    float value = balance / (price * (1 + trading_fees_percent));
    return value < 0 ? 0 : (unsigned int)value;
}

void Stock::update_history(void) {
    /** We use vector now! */
    history.push_back(price);
}

std::vector<float> Stock::return_most_recent_history(unsigned int rounds) {
    std::vector<float> recent_history;
    if (rounds >= history.size()) {
        return history;
    }
    for (unsigned int i = history.size() - rounds; i < history.size(); i++) {
        recent_history.push_back(history[i]);
    }
    return recent_history;
}

float Stock::delta_price(void) {
    // Stock prices are stored in the history array
    if (history.size() < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
    }
    // Return the change of the last two prices
    return history[history.size() - 1] - history[history.size() - 2];
}

float Stock::delta_price_percentage(void) {
    if (history.size() < 2 || history[history.size() - 1] < 0 || history[history.size() - 2] < 0) {
        /** If there are less than two prices in the history array, return 0
         * If the last two prices are negative, return 0, as it is not possible to
         * calculate the percentage change
         */
        return 0;
    }
    return delta_price() / history[history.size() - 2];
}

void Stock::add_event(Stock_event event) {
    if (!can_add_event(event)) {
        // If the event is mutually exclusive with ongoing events,
        // ignore it and do nothing.
        return;
    }
    // If the event does not exist, add it to the list of events
    // Otherwise, update the duration of the event by deleting the old one and add the new one.
    list<Stock_event>::iterator event_itr = events.begin();
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

bool Stock::can_add_event(Stock_event event) {
    list<Stock_event>::iterator event_itr = events.begin();
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

void Stock::remove_obselete_event(void) {
    list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        if (event_itr->duration <= 0) {
            event_itr = events.erase(event_itr);
        }
        else {
            event_itr++;
        }
    }
}

float Stock::sum_attribute(stock_modifiers attribute) {
    float sum = 0;
    list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        sum += event_itr->modifiers[attribute];
    }
    return sum;
}

Stock::Stock(void) {
    /** @todo Follow-up */
    category = random_integer(category_list_size);
    name = generate_name(category, 1)[0];
    /** The distribution of initial stock price will be consistent across same categories
     * Note that the value '3' is because currently init_stock_price has 3 possible input values.
     */
    price = init_stock_price(category % 3 + 1);
    quantity = 0;
    money_spent = 0;
    /** @todo Update the attributes via the functions provided by Jeremy in random_price.cpp */
    attributes[standard_deviation] = 0.1;
    attributes[mean] = 0.1;
    attributes[lower_limit] = 0;
    attributes[upper_limit] = 0;
    update_history();
}

void Stock::next_round(void) {
    /** @todo Use the functions provided by Jeremy in random_price.cpp to update the stock price. */
    price += 0.1;
    /** Reduce all events duration by one */
    list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        event_itr->duration--;
        event_itr++;
    }
    /** Remove the obselete events */
    remove_obselete_event();
    /** Update the history array with the current price */
    update_history();
}
