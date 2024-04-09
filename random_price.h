#ifndef RANDOM_PRICE_H
#define RANDOM_PRICE_H
/**
#ifndef 
#define are to prevent double include the header
*/
/**
* Initial Stock Price Generator
* if a=1 mean 5 sd 2; if a=2 mean 50 sd 20; if a=3 mean 150 sd 50;
*/
double init_stock_price(int a);
/**
* Stock Standard Deviation Generator (for both initial and after initial)
* mean 0.03*init_price; s.d. 0.02*init_price (yes, s.d. of s.d.)
*/
double random_sd(float init_price);
/**
* Random Stock Price Generator (non-initialising)
* requires mean, s.d., upper limit increase threshold (FRACTION of mean) and lower limit decrease threshold (FRACTION of mean)
* e.g. both 0.03; then the mean changes to exactly the new price if the value differ from mean by 3%
*/
double random_stock(float &mean, float &sd,float &upper_limit, float &lower_limit);
/**
* Random integer function in choosing stock type
*/
unsigned int random_integer(unsigned int max_integer);
#endif
