/**
 * @headerfile events.h
 * @brief This file contains the definition of the events that will be applied to the stocks.
 */
#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <map>
#include <vector>

/**
 * The attributes of a stock that Events will modify are hardcoded here.
 * Please store them as map<stock_modifiers, float> !
 */
enum stock_modifiers {
    standard_deviation,
    mean, /** 5 means the mean of normal_distribution is increased by 5% */
    lower_limit,
    upper_limit
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
 * The data structre of an event that will be applied to the stocks.
 * @struct Stock_event
 */
struct Stock_event {
    public:
        /** The id of the event.
         * This is still required for checking, despite the fact that we are using a vector.
         */
        unsigned int event_id;

        /** A list of event_ids that this event is mutually exclusive with */
        std::vector<unsigned int> mutually_exclusive_events;

        /** The text that will be displayed to the player */
        std::string text;

        /** How many rounds does this modifier (of the event) will apply */
        unsigned int duration;

        /** 0 to 1000, so 114 means 11.4% */
        unsigned int probability_permille;

        /** The type of event: Apply to all stocks, in one category or randomly? */
        event_type type_of_event;

        unsigned int category;

        /** Stores the stock_modifiers that the event applies. */
        std::map<stock_modifiers, float> modifiers;
};

/**
 * Pick a random event from the list of events
 * @param num_events The number of events to pick
 * @return A vector of Stock_event
 */
std::vector<Stock_event> pick_events(unsigned int num_events);

/**
 * If A is mutually exclusive with B, then B is mutually exclusive with A.
 * Check if these two events specifies each other as mutually exclusive in mutually_exclusive_events.
 * @param all_events The list of all events
 * @return A map of event_id to a vector of mutually exclusive event_ids that does not exist but should.
 */
std::map<unsigned int, std::vector<unsigned int>> check_mutual_exclusivity(std::vector<Stock_event> all_events);

/** Print a map to std::cout */
void print_map(std::map<unsigned int, std::vector<unsigned int>> map);

#endif
