/**
 * @headerfile stock.h
 * @author eric15342335
 */
#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include "events.h"

/**
 * @class Stock
 * @brief A class that represents a stock object in the game.
 * The stock has a name, price, quantity, category, money spent, events, attributes, and history.
 * The stock can be purchased, sold, and updated.
 */
class Stock {
    public:
        /** Constructor of the Stock object. */
        Stock(void);

        /**
         * Purchase a given number of stocks.
         * @param balance The balance ($) of the player. Pass-by-reference.
         * @param amount The number of stocks to purchase.
         * @param trading_fees_percent The trading fees percentage we charge the player.
         * @return Successful: Total cost of the purchase.
         *         Failed: -1 if the player does not have enough balance to buy the stock.
         */
        float purchase(float & balance, unsigned int amount, float trading_fees_percent);

        /**
         * Sell a given number of stocks.
         * @param balance The balance ($) of the player. Pass-by-reference.
         * @param amount The number of stocks to sell.
         * @param trading_fees_percent The trading fees percentage we charge the player.
         * @return Successful: Amount of money the player receive.
         *         Failed: -1 if the player does not have enough stocks to sell.
         */
        float sell(float & balance, unsigned int amount, float trading_fees_percent);

        /**
         * @param balance The balance of the player.
         * @param trading_fees_percent The trading fees percentage we charge the player.
         * @return Number of stocks that the player can afford with the balance.
         */
        unsigned int num_stocks_affordable(float balance, float trading_fees_percent);

        /**
         * Return the name of the caategory the stock belongs to.
         * @return Name of the category as a string.
         */
        std::string category_name(void);

        /**
         * Return the change of stock price using the most recent price and the current price
         * @return change in stock price.
         */
        float delta_price(void);

        /** Return the percentage of change of stock price.
         * @return Percentage of change in stock price. E.g. 0.05 means 5% increase in price.
         */
        float delta_price_percentage(void);

        /**
         * Get the total change of attribute of the stock due to events only. Getter function. \n
         * Example usage:
         * ```
         * stock.get_attribute(stock_modifiers::offset);
         * ```
         * @param attribute The attribute to get.
         * @return Total change of attribute due to Stock_event. Does not include the base value.
         */
        float sum_attribute(stock_modifiers attribute);

        /**
         * Call this when the game proceed to next round.
         * @todo Finish the implementation of this function.
         *       This function should update the stock price based on the standard deviation and skewness
         *       by calling functions in random_price.h file that Jeremy will provide.
         *       It should remove the obselete events from the linked list
         *       and update the history array with the current price too.
         */
        void next_round(void);

        /** Add an event to the stock.
         * @param event The event to be added. See events.h for more information about the
         * class Stock_Event.
         */
        void add_event(Stock_event event);

        /**
         * Get the stock price of recent rounds.
         * @param rounds The number of rounds to look back. 5 means the last 5 rounds.
         * @return A vector of stock prices.
         *         If the number of rounds is greater than the history size, return the whole history.
         *         Otherwise, return the most recent rounds.
         *         If the history is empty, return an empty vector.
         */
        std::vector<float> return_most_recent_history(unsigned int rounds);

        /**
         * Get the name of the stock. Getter function.
         * @return Name of the stock as float.
         */
        std::string get_name(void) {
            return name;
        }

        /**
         * Get the price of the stock. Getter function.
         * @return Price of the stock as float.
         */
        float get_price(void) {
            return price;
        }

        /**
         * Get the category of the stock. Getter function.
         * @return Category of the stock as unsigned int.
         */
        unsigned int get_category(void) {
            return category;
        }

        /**
         * Get the quantity of the stock. Getter function.
         * @return Quantity of the stock as float.
         */
        unsigned int get_quantity(void) {
            return quantity;
        }

        /**
         * Get the money spent on the stock. Getter function.
         * @return Money spent on the stock as float.
         */
        float get_money_spent(void) {
            return money_spent;
        }

        /**
         * Get the initial price of the stock. Getter function.
         * @return Initial price of the stock as float.
         */
        float get_initial_price(void) {
            return history[0];
        }

        /**
         * Get the base value of stock_attributes of the stock. Getter function.
         * @param attribute The attribute to get. E.g. standard_deviation, mean, lower_limit, upper_limit
         * @return Base value of stock_attributes as float.
         */
        float get_attribute(stock_modifiers attribute) {
            return attributes[attribute];
        }

        /**
         * Get size of the history.
         * @return Size of the history as unsigned int.
         */
        unsigned int get_history_size(void) {
            return history.size();
        }

        /**
         * Change the mean of the stock by delta_mean. Setter function.
         * @param delta_mean The change in mean.
         */
        void change_mean(float delta_mean) {
            attributes[mean] += delta_mean;
        }

    private:
        /** Name of the stock that we assigned to it. */
        std::string name;
        /** Current price of the stock. */
        float price;
        /** Number of stocks the player has purchased. */
        unsigned int quantity;
        /** Use numbers to represent the category of the stock. The range of the numbers
         * should be `[0, category_list_size - 1]`. See names.cpp for more information.
         */
        unsigned int category;
        /** Amount of money the player has spent on buying this stock. */
        float money_spent;

        /** Stores all the events that will apply to this stock specifically. */
        std::list<Stock_event> events;
        /** Stores the initial value of the stock_modifiers (e.g. standard deviation, mean and limits). */
        std::map<stock_modifiers, float> attributes;
        /** Contains the stock price history. First element (index 0) is the oldest. */
        std::vector<float> history;

        /** Update the history array with the current price */
        void update_history(void);

        /** Remove obselete events from the list `events` that durations are
         * less than/equal to 0 (In other words, expired).
         * For internal use after the `Stock::next_round` function is called.
         */
        void remove_obselete_event(void);
};

#endif
