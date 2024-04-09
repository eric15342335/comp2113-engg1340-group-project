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
float init_stock_price(int a);

/**records % change of stock. Should use stock_price(k+1th) = (1+stock_change(mode)/100)*stock_price_kth to calculate raw stock price.
 *default: Non-increasing (mean 0% s.d. 0.5%)
 *mode=1: Increasing moderately (mean 0.5% s.d. 0.5%)
 *mode=2: Decreasing moderately (mean -0.5% s.d. 0.5%)
 *mode=3: Increasing rapidly (mean 2% s.d. 1%)
 *mode=4: Decreasing rapidly (mean -2% s.d. 1%)
 *mode=5: Skyrocketing (mean 10% s.d. 3%)
 *mode=6: Plumetting (mean -10% s.d. 3%)
 *mode=7: Generally increasing but unstable (mean 0.5% s.d. 3%)
 *mode=8: Generally decreasing but unstable (mean -0.5% s.d. 3%)
 *mode=9: Unstable w/o trend (mean 0% s.d. 3%)
 */
float stock_change(int mode);

/**
 * Random integer function potentially useful in choosing stock type
 */
unsigned int random_integer(unsigned int max_integer);
#endif
