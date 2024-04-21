/**
 * @file stock.cpp
 * @author eric15342335
 * @brief Implementation of the Stock class.
 */
#include <iostream>
#include <fstream>
#include "stock.h"
#include "names.h"
#include "random_price.h"

void Stock::random() {
    category = random_integer(category_list_size);
    name = generate_name(category, 1)[0];
    /** The distribution of initial stock price will be consistent across same categories
     * Note that the value '3' is because currently init_stock_price has 3 possible input values.
     */
    price = init_stock_price(category % 3 + 1);
    quantity = 0;
    attributes[standard_deviation] = init_sd();
    attributes[mean] = 0;
    attributes[lower_limit] = -40;
    attributes[upper_limit] = 40;
    update_history();
}

void Stock::save(std::string playername, int i) {
    std::string filesave;
    std::ofstream fout;
    filesave = "saves/" + playername + "/" + std::to_string(i) + ".save";
    fout.open(filesave.c_str());
    fout << category << std::endl;
    fout << name << std::endl;
    for (unsigned int i = 0; i < history.size(); i++) {
        fout << history[i] << " ";
    }
    fout << -1 << std::endl;
    fout << quantity << std::endl;
    fout << attributes[standard_deviation] << " ";
    fout << attributes[mean] << " ";
    fout << attributes[lower_limit] << " ";
    fout << attributes[upper_limit] << std::endl;
    fout.close();
}

void Stock::load(std::string playername, int i) {
    std::string fileload;
    float stockloadprice;
    std::ifstream fin;
    fileload = "saves/" + playername + "/" + std::to_string(i) + ".save";
    std::cout << fileload << std::endl;
    fin.open(fileload.c_str());
    // checks if the file is open successfully
    if (!fin.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        return;
    }
    // checks file good
    if (!fin.good()) {
        std::cerr << "Error: File not good" << std::endl;
        return;
    }
    // get the first line, which is category
    fin >> category;
    // the second line is entirely the stock name
    std::getline(fin >> std::ws, name);
    fin >> stockloadprice;
    while (stockloadprice != -1) {
        history.push_back(stockloadprice);
        fin >> stockloadprice;
    }
    fin >> quantity;
    fin >> attributes[standard_deviation];
    fin >> attributes[mean];
    fin >> attributes[lower_limit];
    fin >> attributes[upper_limit];
    fin.close();
}

float Stock::purchase(float & balance, unsigned int amount, float trading_fees_percent) {
    float total_cost = price * amount * (1 + trading_fees_percent);
    // Check if the player has enough balance to buy the stock
    if (total_cost > balance && price <= 0) {
        return -1;
    }
    // Update the balance, quantity, and money_spent
    balance -= total_cost;
    quantity += amount;
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
    return total_revenue;
}

std::string Stock::category_name(void) {
    return category_list[category];
}

unsigned int Stock::num_stocks_affordable(float balance, float trading_fees_percent) {
    float value = balance / (price * (1 + trading_fees_percent));
    return value < 0 ? 0 : static_cast<unsigned int>(value);
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

bool Stock::can_add_event(Stock_event event) {
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

void Stock::remove_obselete_event(void) {
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

float Stock::sum_attribute(stock_modifiers attribute) {
    float sum = 0;
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        sum += event_itr->modifiers[attribute];
        event_itr++; // Bug fix: infinite loop
    }
    return sum;
}

void Stock::next_round(void) {
    /** Update the price of the stock.
     * If the price is less than 1000, the price will increase or decrease by a random percentage.
     * If the price is more than 1000, the price will be halved and the quantity will be doubled.
     */
    float price_diff = percentage_change_price(*this) / 100;
    if (!(price * (1 + price_diff) > 999.9)) {
        price *= (1 + price_diff);
    }
    else {
        price /= 2;
        quantity *= 2;
        add_event(Stock_event{// Stock split event
                              /** event_id */ 65535,
                              /** mutually_exclusive_events */ {},
                              /** text */
                              name + " has rised too high and the company has decide a stock split on it.",
                              /** duration */ 1,
                              /** percentage_permille */ 0,
                              /** type_of_event */ pick_random_stock,
                              /** category */ category,
                              /** modifiers*/
                              {{standard_deviation, 0}, {mean, 0}, {lower_limit, 0}, {upper_limit, 0}}});
    }
    // Reduce all events duration by one.
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        event_itr->duration--;
        event_itr++;
    }
    remove_obselete_event();
    update_history();
}

std::vector<unsigned int> Stock::get_event_ids(void) {
    std::vector<unsigned int> event_ids;
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        event_ids.push_back(event_itr->event_id);
        event_itr++;
    }
    return event_ids;
}
