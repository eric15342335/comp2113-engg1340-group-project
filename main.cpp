/**
 * @file main.cpp
 */

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "stock.h"

/**
 * 1% trading fees
 * trading fees are applied to both buying and selling
 * see stock.cpp Stock::purchase and Stock::sell functions
 */
const float trading_fees_percent = 0.01;

/** Initial stock count */
const int initial_stock_count = 10;

float player_balance = 1000;

/** Main function */
int main(void) {
    std::list<Stock> stocks_list;
    for (int i = 0; i < initial_stock_count; i++) {
        Stock stock;
        stocks_list.push_back(stock);
    }

    std::cout << "Welcome to the stock market game!" << std::endl;
    for (Stock stock : stocks_list) {
        std::cout << stock.get_name() << " " << stock.get_price()
                  << " " << stock.get_quantity() << " " << stock.get_money_spent() << std::endl;
    }

    /**
     * todo: implement UI code
     *
     * We don't want the game control be simply 'cin >> choice'
     *
     * Possible ideas:
     * 1. Keyboard hotkeys, e.g. press B to buy, S to sell, etc.
     * 2. Arrow keys selection (like a menu)
     *
     * @todo: intro game splash screen using ascii code or something
     */

    return 0;
}
