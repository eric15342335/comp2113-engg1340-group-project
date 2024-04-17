/** @file events.cpp
 * stores the event texts and modifiers
 */
#include "events.h"
#include <iostream>
#include <algorithm>

/*  stock cats:
    "Adv&Market", "Aero&Def", "Airlines", "RenewEnergy", "Auto", "Banks", "Biotech",
    "Broadcast", "Casinos&Gaming", "E-Commerce", "FinServices",
    "Food&Beverage", "Healthcare", "Tech", "RealEstate", "Retail", "Telecom"
*/

/** The list of all events that can be applied to the stocks */
//event_id 0 to 7 affect all stocks
std::vector<Stock_event> all_stock_events = {
    {/** event_id */ 0,
     /** mutually_exclusive_events */ {1},
     /** text */ "The FED has decreased the interest rate!", //good
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, 2}, {lower_limit, 0}, {upper_limit, 20}}},
    {/** event_id */ 1,
     /** mutually_exclusive_events */ {0, 3},
     /** text */ "The FED has increased the interest rate!", //bad
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, -2}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 2,
     /** mutually_exclusive_events */ {},
     /** text */ "Economic Recession: Market Downturn Signals Investor Concerns", //bad
     /** duration */ 7,
     /** percentage_permille */ 20,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.2}, {mean, -5}, {lower_limit, -50}, {upper_limit, 0}}},
    {/** event_id */ 3,
     /** mutually_exclusive_events */ {1},
     /** text */ "Central Bank Cuts Interest Rates: Market Stimulus Boosts Investor Sentiment", //good
     /** duration */ 3,
     /** percentage_permille */ 5,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.05}, {mean, 1}, {lower_limit, 0}, {upper_limit, 10}}},
    {/** event_id */ 4,
     /** mutually_exclusive_events */ {},
     /** text */ "Trade War Escalates: Global Market Volatility Amidst Rising Tensions", //bad
     /** duration */ 5,
     /** percentage_permille */ 15,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.15}, {mean, -3}, {lower_limit, -30}, {upper_limit, 0}}},
    {/** event_id */ 5,
     /** mutually_exclusive_events */ {},
     /** text */ "Natural Disaster Strikes: Stock Market Reacts to Catastrophic Event", //bad
     /** duration */ 7,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, -2}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 6,
     /** mutually_exclusive_events */ {},
     /** text */ "Government Policy Change: Market Impacted by New Regulations", //bad
     /** duration */ 4,
     /** percentage_permille */ 8,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.08}, {mean, -1}, {lower_limit, -15}, {upper_limit, 5}}},
    {/** event_id */ 7,
     /** mutually_exclusive_events */ {},
     /** text */ "Inflation Surges: Market Concerns Rise as Prices Soar", //bad
     /** duration */ 6,
     /** percentage_permille */ 12,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.12}, {mean, -3}, {lower_limit, -25}, {upper_limit, 0}}}
    };

// print a map
void print_map(std::map<unsigned int, std::vector<unsigned int>> map) {
    for (auto i : map) {
        std::cout << i.first << ": ";
        for (unsigned int j : i.second) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

/**
int main() {
    // This outputs 0.1
    std::cout << all_stock_events[0].modifiers[standard_deviation] << std::endl;
    // Checks the events for mutual exclusivity
    print_map(check_mutual_exclusivity(all_stock_events));
    // Outputs:
    // 0: 2
    // 1: 2
    // 2:
    //@todo Consider remove this example in the future.
    return 0;
}
*/

std::map<unsigned int, std::vector<unsigned int>> check_mutual_exclusivity(std::vector<Stock_event> all_events) {
    std::map<unsigned int, std::vector<unsigned int>> mut_excl_map;
    // Build the map
    for (unsigned int i = 0; i < all_events.size(); i++) {
        for (unsigned int j = 0; j < all_events[i].mutually_exclusive_events.size(); j++) {
            mut_excl_map[all_events[i].event_id].push_back(all_events[i].mutually_exclusive_events[j]);
        }
    }
    // If two events are mutually exclusive, they should be in each other's list.
    // Remove such two events from the map.
    // E.g. {0: [1,2], 1: [0], 2:[]} -> {0: [2]}
    // In this case, 2 does not state that it is mutually exclusive with 0.
    for (auto i : mut_excl_map) {
        for (unsigned int j : i.second) {
            if (std::find(mut_excl_map[j].begin(), mut_excl_map[j].end(), i.first) != mut_excl_map[j].end()) {
                mut_excl_map[i.first].erase(std::remove(mut_excl_map[i.first].begin(), mut_excl_map[i.first].end(), j), mut_excl_map[i.first].end());
                mut_excl_map[j].erase(std::remove(mut_excl_map[j].begin(), mut_excl_map[j].end(), i.first), mut_excl_map[j].end());
            }
        }
    }
    return mut_excl_map; // Add the missing return statement
}
