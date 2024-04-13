/** @file events.cpp
 * stores the event texts and modifiers
 */
#include "events.h"
// #include <iostream>

Stock_event example = {
    /** text */ "The FED has decreased the interest rate!",
    /** duration */ 5,
    /** percentage_permille */ 100,
    /** type_of_event */ all_stocks,
    /** category */ 0,
    /** modifiers*/ {{standard_deviation, 0.1},{mean, 1.02}, {lower_limit, 0}, {upper_limit, 20}}
};

float Stock_event::get_modifier(stock_modifiers modifier) {
    return modifiers[modifier];
}

/**
int main() {
    std::cout << fed_decrease_interest_rate.get_modifier(stock_modifiers::standard_deviation) << std::endl;
    // This outputs 0.1
}
*/
