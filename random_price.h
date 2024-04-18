#ifndef RANDOM_PRICE_H
#define RANDOM_PRICE_H
/*
#ifndef
#define are to prevent double include the header
*/

/**
 * Initial Stock Price Generator
 * - if a=1 mean 5 s.d. 2;
 * - if a=2 mean 50 s.d. 20;
 * - if a=3 mean 150 s.d. 50;
 */
float init_stock_price(int a);
// there is ABSOLUTELY nothing at line 15
/**
 * Initiaises a reasonable standard deviation; first around 0.5, second around 3, third around 10
 */
float init_sd(int price_profile);

/**
 * There is a upper limit and lower limit that the realisation of the % change must fall between.
 * - All data is raken from a stock class.
 * As each round pass we allow for more and more chaotic behaviour by making the bounds less tight.
 * - where n is number of rounds
 * - The rate this happens is n^2/15 for upper bound
 * - and n for lower bound before lower bound reach -100
 * - just for fun (chaotic evil smirk). Upon devastating events which leads to
 * a stock price only 10 % left of it's initial, we increase mean to prevent a game over.
 * Upon we are 90.32% sure the bounds would be wrong we bump the mean/
 */
float percentage_change_price(Stock & stock);

/**
 * Random integer function in choosing stock type
 * Return a random integer from 0 to max - 1
 */
unsigned int random_integer(unsigned int max_integer);
#endif
