/**
 * @headerfile stock.h
 * @author eric15342335
 * @brief Declaration of the Stock class.
 */
#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include "events.h"

/**
 * @class Stock stock.h "stock.h"
 * @brief A class that represents a stock object in the game.
 * The stock has a name, price, quantity, category, money spent, events, attributes, and history.
 * The stock can be purchased, sold, and updated.
 * @note Example usage:
 * @code {.cpp}
 * Stock stock;   // Create a stock object. The constructor will initialize the stock automatically.
 * float balance = 1000;
 * stock.purchase(balance, 1, 0.01);    // Purchase a stock.
 * stock.sell(balance, 1, 0.01);        // Sell a stock.
 * std::string name = stock.getName(); // What is the name of the stock?
 * // Get the upper limit of the percentage change of the stock price:
 * float upper_limit = stock.getStockAttribute(upper_limit) + stock.sumEventModifiersAttribute(upper_limit);
 * @endcode
 */
class Stock {
    public:
        /** @brief Constructor of the Stock object. */
        Stock(void);

        /**
         * @brief Purchase a given number of stocks.
         * @param balance The balance ($) of the player. Pass-by-reference.
         * @param amount The number of stocks to purchase.
         * @param trading_fees_percent The trading fees percentage we charge the player.
         * @return Successful: Total cost of the purchase.
         *         Failed: -1 if the player does not have enough balance to buy the stock.
         */
        float purchase(float & balance, unsigned int amount, float trading_fees_percent);

        /**
         * @brief Sell a given number of stocks.
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
        unsigned int getAffordableQuantity(float balance, float trading_fees_percent);

        /**
         * @brief Return the name of the category the stock belongs to.
         * @return Name of the category as a string.
         */
        std::string getCategoryName(void);

        /**
         * @brief Return the change of stock price using the most recent price and the current price
         * @return change in stock price.
         */
        float deltaPrice(void);

        /** @brief Return the percentage of change of stock price.
         * @return Percentage of change in stock price. E.g. 0.05 means 5% increase in price.
         */
        float deltaPercentagePrice(void);

        /**
         * @brief Get the total change of attribute of the stock due to events only. Getter function. \n
         * Example usage: @code {.cpp}
         * std::cout << stock.getStockAttribute(stock_modifiers::standard_deviation);
         * @endcode {.cpp}
         * @param attribute The attribute to get. @ref stock_modifiers
         * @return Total change of attribute due to Stock_event. Does not include the base value.
         */
        float sumEventModifiersAttribute(stock_modifiers attribute);

        /**
         * @brief Call this when the game proceed to next round.
         */
        void gotoNextRound(void);

        /** @brief Add an event to the stock.
         * @param event The event to be added. See events.h for more information about the
         * class Stock_Event.
         */
        void addEvent(Stock_event event);

        /**
         * @brief Get the stock price of recent rounds.
         * @param rounds The number of rounds to look back. 5 means the last 5 rounds.
         * @return A vector of stock prices.
         *         If the number of rounds is greater than the history size, return the whole history.
         *         Otherwise, return the most recent rounds.
         *         If the history is empty, return an empty vector.
         */
        std::vector<float> returnMostRecentHistory(unsigned int rounds);

        /**
         * @brief Get the name of the stock. Getter function.
         * @return Name of the stock as float.
         */
        std::string getName(void) { return name; }

        /**
         * @brief Get the price of the stock. Getter function.
         * @return Price of the stock as float.
         */
        float getPrice(void) { return price; }

        /**
         * @brief Get the category of the stock. Getter function.
         * @return Category of the stock as unsigned int.
         */
        unsigned int getCategory(void) { return category; }

        /**
         * @brief Get the quantity of the stock. Getter function.
         * @return Quantity of the stock as float.
         */
        unsigned int getQuantity(void) { return quantity; }

        /**
         * @brief Get the money spent on the stock. Getter function.
         * @return Money spent on the stock as float.
         */
        float getMoneySpent(void) { return spentMoney; }

        /**
         * @brief Get the initial price of the stock. Getter function.
         * @return Initial price of the stock as float.
         */
        float getInitPrice(void) { return history[0]; }

        /**
         * @brief Get the base value of stock_attributes of the stock. Getter function.
         * @param attribute The attribute to get. E.g. standard_deviation, mean, lower_limit, upper_limit
         * @return Base value of stock_attributes as float.
         */
        float getStockAttribute(stock_modifiers attribute) { return attributes[attribute]; }

        /**
         * @brief Get size of the history.
         * @return Size of the history as unsigned int.
         */
        unsigned int getSizeOfHistory(void) { return history.size(); }

        /**
         * @brief Change the mean of the stock by delta_mean. Setter function.
         * @param delta_mean The change in mean.
         */
        void changeMean(float delta_mean) { attributes[mean] += delta_mean; }

        /**
         * @brief Return all the events that will apply to this stock specifically. Getter function.
         * @return A list of Stock_event.
         */
        std::list<Stock_event> getAllEvents(void) { return events; }

        /**
         * @brief Check if we can add the event to the stock.
         *
         * A event can be added if the event is not mutually exclusive with any of the existing events.
         * @param event The event to be added.
         * @return True if the event can be added. False otherwise.
         */
        bool canAddEvent(Stock_event event);

    private:
        /** @brief Name of the stock that we assigned to it. */
        std::string name;
        /** @brief Current price of the stock. */
        float price;
        /** @brief Number of stocks the player has purchased. */
        unsigned int quantity;
        /** @brief Use numbers to represent the category of the stock. The range of the numbers
         * should be `[0, sizeofCategoryList - 1]`. See names.cpp for more information.
         */
        unsigned int category;
        /** @brief Amount of money the player has spent on buying this stock. */
        float spentMoney;

        /** @brief Stores all the events that will apply to this stock specifically. */
        std::list<Stock_event> events;
        /** @brief Stores the initial value of the stock_modifiers (e.g. standard deviation, mean and limits). */
        std::map<stock_modifiers, float> attributes;
        /** @brief Contains the stock price history. First element (index 0) is the oldest. */
        std::vector<float> history;

        /** Update the history array with the current price */
        void updatePriceHistory(void);

        /** @brief Remove obselete events from the list `events` that durations are
         * less than/equal to 0 (In other words, expired).
         * @note For internal use after the `Stock::gotoNextRound` function is called.
         */
        void removeObseleteEvent(void);
};

#endif
