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

/** A class that represents a stock object in the game. */
class Stock {
    public:
        /**
         * Purchase a given number of stocks
         * @param balance The balance ($) of the player. Pass-by-reference
         * @param amount The number of stocks to purchase
         * @param trading_fees_percent The trading fees percentage we charge the player
         * @return Successful: Total cost of the purchase.
         *         Failed: -1 if the player does not have enough balance to buy the stock
         */
        float purchase(float & balance, unsigned int amount, float trading_fees_percent);

        /**
         * Sell a number of stocks
         * @param balance The balance ($) of the player. Pass-by-reference
         * @param amount The number of stocks to sell
         * @param trading_fees_percent The trading fees percentage we charge the player
         * @return Successful: Amount of money the player receive.
         *         Failed: -1 if the player does not have enough stocks to sell
         */
        float sell(float & balance, unsigned int amount, float trading_fees_percent);

        /**
         * @param balance The balance of the player
         * @param trading_fees_percent The trading fees percentage we charge the player
         * @return Number of stocks that the player can afford with the balance
         */
        unsigned int num_stocks_affordable(float balance, float trading_fees_percent);

        /**
         * Call this function to create a new stock.
         * It assign a random price, standard deviation,
         * skewness, and category to it. Also, generate a name based on the category.
         * Should be called only once.
         */
        void init(void);

        /**
         * Return the name of the caategory the stock belongs to
         * @return Name of the category as a string
         */
        std::string category_name(void);

        /**
         * Return the change of stock price using the most recent price and the current price
         * @return change in stock price
         */
        float delta_price(void);

        /** Return the percentage of change of stock price using Stock::delta_price();
         * @return percentage of change in stock price
         */
        float delta_price_percentage(void);

        /**
         * Return the sum of a specific attribute of the stock.
         * For example, to get the sum of standard deviation of all stocks:
         * stock.sum_attribute(stock_modifiers::standard_deviation);
         * @param attribute The attribute to sum up
         * @return The sum of the attribute
         */
        float sum_attribute(stock_modifiers attribute);

        /**
         * Proceed to next round
         * @todo Finish the implementation of this function.
         *       This function should update the stock price based on the standard deviation and skewness
         *       by calling functions in random_price.h file that Jeremy will provide.
         *       It should remove the obselete events from the linked list
         *       and update the history array with the current price too.
         */
        void next_round(void);

        /**
         * Add an event to the stock
         * @param event The event to be added. See events.h for more information.
         */
        void add_event(Stock_event event);

    private:
        std::string name;            /** name of the stock */
        float price;                /** current price of the stock */
        unsigned int quantity;       /** number of stocks player has */
        unsigned int category;       /** stores category numbers, where the names are stored in names.h */
        float money_spent;          /** total money spent on purchasing the stock */
        
        std::list<Stock_event> events; /** List of events that will modify the stock */
        std::map<stock_modifiers, float> attributes; /** The attributes of the stock */
        std::vector<float> history; /** The history of stock prices */

        void update_history(void); /** Update the history array with the current price */

        /**
         * Remove obselete events that has duration <= 0
         * Internal use after the "next_round" function is called
         */
        void remove_obselete_event(void);

        /**
         * Return the most recent stock prices
         * @param rounds The number of rounds to look back
         * @return Most recent price being the *last* element in the vector.
         *         If the number of rounds is greater than the size of the history array,
         *         return the entire history
         */
        std::vector<float> return_most_recent_history(int rounds);
};

#endif
