#ifndef RANDOM_PRICE_H
#define RANDOM_PRICE_H

/*
#ifndef
#define are to prevent double include the header
*/

/**
 * Initial Stock Price Generator
 * if price_profile=2 mean 50 sd 20; if price_profile=3 mean 150 sd 50; else mean 5 sd 2;
 *Stock prices cluster in 3 tiers in our world: about 5 hkd (a=ELSE) variating about 2 hkd; , 50 hkd(a=2) variating about 20 hkd,
 *and 150 hkd(a=3)variating about 50 hkd (based on a very little sample observation of real world).
 */
double init_stock_price(int a);
/**
 * Stock Standard Deviation Generator (for both initial and after initial)
 * s.d. usually 1%-5% of initial stock price;
 * modelling with absolute value of norm dist mean 0.03*init_price; s.d. 0.02*init_price (yes, s.d. of s.d.)
 */
double random_sd(float init_price);
/**
 * Random Stock Price Generator (non-initialising)
 * requires mean, s.d., upper limit increase threshold (FRACTION of mean) and lower limit decrease threshold (FRACTION of mean)
 * e.g. both 0.03; then the mean changes to exactly the new price if the value differ from mean by 3%
 */
double random_stock(float & mean, float & sd, float & upper_limit, float & lower_limit);
/**
 * Random integer function in choosing stock type
 * Return a random integer from 0 to max - 1
 */
unsigned int random_integer(unsigned int max_integer);
#endif
