/** 
 * @headerfile events.h
 * @brief This file contains the definition of the events that will be applied to the stocks.
*/
#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <map>

/**
 * The attributes of a stock that Events will modify are hardcoded here.
 * Please store them as map<stock_modifiers, float> !
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

/**
 * The class that stores the event that will be applied to the stocks
*/
struct Stock_event {
    public:
        /** The text that will be displayed to the player */
        std::string text; 
        /** How many rounds does this modifier (of the event) will apply */
        unsigned int duration;
        /** 0 to 1000, so 114 means 11.4% */
        unsigned int probability_permille; 
        /** The type of event */
        event_type type_of_event;
        /** Stock categories names are hardcoded in names.h */
        unsigned int category;
        /** The type of modifier */
        std::map<stock_modifiers, float> modifiers;

        /**
         * Get the value of a specific type of modifiers
         */
        float get_modifier(stock_modifiers modifier);
};

#endif
