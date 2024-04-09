#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <map>

/**
 * The attributes of a stock that Events will modify are hardcoded here.
 * Please store them as map<stock_modifiers, double> !
*/
enum stock_modifiers {
    standard_deviation,
    skewness
};

/**
 * The type of event that will be applied to the stocks
*/
enum event_type {
    all_stocks,
    category,
    pick_random_stock
};

struct Stock_event {
    public:
        std::string text; /** The text that will be displayed to the player */
        unsigned int duration; /** How many rounds does this modifier (of the event) will apply */
        unsigned int probability_permille; /** 0 to 1000, so 114 means 11.4% */
        event_type type_of_event;
        /** Stock categories names are hardcoded in names.h */
        unsigned int category;
        /** The type of modifier */
        std::map<stock_modifiers, double> modifiers;

        /**
         * Get the value of a specific type of modifiers
         */
        double get_modifier(stock_modifiers modifier);
};

#endif
