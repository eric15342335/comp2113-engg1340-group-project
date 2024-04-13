/**
 * @file main.cpp
 */
#include "stock.h"
#include "random_price.h"
#include "nonstdlibs/VariadicTable.h"

/**
 * 1% trading fees
 * trading fees are applied to both buying and selling
 * see stock.cpp Stock::purchase and Stock::sell functions
 */
const float trading_fees_percent = 0.01;

/** Initial stock count */
const int initial_stock_count = 20;

/** Print the table of stocks.
 * Put it in a function so we can call it multiple times.
 * @param stocks_list The list of stocks to print.
 * @param player The player object, for retrieving the player balance.
 */
void print_table(std::vector<Stock> stocks_list, float balance) {
    /** Create a table */
    VariadicTable<unsigned int, std::string, float, float, float, unsigned int, float, unsigned int>
        table({"No.", "Name", "Last Price", "Change", "\% Change", "Quantity", "$ Spent", "Max"});
    /** Set the precision and format of the columns.
     * Note: Precision and Format is ignored for std::string columns.
     */
    table.setColumnPrecision({1, 0, 2, 1, 1, 1, 2, 1});
    table.setColumnFormat({
        VariadicTableColumnFormat::AUTO,
        VariadicTableColumnFormat::AUTO,
        VariadicTableColumnFormat::FIXED,
        VariadicTableColumnFormat::FIXED,
        VariadicTableColumnFormat::FIXED,
        VariadicTableColumnFormat::AUTO,
        VariadicTableColumnFormat::FIXED,
        VariadicTableColumnFormat::AUTO,
    });
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        table.addRow(i + 1, stocks_list[i].get_name(), stocks_list[i].get_price(),
                     stocks_list[i].delta_price(), stocks_list[i].delta_price_percentage() * 100,
                     stocks_list[i].get_quantity(), stocks_list[i].get_money_spent(),
                     stocks_list[i].num_stocks_affordable(balance, trading_fees_percent));
    }
    table.print(std::cout);
    /** Display 2 decimal places for balance.
     * This line reverts the precision back to default after the table is printed.
     * Since the table uses std::auto (VariadicTableColumnFormat::AUTO), we need to revert it back to default.
     */
    std::cout << std::fixed << std::setprecision(2);
}

float balance = 1000.0;
unsigned int rounds_played = 1;

/** Main function */
int main(void) {
    std::vector<Stock> stocks_list; // Create a vector of stocks
    for (int i = 0; i < initial_stock_count; i++) {
        Stock stock;
        stock.init();                 // Initialize the stock
        stocks_list.push_back(stock); // Add the stock to the vector
    }

    // Print the welcome message
    std::cout << "Welcome to the Stock Market Simulator!" << std::endl;
    std::cout << "Current trading fees are charged at " << trading_fees_percent * 100 << " %" << std::endl;
    std::cout << "You currently have $" << balance << "." << std::endl;
    print_table(stocks_list, balance); // Print the table of stocks

    /** Simulate player buying stocks */
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        int num_buyable = stocks_list[i].num_stocks_affordable(balance, trading_fees_percent);
        /** If the player can afford at least one stock, buy a random amount of stocks */
        if (num_buyable > 0) {
            /** Buy random amount of the stocks */
            stocks_list[i].purchase(balance, random_integer(num_buyable), trading_fees_percent);
        }
    }

    /** Go to next round */
    rounds_played++;                                            // Increment the round
    std::cout << "Round " << rounds_played << "." << std::endl; // Print the round number
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].next_round(); // Update the stock price
    }
    print_table(stocks_list, balance);
    std::cout << "You currently have $" << balance << "." << std::endl;

    /** Simulate player buying stocks */
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        int num_sellable = stocks_list[i].get_quantity();
        if (num_sellable > 0) {
            /** If the player has spent more than $100 on the stock, sell all the stocks */
            if (stocks_list[i].get_money_spent() > 100) {
                /** Sell all the stocks */
                stocks_list[i].sell(balance, num_sellable, trading_fees_percent);
            }
            else {
                /** Sell random amount of the stocks */
                stocks_list[i].sell(balance, random_integer(num_sellable), trading_fees_percent);
            }
        }
    }
    print_table(stocks_list, balance);
    std::cout << "You currently have $" << balance << "." << std::endl;

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
