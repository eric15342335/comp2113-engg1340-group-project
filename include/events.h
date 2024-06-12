/// @file events.h
/// Implements event-related data structures and (declarations of) such functions.
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

#ifndef EVENTS_H
#define EVENTS_H

#include <istream>
#include <map>
#include <sstream>
#include <string>
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
     * For example, if lower_limit is -10, then the percentage change will not go below
     * -10%. Note that stock initially has a lower limit of -40%. This value adds to
     * that. The value should be `[-100, 0]`.
     */
    lower_limit,
    /** The upper limit of the stock price percentage change.
     * For example, if upper_limit is 10, then the percentage change will not go over
     * +10%. Note that stock initially has a upper limit of +40%. This value adds to
     * that. The value should be `[0, 100]`.
     */
    upper_limit
};

/// @brief Multiplier for mean
constexpr float meanMultiplier = 0.6f;

/// @brief Multiplier for standard deviation
const float sdMultiplier = 7.5f;

/// @brief Lower limit multiplier
const float lowerLimitMultiplier = 0.2;

/// @brief Upper limit multiplier
const float upperLimitMultiplier = 0.2;

/// @brief Default lower limit
const float defaultLowerLimit = -5;

/// @brief Default upper limit
const float defaultUpperLimit = 5;

/// @brief Default mean
constexpr float defaultMean = 0.5f / meanMultiplier;

/// @brief Rate of decrease of duration
const unsigned int durationDecreaseMultiplier = 2;

/** @enum event_type
 * @brief The type of event that will be applied to the stocks
 * @note These objects does not have any values, they are used to specify the type of
 * event.
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
    /** This event will apply to a randomly selected stock from all of the stocks
       available currently. */
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
        /** @brief The id of the event.
         * This is still required for checking, despite the fact that we are using a
         * vector.
         */
        unsigned int event_id;

        /** @brief A list of event_ids that this event is mutually exclusive with. */
        std::vector<unsigned int> mutually_exclusive_events;

        /** @brief The text that will be displayed to the player. */
        std::string text;

        /** @brief Number of rounds the event will last. If the event has duration <= 0
         * then it will be removed. */
        unsigned int duration;

        /** @brief 0 to 1000, so 114 means 11.4% */
        unsigned int probability_permille;

        /** @brief The type of event: Apply to all stocks, in one category or randomly?
         */
        event_type type_of_event;

        unsigned int category;

        /** @brief Stores the stock_modifiers that the event applies. */
        std::map<stock_modifiers, double> modifiers;

        /** @brief Overload the == operator to compare two Stock_event */
        bool operator==(const Stock_event & other) const {
            return event_id == other.event_id && text == other.text &&
                   probability_permille == other.probability_permille &&
                   type_of_event == other.type_of_event && category == other.category &&
                   modifiers == other.modifiers;
        }

        /**
         * @brief Serialize the event as std::ostream object.
         * @param outputstream The std::ostream object to write the data.
         * @param event The event object to get the data from.
         * @return A std:ostream object contains all the data of the event.
         * @code
         * // Create a event object by calling the constructor
         * Stock_event event;
         * // Print the data of the event.
         * std::cout << event << std::endl;
         * @endcode
         */
        friend std::ostream & operator<<(
            std::ostream & outputstream, const Stock_event & event) {
            outputstream << event.event_id << " ";
            for (unsigned int i = 0; i < event.mutually_exclusive_events.size(); i++) {
                outputstream << event.mutually_exclusive_events[i] << " ";
            }
            outputstream << ";" << event.text << ";" << event.duration << " "
                         << event.probability_permille << " " << event.type_of_event
                         << " " << event.category << " ";
            for (const auto & modifier : event.modifiers) {
                outputstream << modifier.second << " ";
            }
            return outputstream;
        }

        /**
         * @brief Deserialize the event from a std::istream object.
         * @param inputstream The std::istream object to read the data.
         * @param event The event object to store the data.
         * @return A std:istream object contains all the data of the event.
         */
        friend std::istream & operator>>(
            std::istream & inputstream, Stock_event & event) {
            // fix the bug that mutually_exclusive_events is not read correctly
            inputstream >> event.event_id;
            std::string _mutually_exclusive_events;
            std::getline(inputstream, _mutually_exclusive_events, ';');
            std::istringstream mutually_exclusive_events_stream(
                _mutually_exclusive_events);
            unsigned int temp_id;
            while (mutually_exclusive_events_stream >> temp_id) {
                event.mutually_exclusive_events.emplace_back(temp_id);
            }
            std::getline(inputstream, event.text, ';');
            unsigned int temp_type;
            inputstream >> event.duration >> event.probability_permille >> temp_type >>
                event.category;
            event.type_of_event = static_cast<event_type>(temp_type);
            inputstream >> event.modifiers[standard_deviation] >>
                event.modifiers[mean] >> event.modifiers[lower_limit] >>
                event.modifiers[upper_limit];
            return inputstream;
        }
};

/** @brief The list of all events that will be applied to the stocks. */
extern const std::vector<Stock_event> all_stock_events;

/**
 * @brief Pick a random event from the list of events
 * @param all_events The list of all events
 * @param num_events The number of events to pick
 * @return A vector of Stock_event
 */
std::vector<Stock_event> pick_events(
    const std::vector<Stock_event> & all_events, unsigned int num_events);

/**
 * @brief If A is mutually exclusive with B, then B is mutually exclusive with A.
 * Check if these two events specifies each other as mutually exclusive in
 * mutually_exclusive_events.
 * @param all_events The list of all events
 * @return A map of event_id to a vector of mutually exclusive event_ids that does not
 * exist but should.
 */
std::map<unsigned int, std::vector<unsigned int>> check_mutual_exclusivity(
    const std::vector<Stock_event> & all_events);

/**
 * @brief Check if there are mutual exclusivity violations in all_stock_events.
 * @return True if the events are mutually exclusive with each other.
 */
bool assertion_check_mutual_exclusivity(void);

/** @brief Print a map to std::cout.
 * @param map The std::map object you want to print.
 */
void print_map(const std::map<unsigned int, std::vector<unsigned int>> & map);

Stock_event getStockSplitEvent(void);

/**
 * @brief Filter out the events that are mutually exclusive with each other,
 * or events that are identical (except for event_type::pick_random_stock).
 * @param picked_events The list of events to filter.
 * @return A list of events that are mutually exclusive with each other.
 */
std::vector<Stock_event> uniq_events(std::vector<Stock_event> picked_events);

void assertion_check_uniq_events(void);

#endif
