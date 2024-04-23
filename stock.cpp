/**
 * @file stock.cpp
 * @authors eric15342335, comet13579 (save/load)
 * @brief Implementation of the Stock class.
 */

#include <iostream>
#include <fstream>
#include "stock.h"
#include "names.h"
#include "random_price.h"

Stock::Stock(void) {
    category = random_integer(category_list_size);
    name = generate_name(category, 1)[0];
    /** The distribution of initial stock price will be consistent across same categories
     * Note that the value '3' is because currently init_stock_price has 3 possible input values.
     */
    price = init_stock_price(category % 3 + 1);
    quantity = 0;
    attributes[standard_deviation] = init_sd();
    attributes[mean] = 0;
    attributes[lower_limit] = -20;
    attributes[upper_limit] = 20;
    split_count = 0;
    update_history();
}

void Stock::save(std::string playerName, int i) {
    std::string filesave;
    std::ofstream fout;
    filesave = "saves/" + playerName + "/" + std::to_string(i) + ".save"; // creating the file path
    fout.open(filesave.c_str());
    fout << category << std::endl; // literally load everything into class into file
    fout << name << std::endl;
    for (unsigned int i = 0; i < history.size(); i++) {
        fout << history[i] << " ";
    }
    fout << -1 << std::endl; // -1 is the stop code for vector<float> history in filesave
    fout << quantity << std::endl;
    fout << attributes[standard_deviation] << " ";
    fout << attributes[mean] << " ";
    fout << attributes[lower_limit] << " ";
    fout << attributes[upper_limit] << std::endl;
    fout << split_count << std::endl << std::endl;

    // Save the ongoing events, separated by std::endl
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        fout << *event_itr << std::endl;
        event_itr++;
    }
    fout.close();
}

void Stock::load(std::string playerName, int i) {
    std::string fileToBeLoaded;
    float loadedPrice;
    std::ifstream fin;
    fileToBeLoaded = "saves/" + playerName + "/" + std::to_string(i) + ".save";
    std::cout << fileToBeLoaded << std::endl;
    fin.open(fileToBeLoaded.c_str());
    // checks if the file is open successfully
    if (!fin.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        return;
    }
    // get the first line, which is category
    fin >> category;
    // boundary check for category
    if (category >= category_list_size) {
        std::cerr << "Error: Invalid category loaded" << std::endl;
        throw;
    }
    // the second line is entirely the stock name
    std::getline(fin >> std::ws, name);
    fin >> loadedPrice;
    // Erase the history vector, since we called the constructor already
    history.clear();
    while (loadedPrice != -1) {
        history.push_back(loadedPrice);
        fin >> loadedPrice;
    }
    // Set the price
    price = history[history.size() - 1];
    fin >> quantity;
    fin >> attributes[standard_deviation];
    fin >> attributes[mean];
    fin >> attributes[lower_limit];
    fin >> attributes[upper_limit];
    fin >> split_count;
    // Manually reposition the file pointer to the sixth line
    // by going to the beginning of the file and skipping the first five lines
    fin.seekg(0, std::ios::beg);
    for (int i = 0; i < 7; i++) {
        std::string line;
        std::getline(fin, line);
    }

    // Load the ongoing events, separated by std::endl
    std::string loadedEventString;
    while (std::getline(fin, loadedEventString)) {
        Stock_event loadedEvent;
        std::istringstream(loadedEventString) >> loadedEvent;
        // Check the loaded event is valid
        // Ignore the special case of event_id >= 65535
        if (loadedEvent.event_id >= 65535 && loadedEvent.event_id < all_stock_events.size()) {
            add_event(loadedEvent);
            continue;
        }
        Stock_event comparedEvent = all_stock_events[loadedEvent.event_id];
        if (loadedEvent == comparedEvent) {
            add_event(loadedEvent);
        }
        else {
            std::cerr << "Error: Invalid event loaded" << std::endl;
            // Output the difference between the loaded event and the compared event
            std::cerr << "Loaded event: " << loadedEvent << std::endl;
            std::cerr << "Compared event: " << comparedEvent << std::endl;
            throw;
        }
    }
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
        split_count++;
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
