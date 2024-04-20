/**
 * @file main.cpp
 * @brief Hello! Welcome to the Stock Market Simulator!
 * @authors Everyone in the group project.
 */
#include "draw.h"
#include "format.h"
#include "draw.h"
#include "format.h"
#include "graph.h"
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
void printTable(std::vector<Stock> stocks_list, float balance) {
    // Create a table, note that R"(% Change)" is a raw string literal (C++11 feature).
    VariadicTable<unsigned int, std::string, std::string, float, float, float, unsigned int, float, unsigned int> table(
        {"No.", "Category", "Name", "Last Price", "Change", R"(% Change)", "Quantity", "$ Spent", "Max"});
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
        table.addRow(i + 1, stocks_list[i].getCategoryName(), stocks_list[i].getName(), stocks_list[i].getPrice(),
                     stocks_list[i].deltaPrice(), stocks_list[i].deltaPercentagePrice() * 100,
                     stocks_list[i].getQuantity(), stocks_list[i].getMoneySpent(),
                     stocks_list[i].getAffordableQuantity(balance, trading_fees_percent));
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
std::vector<Stock_event> getOngoingEvents(std::vector<Stock> stocks_list) {
    // Return a vector of ongoing events without duplicates
    std::vector<Stock_event> ongoing_events = {};
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        std::list<Stock_event> events = stocks_list[i].getAllEvents();
        for (Stock_event event : events) {
            // Side note: Events with duration <= 0 are automatically removed from the stock's event list.
            // By stock.cpp Stock::gotoNextRound() which uses Stock::removeObseleteEvent()
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
void newNextRoundEvents(std::vector<Stock> & stocks_list) {
    // Apply events into stocks
    std::vector<Stock_event> picked_events = pickNumEvents(allStockEvents, 5);
    for (Stock_event event : picked_events) {
        switch (event.type_of_event) {
        case all_stocks:
            for (unsigned int i = 0; i < stocks_list.size(); i++) {
                stocks_list[i].addEvent(event);
            }
            break;
        case category:
            for (unsigned int i = 0; i < stocks_list.size(); i++) {
                if (stocks_list[i].getCategory() == event.category) {
                    stocks_list[i].addEvent(event);
                }
            }
            break;
        case pick_random_stock: {
            std::vector<unsigned int> stocks_indices_not_suitable = {};
            while (stocks_list.size() > 0 && stocks_list.size() < stocks_indices_not_suitable.size()) {
                // Pick a random stock
                unsigned int choice = py_random::randint(0, stocks_list.size() - 1);
                Stock lucky_stock = stocks_list[choice];
                if (!lucky_stock.canAddEvent(event)) {
                    stocks_indices_not_suitable.push_back(choice);
                }
                else {
                    Stock_event modified_event = event;
                    modified_event.text = lucky_stock.getName() + " " + event.text;
                    lucky_stock.addEvent(modified_event);
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

void gotoNextRound(unsigned int & rounds_played, std::vector<Stock> & stocks_list) {
    rounds_played++;                 // Increment the round number
    newNextRoundEvents(stocks_list); // Generate new events and apply them to the stocks
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].gotoNextRound(); // Update the stock price
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

    drawLogo(row, col);
    std::cout << "Welcome to the Stock Market Simulator!" << std::endl;
    time::sleep(200);
    std::cout << "Current trading fees are charged at " << trading_fees_percent * 100 << " %" << std::endl;
    time::sleep(200);
    std::cout << textClear << setCursorPosition(5, 0);
    printTable(stocks_list, balance); // Print the table of stocks
    drawRoundInfo(row, col, rounds_played, balance);
    drawEventBar(row, col);
    drawButton(row, col);
    time::sleep(200);

    // Simulate 5*2 rounds of the game with buying/selling alternating
    for (int i = 0; i < 5; i++) {
        // Simulate player buying stocks
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            int num_buyable = stocks_list[i].getAffordableQuantity(balance, trading_fees_percent);
            // If the player can afford at least one stock, buy a random amount of stocks
            if (num_buyable > 0) {
                // Buy random amount of the stocks
                stocks_list[i].purchase(balance, py_random::randint(0, num_buyable - 1), trading_fees_percent);
            }
        }

        gotoNextRound(rounds_played, stocks_list); // Call the next round routine
        std::cout << textClear << setCursorPosition(5, 0);
        printTable(stocks_list, balance);
        drawRoundInfo(row, col, rounds_played, balance); // Prints the round number and balance
        drawEventBar(row, col);
        drawButton(row, col);

        // Simulate player selling stocks
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            int num_sellable = stocks_list[i].getQuantity();
            if (num_sellable > 0) {
                // If the player has spent more than $100 on the stock, sell all the stocks
                if (stocks_list[i].getMoneySpent() > 100) {
                    // Sell all the stocks
                    stocks_list[i].sell(balance, num_sellable, trading_fees_percent);
                }
                else {
                    // Sell random amount of the stocks
                    stocks_list[i].sell(balance, py_random::randint(0, num_sellable - 1), trading_fees_percent);
                }
            }
        }
    }

    time::sleep(500);
    std::cout << textClear << setCursorPosition(5, 0);
    printTable(stocks_list, balance);
    // graph_plotting("test", col * 2 / 3, row - 10);
    drawRoundInfo(row, col, rounds_played, balance);
    drawEventBar(row, col);
    drawButton(row, col);
    std::cout << "\n";

    plotGraph("stockA", 50, 50);
    return 0;
}
