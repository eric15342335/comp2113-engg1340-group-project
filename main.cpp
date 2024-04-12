/**
 * @file main.cpp
 */
#include "stock.h"
#include "player.h"
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

void print_table(std::vector<Stock> stocks_list, Player player) {
    VariadicTable<unsigned int, std::string, float, float, float, unsigned int, float, unsigned int>
        table({"No.", "Name", "Last Price", "Change", "\% Change", "Quantity", "$ Spent", "Max"});

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
                     stocks_list[i].num_stocks_affordable(player.bal(), trading_fees_percent));
    }
    table.print(std::cout);
}

/** Main function */
int main(void) {
    std::vector<Stock> stocks_list;
    Player player;
    player.start_game();
    for (int i = 0; i < initial_stock_count; i++) {
        Stock stock;
        stock.init();
        stocks_list.push_back(stock);
    }

    std::cout << "Welcome to the Stock Market Simulator!" << std::endl;
    std::cout << "Current trading fees are charged at " << trading_fees_percent * 100 << " %" << std::endl;
    std::cout << "You currently have $" << *player.get_balance_ptr() << "." << std::endl;
    /** Test for VariadicTable.h */

    print_table(stocks_list, player);
    /** Simulate player buying and selling stocks automatically */
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        int num_buyable = stocks_list[i].num_stocks_affordable(player.bal(), trading_fees_percent);
        if (num_buyable > 0) {
            stocks_list[i].purchase(*player.get_balance_ptr(), random_integer(num_buyable), trading_fees_percent);
        }
    }
    /** Go to next round */
    player.next_round();
    std::cout << "Played: " << player.get_rounds_played() << " Rounds." << std::endl;
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].next_round();
    }
    print_table(stocks_list, player);
    std::cout << "You currently have $" << *player.get_balance_ptr() << "." << std::endl;

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
