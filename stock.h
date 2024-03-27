#ifndef STOCK_H
#define STOCK_H

#include <string>
using namespace std;
class Stock {
    public:
        double purchase(double &balance, unsigned int amount);
        double sell(double &balance, unsigned int amount);
        void init(void);
        string category_name(void);
    private:
        string name;
        double price;
        unsigned int quantity;
        double sd; // standard deviation
        double skew; // skewness
        unsigned int category;
        /* 0: tech, 1: finance, 2: healthcare, 3: consumer, 4: energy
        */
};

#endif
