/**
 * @file events.h
 * @author eric15342335
 * @brief This file contains the definition of the events that will be applied to the stocks.
 */
#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <map>
#include <vector>

/**
 * @enum stock_modifiers
 * @brief The attributes of a stock that Events will modify are hardcoded here.
 * @note Please store them as `std::map<stock_modifiers, float>`.
 */
enum stock_modifiers {
    /** Amount of variation of the stock price percentage change. */
    standard_deviation,
    /** The expectation of the stock price percentage change.
     * For a normal distribution, this is the mean, median and mode.
     */
    mean,
    /** The lower limit of the stock price percentage change.
     * For example, if lower_limit is -10, then the percentage change will not go below -10%.
     * Note that stock initially has a lower limit of -40%. This value adds to that.
     * The value should be `[-100, 0]`.
     */
    lower_limit,
    /** The upper limit of the stock price percentage change.
     * For example, if upper_limit is 10, then the percentage change will not go over +10%.
     * Note that stock initially has a upper limit of +40%. This value adds to that.
     * The value should be `[0, 100]`.
     */
    upper_limit
};

/** @enum event_type
 * @brief The type of event that will be applied to the stocks
 * @note These objects does not have any values, they are used to specify the type of event.
 * @code {.cpp}
 * if (event.type_of_event == all_stocks) {
 *    // Apply the event to all stocks
 *     for (auto &stock : stocks) {
 *        stock.add_event(event);
 *     }
 * } else if (event.type_of_event == category) { ...
 * @endcode
 */
enum event_type {
    /** This event will apply to all stocks. */
    all_stocks,
    /** This event will apply to stocks within the specified category. */
    category,
    /** This event will apply to a randomly selected stock from all of the stocks available currently. */
    pick_random_stock
};

/**
 * @struct Stock_event events.h "events.h"
 * @brief The data structure of an event that will be applied to the stocks.
 * @note <b> For more information about how to write your own events,
 * visit the documentation of the @ref events.h "events.h" file. </b>
 */
struct Stock_event {
    public:
        /** The id of the event.
         * This is still required for checking, despite the fact that we are using a vector.
         */
        unsigned int event_id;

        /** A list of event_ids that this event is mutually exclusive with. */
        std::vector<unsigned int> mutually_exclusive_events;

        /** The text that will be displayed to the player. */
        std::string text;

        /** Number of rounds the event will last. If the event has duration <= 0 then it will be removed. */
        unsigned int duration;

        /** 0 to 1000, so 114 means 11.4% */
        unsigned int probability_permille;

        /** The type of event: Apply to all stocks, in one category or randomly? */
        event_type type_of_event;

        unsigned int category;

        /** Stores the stock_modifiers that the event applies. */
        std::map<stock_modifiers, float> modifiers;

        /** Overload the == operator to compare two Stock_event */
        bool operator==(const Stock_event & other) const {
            /** Events are the same if they have same event_id and same text.
             * The latter is because for type_of_event == pick_random_stock, the text is different.
             * But the event_id is the same.
             */
            return event_id == other.event_id && text == other.text;
        }
};

/** The list of all events that will be applied to the stocks. */
extern std::vector<Stock_event> all_stock_events;

/**
 * Pick a random event from the list of events
 * @param all_events The list of all events
 * @param num_events The number of events to pick
 * @return A vector of Stock_event
 */
std::vector<Stock_event> pick_events(std::vector<Stock_event> all_events, unsigned int num_events);

/**
 * If A is mutually exclusive with B, then B is mutually exclusive with A.
 * Check if these two events specifies each other as mutually exclusive in mutually_exclusive_events.
 * @param all_events The list of all events
 * @return A map of event_id to a vector of mutually exclusive event_ids that does not exist but should.
 */
std::map<unsigned int, std::vector<unsigned int> > check_mutual_exclusivity(std::vector<Stock_event> all_events);

/** Print a map to std::cout.
 * @param map The std::map object you want to print.
 */
void print_map(std::map<unsigned int, std::vector<unsigned int> > map);

#endif
