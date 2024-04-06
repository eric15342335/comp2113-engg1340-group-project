#ifndef EVENTS_H
#define EVENTS_H

#include <string>
using namespace std;

struct Stock_event {
    public:
        string text;
        double sd;
        double skew;
        unsigned int duration;
        unsigned int probability_permille; // 0 to 1000, so 114 means 11.4%
        unsigned int type_of_event;
        // 0 means apply to all stocks, 1 means apply to stocks in a category
        // 2 means apply to a randomly selected stock
        unsigned int category; // if type is 1, the event will happen to stocks in this category
};

#endif
