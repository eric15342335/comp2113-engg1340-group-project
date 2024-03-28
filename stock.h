#ifndef STOCK_H
#define STOCK_H

#include <string>
using namespace std;
class Stock {
    public:
        double purchase(double &balance, unsigned int amount);
        double sell(double &balance, unsigned int amount);
        unsigned int num_stocks_affordable(double balance);
        void init(void);
        string category_name(void);
        // todo: double delta_price(void) function
        // todo: double delta_price_percentage(void) function
        // todo: void next_round(void) function
        // todo: void event_modifier(double sd, double skew, unsigned int duration) function
    private:
        string name;
        double price;
        unsigned int quantity; // # of stocks player has
        double sd; // standard deviation
        double skew; // skewness
        unsigned int category; // category names in names.h
        // todo: stock history using linked list
        // todo: event offsets & duration using linked list
        /* e.g.
        [[sd_change_1, skew_change_1, duration_1],
         [sd_change_2, skew_change_2, duration_2], ...]
        */
        // In case multiple events apply modifiers to the same stock
        
};

#endif
