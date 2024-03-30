#ifndef STOCK_H
#define STOCK_H

#include <string>
#include "events.h"
using namespace std;

class Stock {
    public:
        double purchase(double &balance, unsigned int amount);
        double sell(double &balance, unsigned int amount);
        unsigned int num_stocks_affordable(double balance);
        void init(void);
        string category_name(void);
        void delete_memory(void);
        double delta_price(void);
        double delta_price_percentage(void);
        double get_true_sd(void);
        double get_true_skewness(void);
        // todo: void next_round(void) function
        // todo: void event_modifier(double sd, double skew, unsigned int duration) function

    private:
        string name;
        double price;
        unsigned int quantity; // # of stocks player has
        double sd; // standard deviation
        double skew; // skewness
        unsigned int category; // category names in names.h

        // dynamic array storing history
        // since we don't need to delete history
        // a linked list is not necessary
        int history_array_size = 10;
        double * history = new double[history_array_size];
        int history_index = 0; // index of the next element to be added
        void initialize_history(void);
        void update_history(void);
        void remove_obselete_event(void);
        /* TODO: Summarize the above code to README.md:
        "Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)"
        */

        struct Event_Modifier {
            double sd_change;
            double skew_change;
            unsigned int duration;
            Event_Modifier * next;
        };

        Event_Modifier * event_modifier_head = nullptr;
        void add_event(Stock_event event);

};

#endif
