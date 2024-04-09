// stores the event texts and modifiers
#include "events.h"
#include <iostream>

Stock_event example {
    /* text */ "The company has released a new product, received many positive reviews.",
    /* duration */ 5,
    /* percentage_permille */ 100,
    /* type_of_event */ all_stocks,
    /* category */ 0,
    /* modifiers*/ {
        {standard_deviation, 0.1},
        {skewness, 0.1}
    }
};

double Stock_event::get_modifier(stock_modifiers modifier) {
    return modifiers[modifier];
}

/*
int main() {
    std::cout << example.get_modifier(stock_modifiers::standard_deviation) << std::endl;
    // This outputs 0.1
}
*/
