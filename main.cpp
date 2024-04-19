/**
 * @file main.cpp
 */
#include "draw.h"
#include "format.h"
#include "stock.h"
#include "events.h"
#include "random_price.h"
#include "graph.h"
#include "nonstdlibs/VariadicTable.h"

/**
 * 0.01 means 1% trading fees.
 *
 * Trading fees are applied to both buying and selling.
 *
 * see stock.cpp `Stock::purchase` and `Stock::sell` functions
 */
const float trading_fees_percent = 0.01;

/** Initial stock count */
const int initial_stock_count = 20;

/** Player's balance */
float balance = 1000;
/** Number of rounds played */
unsigned int rounds_played = 1;

/** Print the table of stocks. We put it in a function so we can call it multiple times.
 * @param stocks_list A vector of stocks. The stocks to be printed.
 * @param balance How much money the player has.
 */
void print_table(std::vector<Stock> stocks_list, float balance) {
    // Create a table, note that R"(% Change)" is a raw string literal (C++11 feature).
    VariadicTable<unsigned int, std::string, std::string, float, float, float, unsigned int, float, unsigned int>
        table({"No.", "Category", "Name", "Last Price", "Change", R"(% Change)", "Quantity", "$ Spent", "Max"});
    /* Set the precision and format of the columns.
     * Note: Precision and Format is ignored for std::string columns. */
    table.setColumnPrecision({1, 0, 0, 2, 2, 2, 1, 2, 1});
    table.setColumnFormat({
        VariadicTableColumnFormat::AUTO,
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
        table.addRow(i + 1, stocks_list[i].category_name(), stocks_list[i].get_name(), stocks_list[i].get_price(),
                     stocks_list[i].delta_price(), stocks_list[i].delta_price_percentage() * 100,
                     stocks_list[i].get_quantity(), stocks_list[i].get_money_spent(),
                     stocks_list[i].num_stocks_affordable(balance, trading_fees_percent));
    }
    table.print(std::cout);
    /* Display 2 decimal places for balance.
     * This line reverts the precision back to default after the table is printed.
     * Since the table uses std::auto (VariadicTableColumnFormat::AUTO), we need to revert it back to default.
     */
    std::cout << std::fixed << std::setprecision(2);
}

/**
 * Get all the ongoing events.
 * @param stocks_list A vector of stocks.
 * @return A vector of Stock_event
 */
std::vector<Stock_event> get_ongoing_events(std::vector<Stock> stocks_list) {
    // Return a vector of ongoing events without duplicates
    std::vector<Stock_event> ongoing_events = {};
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        std::list<Stock_event> events = stocks_list[i].get_events();
        for (Stock_event event : events) {
            // Side note: Events with duration <= 0 are automatically removed from the stock's event list.
            // By stock.cpp Stock::next_round() which uses Stock::remove_obselete_event()
            if (event.duration > 0) {
                // If the event is not in the ongoing_events, add it.
                if (std::find(ongoing_events.begin(), ongoing_events.end(), event) == ongoing_events.end()) {
                    ongoing_events.push_back(event);
                }
            }
        }
    }
    return ongoing_events;
}

/**
 * Generate new events and apply them to the stocks. Should be called at the beginning of each round.
 * We put it in a function so we can call it multiple times easily.
 * @param stocks_list A vector of stocks. Pass by reference to modify the stocks.
 */
void new_events_next_round(std::vector<Stock> & stocks_list) {
    // Apply events into stocks
    std::vector<Stock_event> picked_events = pick_events(all_stock_events, 5);
    for (Stock_event event : picked_events) {
        switch (event.type_of_event) {
        case all_stocks:
            for (unsigned int i = 0; i < stocks_list.size(); i++) {
                stocks_list[i].add_event(event);
            }
            break;
        case category:
            for (unsigned int i = 0; i < stocks_list.size(); i++) {
                if (stocks_list[i].get_category() == event.category) {
                    stocks_list[i].add_event(event);
                }
            }
            break;
        case pick_random_stock: {
            std::vector<unsigned int> stocks_indices_not_suitable = {};
            while (stocks_list.size() > 0 && stocks_list.size() < stocks_indices_not_suitable.size()) {
                // Pick a random stock
                unsigned int choice = random_integer(stocks_list.size());
                Stock lucky_stock = stocks_list[choice];
                if (!lucky_stock.can_add_event(event)) {
                    stocks_indices_not_suitable.push_back(choice);
                }
                else {
                    Stock_event modified_event = event;
                    modified_event.text = lucky_stock.get_name() + " " + event.text;
                    lucky_stock.add_event(modified_event);
                    break;
                }
            }
            break;
        }
        default:
            // Should not reach here, but if it does, break the loop
            // so that the player can continue playing the game.
            break;
        }
    }
}

void next_round_routine(unsigned int & rounds_played, std::vector<Stock> & stocks_list) {
    rounds_played++;                    // Increment the round number
    new_events_next_round(stocks_list); // Generate new events and apply them to the stocks
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].next_round(); // Update the stock price
    }
}

/** Main function, the entry point of the program */
int main(void) {
    int row; // Number of characters to fit in a column
    int col; // Number of characters to fit in a row
    fetchConsoleDimensions(row, col);

    std::vector<Stock> stocks_list; // Create a vector of stocks
    for (int i = 0; i < initial_stock_count; i++) {
        Stock stock;
        stocks_list.push_back(stock); // Add the stock to the vector
    }

    // Print the welcome message
    std::cout << textClear << setCursorPosition(0, 0);
    std::cout << "Welcome to the Stock Market Simulator!" << std::endl;
    sleep(200);
    std::cout << "Current trading fees are charged at " << trading_fees_percent * 100 << " %" << std::endl;
    std::cout << "You currently have $" << balance << "." << std::endl;
    sleep(500);
    print_table(stocks_list, balance); // Print the table of stocks
    sleep(500);

    // Simulate 5*2 rounds of the game with buying/selling alternating
    for (int i = 0; i < 5; i++) {
        // Simulate player buying stocks
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            int num_buyable = stocks_list[i].num_stocks_affordable(balance, trading_fees_percent);
            // If the player can afford at least one stock, buy a random amount of stocks
            if (num_buyable > 0) {
                // Buy random amount of the stocks
                stocks_list[i].purchase(balance, random_integer(num_buyable), trading_fees_percent);
            }
        }

        next_round_routine(rounds_played, stocks_list); // Call the next round routine
        std::cout << textClear << setCursorPosition(0, 0);
        drawRoundInfo(row, col, rounds_played, balance); // Prints the round number and balance
        std::cout << setCursorPosition(5, 0);

        print_table(stocks_list, balance);
        drawEventBar(row, col);
        drawButton(row, col);

        print_table(stocks_list, balance);
        std::cout << "You currently have $" << balance << "." << std::endl;

        // Simulate player selling stocks
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            int num_sellable = stocks_list[i].get_quantity();
            if (num_sellable > 0) {
                // If the player has spent more than $100 on the stock, sell all the stocks
                if (stocks_list[i].get_money_spent() > 100) {
                    // Sell all the stocks
                    stocks_list[i].sell(balance, num_sellable, trading_fees_percent);
                }
                else {
                    // Sell random amount of the stocks
                    stocks_list[i].sell(balance, random_integer(num_sellable), trading_fees_percent);
                }
            }
        }

        next_round_routine(rounds_played, stocks_list); // Call the next round routine
        {
            std::cout << "Round " << rounds_played << "." << std::endl; // Print the round number
            std::vector<Stock_event> ongoing_events = get_ongoing_events(stocks_list);
            for (Stock_event event : ongoing_events) {
                std::cout << event.text << " " << event.duration << std::endl;
            }

            print_table(stocks_list, balance);
            std::cout << "You currently have $" << balance << "." << std::endl;
        }
    }

    sleep(500);
    std::cout << textClear << setCursorPosition(0, 0);
    drawRoundInfo(row, col, rounds_played, balance);
    std::cout << setCursorPosition(5, 0);
    print_table(stocks_list, balance);
    drawEventBar(row, col);
    drawButton(row, col);

    while (0) {
        fetchConsoleDimensions(row, col);
        drawEventBar(row, col);
        drawButton(row, col);
        sleep(200);
        std::cout << textClear;
    }

    // graph_plotting("stockA", 50, 50);
    return 0;
}
