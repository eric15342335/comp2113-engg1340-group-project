#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include "events.h"
using namespace std;

class Stock {
    public:
        double purchase(double & balance, unsigned int amount, double trading_fees_percent);
        double sell(double & balance, unsigned int amount, double trading_fees_percent);
        unsigned int num_stocks_affordable(double balance, double trading_fees_percent);
        void init(void);
        string category_name(void);
        void delete_memory(void);
        double delta_price(void);
        double delta_price_percentage(void);
        double get_true_sd(void);
        double get_true_skewness(void);
        void testing_set_attributes(string name, double price, unsigned int quantity, double sd, double skew, unsigned int category);
        // todo: void next_round(void) function
        // todo: void event_modifier(double sd, double skew, unsigned int duration) function

    private:
        string name;
        double price;
        unsigned int quantity; // # of stocks player has
        double sd;             // standard deviation
        double skew;           // skewness
        unsigned int category; // category names in names.h

        vector<double> history;
        void update_history(void);
        vector<double> return_most_recent_history(int rounds);

        void remove_obselete_event(void);
        /* TODO: Summarize the above code to README.md:
        "Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)"
        */

        struct Event_Modifier {
            public:
                double sd_change;
                double skew_change;
                unsigned int duration;
                Event_Modifier * next;
        };

        Event_Modifier * event_modifier_head = nullptr;
        void add_event(Stock_event event);
};

#endif
