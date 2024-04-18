/** @file events.cpp
 * stores the event texts and modifiers
 */
#include "events.h"
#include <iostream>
#include <algorithm>

/** The list of all events that can be applied to the stocks */
std::vector<Stock_event> all_stock_events = {
    {/** event_id */ 0,
     /** mutually_exclusive_events */ {1, 2},
     /** text */ "The FED has decreased the interest rate!",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, 2}, {lower_limit, 0}, {upper_limit, 20}}},
    {/** event_id */ 1,
     /** mutually_exclusive_events */ {0, 2},
     /** text */ "The FED has increased the interest rate!",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, -2}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 2,
     /** mutually_exclusive_events */ {},
     /** text */ "This event is used for testing the mutual exclusivity function!",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0}, {mean, 0}, {lower_limit, 0}, {upper_limit, 0}}}};

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

std::vector<Stock_event> pick_events(std::vector<Stock_event> all_events, unsigned int num_events) {
    std::vector<Stock_event> picked_events;
    // Pick num_events random events
    for (unsigned int i = 0; i < num_events; i++) {
        // When picking the event, consider event.probability_permille.
        unsigned int total_permille = 0;
        for (Stock_event event : all_events) {
            total_permille += event.probability_permille;
        }
        unsigned int random_permille = rand() % total_permille;
        for (Stock_event event : all_events) {
            total_permille -= event.probability_permille;
            if (total_permille <= random_permille) {
                picked_events.push_back(event);
                break;
            }
        }
    }
    // Check event duplication and mutual exclusivity
    std::map<unsigned int, std::vector<unsigned int>> mut_excl_map = check_mutual_exclusivity(all_events);
    for (unsigned int i = 0; i < picked_events.size(); i++) {
        for (unsigned int j = i + 1; j < picked_events.size(); j++) {
            // If two events are the same, remove one of them
            // Note that we don't remove the duplicate events with type_of_event == pick_random_stock
            if (picked_events[i].event_id == picked_events[j].event_id &&
                picked_events[i].type_of_event != pick_random_stock) {
                picked_events.erase(picked_events.begin() + j);
                j--;
            }
            // If two events are mutually exclusive, remove one of them
            else if (std::find(mut_excl_map[picked_events[i].event_id].begin(), mut_excl_map[picked_events[i].event_id].end(), picked_events[j].event_id) != mut_excl_map[picked_events[i].event_id].end()) {
                picked_events.erase(picked_events.begin() + j);
                j--;
            }
        }
    }
    return picked_events;
}