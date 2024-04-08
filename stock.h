/**
 * @headerfile stock.h
 * @author eric15342335
 */
#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include "events.h"
using namespace std;

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
        double purchase(double & balance, unsigned int amount, double trading_fees_percent);

        /**
         * Sell a number of stocks
         * @param balance The balance ($) of the player. Pass-by-reference
         * @param amount The number of stocks to sell
         * @param trading_fees_percent The trading fees percentage we charge the player
         * @return Successful: Amount of money the player receive.
         *         Failed: -1 if the player does not have enough stocks to sell
         */
        double sell(double & balance, unsigned int amount, double trading_fees_percent);

        /**
         * @param balance The balance of the player
         * @param trading_fees_percent The trading fees percentage we charge the player
         * @return Number of stocks that the player can afford with the balance
         */
        unsigned int num_stocks_affordable(double balance, double trading_fees_percent);

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
        string category_name(void);

        /**
         * Delete the linked list that stores event modifiers in order to free memory
         */
        void delete_memory(void);

        /**
         * Return the change of stock price using the most recent price and the current price
         * @return change in stock price
         */
        double delta_price(void);

        /** Return the percentage of change of stock price using Stock::delta_price();
         * @return percentage of change in stock price
         */
        double delta_price_percentage(void);

        /**
         * Return the standard deviation value of the stock
         * after applying the event modifiers
        @return standard deviation value of the stock
        */
        double get_true_sd(void);

        /**
         * Return the skewness value of the stock
         * after applying the event modifiers
        @return skewness value of the stock
        */
        double get_true_skewness(void);

        /**
         * Set the attributes of the stock for testing purposes
         * @param name The name of the stock
         * @param price The price of the stock
         * @param quantity The quantity of the stock
         * @param sd The standard deviation of the stock
         * @param skew The skewness of the stock
         * @param category The category of the stock
         */
        void testing_set_attributes(string name, double price, unsigned int quantity, double sd, double skew, unsigned int category);

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
        string name;            // name of the stock
        double price;           // current price of the stock
        unsigned int quantity;  // number of stocks player has
        double sd;              // standard deviation value of the stock
        double skew;            // skewness value of the stock
        unsigned int category;  // stores category numbers, where the names are stored in names.h
        double money_spent;     // total money spent on purchasing the stock
        vector<double> history; // History of stock prices for the stock object

        /** Update the history array with the current price */
        void update_history(void);

        /**
         * Return the most recent stock prices
         * @param rounds The number of rounds to look back
         * @return Most recent price being the *last* element in the vector.
         *         If the number of rounds is greater than the size of the history array,
         *         return the entire history
        */
        vector<double> return_most_recent_history(int rounds);

        /**
         * Loop through the Event_Modifier linked list and remove the obselete event
         * obselete events are events that have duration <= 0
         * Internal use after the "next_round" function is called
         */
        void remove_obselete_event(void);

        /**
         * The Node of the Event_Modifier linked list.
         * The members should keep consistent with Stock_event in events.h
         */
        struct Event_Modifier {
            public:
                /** Standard deviation offset */
                double sd_change;
                /** Skewness offset */
                double skew_change;
                /**
                 * The duration is decremented by 1 each round
                 * When the duration reaches 0, the event is removed from the linked list
                 */
                unsigned int duration;
                /** Pointer to the next node in the linked list */
                Event_Modifier * next;
        };

        /** Head pointer of the linked list, initially set to nullptr */
        Event_Modifier * event_modifier_head = nullptr;
};

#endif
