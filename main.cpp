/**
 * @file main.cpp
 * @brief Hello! Welcome to the Stock Market Simulator!
 * @authors Everyone in the group project.
 */

#include <fstream>
#include <numeric>
#include "draw.h"
#include "format.h"
#include "events.h"
#include "graph.h"
#include "stock.h"
#include "random_price.h"
#include "controls.h"
#include "file_io.h"
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

std::string vectorToString(const std::vector<unsigned int> & vec) {
    return std::accumulate(vec.begin(), vec.end(), std::string(), [](std::string s, int v) { return s.empty() ? std::to_string(v) : s + " " + std::to_string(v); });
}

/** Print the table of stocks. We put it in a function so we can call it multiple times.
 * @param stocks_list A vector of stocks. The stocks to be printed.
 * @param balance How much money the player has.
 */
void print_table(std::vector<Stock> stocks_list, float balance) {
    // Create a table, note that R"(% Change)" is a raw string literal (C++11 feature).
    VariadicTable<unsigned int, std::string, std::string, float, float, float, unsigned int, unsigned int, int, float, std::string>
        table({"No.", "Category", "Name", "Last Price", "Change", R"(% Change)", "Quantity", "Max", "Mean", " SD ", "event_id"});
    /* Set the precision and format of the columns.
     * Note: Precision and Format is ignored for std::string columns. */
    table.setColumnPrecision({1, 0, 0, 2, 2, 2, 1, 1, 0, 1, 0});
    table.setColumnFormat({VariadicTableColumnFormat::AUTO,
                           VariadicTableColumnFormat::AUTO,
                           VariadicTableColumnFormat::AUTO,
                           VariadicTableColumnFormat::FIXED,
                           VariadicTableColumnFormat::FIXED,
                           VariadicTableColumnFormat::FIXED,
                           VariadicTableColumnFormat::FIXED,
                           VariadicTableColumnFormat::FIXED,
                           VariadicTableColumnFormat::AUTO,
                           VariadicTableColumnFormat::FIXED,
                           VariadicTableColumnFormat::AUTO});
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        table.addRow(i + 1, stocks_list[i].category_name(), stocks_list[i].get_name(), stocks_list[i].get_price(),
                     stocks_list[i].delta_price(), stocks_list[i].delta_price_percentage() * 100,
                     stocks_list[i].get_quantity(),
                     stocks_list[i].num_stocks_affordable(balance, trading_fees_percent),
                     stocks_list[i].get_attribute(mean) + stocks_list[i].sum_attribute(mean),
                     stocks_list[i].get_attribute(standard_deviation) + stocks_list[i].sum_attribute(standard_deviation),
                     vectorToString(stocks_list[i].get_event_ids()));
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

    /** @todo Finish UI code. Eric: I don't know where to put your "char command". */
    // char command;
    std::vector<Stock> stocks_list; // Create a vector of stocks
    for (int i = 0; i < initial_stock_count; i++) {
        Stock stock;
        stocks_list.push_back(stock); // Add the stock to the vector
    }

    // File IO related code, for game saving and loading
    std::string playerName, loadsave;
    std::cout << textClear;
    std::cout << "Enter 0 for new save or enter 1 for loading old save: ";
    std::cin >> loadsave;
    while (loadsave != "0" && loadsave != "1") {
        std::cout << "Invalid input. Please enter 0 for new save or enter 1 for loading old save: ";
        std::cin >> loadsave; // choose new file or load previous file
    }
    if (loadsave == "1") {
        loadstatus(rounds_played, stocks_list, balance, playerName);
    }
    if (loadsave == "0") {
        createplayer(playerName); // create a new save file
    }
    // Done loading/creating a new file.

    drawLogo(row, col);
    std::cout << "Welcome to the Stock Market Simulator!" << std::endl;
    time::sleep(100);
    std::cout << "Current trading fees are charged at " << trading_fees_percent * 100 << " %" << std::endl;
    time::sleep(100);
    std::cout << textClear << setCursorPosition(5, 0);
    print_table(stocks_list, balance); // Print the table of stocks
    drawRoundInfo(row, col, rounds_played, balance);
    drawEventBar(row, col);
    drawButton(row, col);
    optionsInput(row, col, balance, trading_fees_percent, stocks_list);
    time::sleep(200);

    /*
    // Simulate 5*2 rounds of the game with buying/selling alternating
    for (int i = 0; i < 10; i++) {
        // Simulate player selling stocks
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            int num_sellable = stocks_list[i].get_quantity();
            if (num_sellable > 0) {
                stocks_list[i].sell(balance, random_integer(num_sellable), trading_fees_percent);
            }
        }
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
        savestatus(rounds_played, stocks_list, balance, playerName);
        std::cout << textClear << setCursorPosition(5, 0);
        print_table(stocks_list, balance);
        drawRoundInfo(row, col, rounds_played, balance); // Prints the round number and balance
        drawEventBar(row, col);
        drawButton(row, col);
        time::sleep(200);
    }
    */

    std::cout << textClear << setCursorPosition(5, 0);
    // print_table(stocks_list, balance);
    // A test case for the graphs. Also can get a better understanding
    // of stock price fluctuation.
    // for (unsigned int i = 0; i < stocks_list.size(); i++) {
    //     graph_plotting(playerName, i, col * 2 / 3, row - 10);
    // }
    drawRoundInfo(row, col, rounds_played, balance);
    drawEventBar(row, col);
    drawButton(row, col);
    optionsInput(row, col, balance, trading_fees_percent, stocks_list);
    std::cout << "\n";
    return 0;
}