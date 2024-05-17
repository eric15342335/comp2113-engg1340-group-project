/// @file stock.cpp
/// Implementation of the Stock class.
/*
This program is free software: you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this
program. If not, see <https://www.gnu.org/licenses/>.
*/
#include "stock.h"

#include "format.h"
#include "names.h"
#include "random_price.h"

#include <algorithm>
#include <fstream>
#include <iostream>

const int INVALID_OPERATION = -1;

Stock::Stock(void) {
    category = random_integer(category_list_size);
    name = generate_name(category, 1)[0];
    /** The distribution of initial stock price will be consistent across the same
     * categories.
     * Note that the value '3' is because currently init_stock_price has 3
     * possible input values.
     */
    price = init_stock_price(category % 3 + 1);
    quantity = 0;
    attributes[standard_deviation] = init_sd();
    attributes[mean] = defaultMean;
    attributes[lower_limit] = defaultLowerLimit;
    attributes[upper_limit] = defaultUpperLimit;
    split_count = 0;
    update_history();
}

void Stock::save(const std::string & playerName, int i) {
    std::string filesave;
    std::ofstream fout;
    filesave = "saves/" + playerName + "/" + std::to_string(i) +
               ".save"; // creating the file path
    fout.open(filesave.c_str());
    fout << category << std::endl; // literally load everything into class into file
    fout << name << std::endl;
    for (unsigned int index = 0; index < history.size(); index++) {
        fout << history[index] << " ";
    }
    fout << -1
         << std::endl; // -1 is the stop code for vector<float> history in filesave
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

void Stock::load(const std::string & playerName, int i) {
    std::string fileToBeLoaded;
    float loadedPrice;
    std::ifstream fin;
    fileToBeLoaded = "saves/" + playerName + "/" + std::to_string(i) + ".save";
    std::cout << "Loading " << fileToBeLoaded << " ... ";
    fin.open(fileToBeLoaded.c_str());
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
        history.emplace_back(loadedPrice);
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
    for (int lineCount = 0; lineCount < 7; lineCount++) {
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
        if (loadedEvent.event_id >= 65535 &&
            loadedEvent.event_id < all_stock_events.size()) {
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
    time::sleep(random_integer(sleepShort)); // optimize this
    std::cout << "done" << std::endl;
}

float Stock::purchase(
    float & balance, unsigned int amount, float trading_fees_percent) {
    float total_cost = price * amount * (1 + trading_fees_percent);
    // Check if the player has enough balance to buy the stock
    if (total_cost > balance && price <= 0) {
        return INVALID_OPERATION;
    }
    // Update the balance, quantity, and money_spent
    balance -= total_cost;
    quantity += amount;
    return total_cost;
}

float Stock::sell(float & balance, unsigned int amount, float trading_fees_percent) {
    // Check if the player has enough stocks to sell
    if (quantity < amount && price <= 0) {
        return INVALID_OPERATION;
    }
    // Calculate the total revenue
    float total_revenue = price * amount * (1 - trading_fees_percent);
    balance += total_revenue;
    quantity -= amount;
    return total_revenue;
}

std::string Stock::category_name(void) const { return category_list[category]; }

unsigned int Stock::num_stocks_affordable(
    float balance, float trading_fees_percent) const {
    float value = balance / (price * (1 + trading_fees_percent));
    return value < 0 ? 0 : static_cast<unsigned int>(value);
}

void Stock::update_history(void) {
    /** We use vector now! */
    history.emplace_back(price);
}

std::vector<float> Stock::return_most_recent_history(unsigned int rounds) {
    std::vector<float> recent_history;
    if (rounds >= history.size()) {
        return history;
    }
    for (unsigned int i = history.size() - rounds; i < history.size(); i++) {
        recent_history.emplace_back(history[i]);
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
    if (history.size() < 2 || history[history.size() - 1] < 0 ||
        history[history.size() - 2] < 0) {
        /** If there are less than two prices in the history array, return 0
         * If the last two prices are negative, return 0, as it is not possible to
         * calculate the percentage change
         */
        return 0;
    }
    return delta_price() / history[history.size() - 2];
}

void Stock::add_event(const Stock_event & event) {
    if (!can_add_event(event)) {
        // If the event is mutually exclusive with ongoing events,
        // ignore it and do nothing.
        return;
    }
    // If the event does not exist, add it to the std::list of events
    // Otherwise, update the duration of the event by deleting the old one and add the
    // new one.
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        if (*event_itr == event) {
            event_itr = events.erase(event_itr);
        }
        else {
            event_itr++;
        }
    }
    events.emplace_back(event);
}

bool Stock::can_add_event(const Stock_event & event) {
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        if (!event_itr->mutually_exclusive_events.empty()) {
            for (unsigned int i = 0; i < event_itr->mutually_exclusive_events.size();
                 i++) {
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
     * If the price is less than 1000, the price will increase or decrease by a random
     * percentage. If the price is more than 1000, the price will be halved and the
     * quantity will be doubled.
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
            name +
                " has rised too high and the company has decide a stock split on it.",
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
        if (event_itr->duration > durationDecreaseMultiplier) {
            event_itr->duration -= durationDecreaseMultiplier;
        }
        else {
            event_itr->duration = 0;
        }
        event_itr++;
    }
    remove_obselete_event();
    update_history();
}

std::vector<unsigned int> Stock::get_event_ids(void) {
    std::vector<unsigned int> event_ids;
    std::list<Stock_event>::iterator event_itr = events.begin();
    while (event_itr != events.end()) {
        event_ids.emplace_back(event_itr->event_id);
        event_itr++;
    }
    return event_ids;
}

float Stock::getTotalAttribute(stock_modifiers attribute) {
    return attributes[attribute] + sum_attribute(attribute);
}

void sortStocksList(std::vector<Stock> & stocks_list, SortingMethods sortMethod,
    SortingDirections sortDirection) {
    switch (sortMethod) {
        case by_name:
            std::sort(stocks_list.begin(), stocks_list.end(),
                [](Stock a, Stock b) { return a.get_name() < b.get_name(); });
            break;
        case by_category:
            std::sort(stocks_list.begin(), stocks_list.end(),
                [](Stock a, Stock b) { return a.get_category() < b.get_category(); });
            break;
        case by_price:
            std::sort(stocks_list.begin(), stocks_list.end(),
                [](Stock a, Stock b) { return a.get_price() < b.get_price(); });
            break;
        case by_quantity:
            std::sort(stocks_list.begin(), stocks_list.end(),
                [](Stock a, Stock b) { return a.get_quantity() < b.get_quantity(); });
            break;
        case by_sd:
            std::sort(stocks_list.begin(), stocks_list.end(), [](Stock a, Stock b) {
                return a.getTotalAttribute(standard_deviation) <
                       b.getTotalAttribute(standard_deviation);
            });
            break;
        case by_mean:
            std::sort(stocks_list.begin(), stocks_list.end(), [](Stock a, Stock b) {
                return a.getTotalAttribute(mean) < b.getTotalAttribute(mean);
            });
            break;
        case by_lower_limit:
            std::sort(stocks_list.begin(), stocks_list.end(), [](Stock a, Stock b) {
                return a.getTotalAttribute(lower_limit) <
                       b.getTotalAttribute(lower_limit);
            });
            break;
        case by_upper_limit:
            std::sort(stocks_list.begin(), stocks_list.end(), [](Stock a, Stock b) {
                return a.getTotalAttribute(upper_limit) <
                       b.getTotalAttribute(upper_limit);
            });
            break;
        default:
            break;
    }
    if (sortDirection == descending) {
        std::reverse(stocks_list.begin(), stocks_list.end());
    }
}
