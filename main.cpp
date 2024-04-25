/**
 * @file main.cpp
 * @brief Hello! Welcome to the Stock Market Simulator!
 * @authors Everyone in the group project.
 */

#include "controls.h"
#include "draw.h"
#include "events.h"
#include "file_io.h"
#include "format.h"
#include "graph.h"
#include "nonstdlibs/VariadicTable.h"
#include "random_price.h"
#include "stock.h"

#include <cmath>
#include <fstream>
#include <numeric>

#ifdef _WIN32
#include <windows.h>
#else
#define SetConsoleOutputCP(x) // Do nothing
#endif

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

/** Player's name */
std::string playerName;

std::string vectorToString(const std::vector<unsigned int> & vec) {
    return std::accumulate(
        vec.begin(), vec.end(), std::string(), [](std::string s, int v) {
            return s.empty() ? std::to_string(v) : s + " " + std::to_string(v);
        });
}

void get_hsi(std::vector<Stock> stocks_list, std::vector<float> & hsi_history) {
    float hsi = 0;
    std::string filesave = "saves/" + playerName + "/hsi.save";
    std::vector<float> total;
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        total.push_back(stocks_list[i].get_price() /
                        stocks_list[i].get_initial_price() * 1000 *
                        pow(2, stocks_list[i].get_split_count()));
        // HSI formula = (price/initial price) * 1000 * 2^split count
    }
    hsi = std::reduce(total.begin(), total.end()) / total.size();
    hsi_history.push_back(hsi);
    std::ofstream fout;
    fout.open(filesave.c_str(), std::ios::app);
    fout << hsi << ' ';
    fout.close();
}

/**
 * @brief hiding mean/sd/uplim/lowlim/event_id columns in the table
 */
enum mode { normal, dev };

/** Print the table of stocks. We put it in a function so we can call it multiple times.
 * @param stocks_list A vector of stocks. The stocks to be printed.
 * @param balance How much money the player has.
 * @param m mode to hide mean/sd/uplim/lowlim/event_id columns in the table
 */
void print_table(std::vector<Stock> stocks_list, float balance, mode m = dev) {
    std::vector<std::string> defaultColumns = {
        "#", "Category", "Name", "$Price", "Change", R"(%Change)", "#Has", "#Max"};
    VariadicTable<unsigned int, std::string, std::string, float, float, float,
        unsigned int, unsigned int>
        table(defaultColumns);
    if (m == dev) {
        defaultColumns.emplace_back(" Mean ");
        defaultColumns.emplace_back(" SD ");
        defaultColumns.emplace_back("up");
        defaultColumns.emplace_back("low");
        defaultColumns.emplace_back("event_id");
        // Create a table, note that R"(% Change)" is a raw string literal (C++11
        // feature).
        VariadicTable<unsigned int, std::string, std::string, float, float, float,
            unsigned int, unsigned int, float, float, float, float, std::string>
            table({defaultColumns});
        /* Set the precision and format of the columns.
         * Note: Precision and Format is ignored for std::string columns. */
        table.setColumnPrecision({0, 0, 0, 2, 2, 2, 0, 0, 2, 1, 0, 0, 0});
        table.setColumnFormat({VariadicTableColumnFormat::AUTO,
            VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::AUTO,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::AUTO});
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            std::map<stock_modifiers, float> modifiers =
                getProcessedModifiers(stocks_list[i]);
            table.addRow(i + 1, stocks_list[i].category_name(),
                stocks_list[i].get_name(), stocks_list[i].get_price(),
                stocks_list[i].delta_price(),
                stocks_list[i].delta_price_percentage() * 100,
                stocks_list[i].get_quantity(),
                stocks_list[i].num_stocks_affordable(balance, trading_fees_percent),
                modifiers[mean], modifiers[standard_deviation], modifiers[upper_limit],
                modifiers[lower_limit], vectorToString(stocks_list[i].get_event_ids()));
        }
        table.print(std::cout);
    }
    else {
        /* Set the precision and format of the columns.
         * Note: Precision and Format is ignored for std::string columns. */
        table.setColumnPrecision({0, 0, 0, 2, 2, 2, 0, 0});
        table.setColumnFormat(
            {VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::AUTO,
                VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::FIXED,
                VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
                VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED});
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            table.addRow(i + 1, stocks_list[i].category_name(),
                stocks_list[i].get_name(), stocks_list[i].get_price(),
                stocks_list[i].delta_price(),
                stocks_list[i].delta_price_percentage() * 100,
                stocks_list[i].get_quantity(),
                stocks_list[i].num_stocks_affordable(balance, trading_fees_percent));
        }
        table.print(std::cout);
    }
    /* Display 2 decimal places for balance.
     * This line reverts the precision back to default after the table is printed.
     * Since the table uses std::auto (VariadicTableColumnFormat::AUTO), we need to
     * revert it back to default.
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
            // Side note: Events with duration <= 0 are automatically removed from the
            // stock's event list. By stock.cpp Stock::next_round() which uses
            // Stock::remove_obselete_event()
            if (event.duration > 0) {
                // If the event is not in the ongoing_events, add it.
                if (std::find(ongoing_events.begin(), ongoing_events.end(), event) ==
                    ongoing_events.end()) {
                    ongoing_events.push_back(event);
                }
            }
        }
    }
    return ongoing_events;
}

/**
 * @brief Generate new events and apply them to the stocks. Should be called at the
 * beginning of each round.
 * @param stocks_list A vector of stocks. Pass by reference to modify the stocks.
 */
void new_events_next_round(std::vector<Stock> & stocks_list) {
    /** @note numEvents is the sum of these two values:
     * - A random integer between 0 and 2
     * - 1/5 of numOfRounds, or 2. Whichever is smaller
     */
    unsigned int numEvents =
        random_integer(2) +
        std::min(static_cast<int>(stocks_list[0].get_history_size() / 5), 2);
    std::vector<Stock_event> picked_events = pick_events(all_stock_events, numEvents);
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
                while (stocks_list.size() > 0 &&
                       stocks_list.size() < stocks_indices_not_suitable.size()) {
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

void next_round_routine(
    unsigned int & rounds_played, std::vector<Stock> & stocks_list) {
    rounds_played++; // Increment the round number
    new_events_next_round(
        stocks_list); // Generate new events and apply them to the stocks
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].next_round(); // Update the stock price
    }
}

/** Main function, the entry point of the program */
int main(void) {
    // Set the console to UTF-8 mode
    SetConsoleOutputCP(65001);
    bool viewMode = 0;
    int graphIndex;
    bool advance;      // Whether to advance to the next round
    bool gameQuit = 0; // Whether the player wants to quit the game
    bool optionsQuit;
    int row; // Number of characters to fit in a column
    int col; // Number of characters to fit in a row
    fetchConsoleDimensions(row, col);

    std::vector<Stock> stocks_list;
    for (int i = 0; i < initial_stock_count; i++) {
        Stock stock;
        stocks_list.push_back(stock); // Add the stock to the vector
    }

    sortStocksList(stocks_list, by_category, ascending);

    std::vector<float> hsi_history;
    std::string loadsave;
    std::cout << "Please enter 0 for new save, enter 1 for loading old save, enter 2 "
                 "for deleting save or enter 3 to quit: ";
    std::cin >> loadsave;
    while (loadsave != "0" && loadsave != "1" && loadsave != "2" && loadsave != "3") {
        std::cout << "Invalid input. Please enter 0 for new save, enter 1 for loading "
                     "old save, enter 2 for deleting save or enter 3 to quit: ";
        std::cin >> loadsave; // choose new file or load previous file
    }
    if (loadsave == "1") {
        loadstatus(rounds_played, stocks_list, balance, playerName, hsi_history);
    }
    if (loadsave == "2") {
        delsave(loadsave); // delete existing file
    }
    if (loadsave == "3") {
        std::cout << "Goodbye! Hope you had a good luck in the stock market!"
                  << std::endl;
        ;
        return 0;
    }
    if (loadsave == "0") {
        createplayer(playerName);
        savestatus(rounds_played, stocks_list, balance, playerName);
    }
    // Done loading/creating a new file.

    get_hsi(stocks_list, hsi_history);

    drawLogo(row, col);
    time::sleep(sleepMedium);
    std::cout << textClear << setCursorPosition(0, 0);
    std::cout << "Current trading fees are charged at " << trading_fees_percent * 100
              << " %" << std::endl;
    time::sleep(sleepMedium);

    while (!gameQuit) {
        advance = 0;
        optionsQuit = 0;
        if (viewMode) {
            graphIndex = integerInput(row, col, "Select stock index to display: ");
            while (graphIndex < 1 || graphIndex > (int)stocks_list.size()) {
                std::cout << setCursorPosition(row, 3) << "\x1b[2K";
                std::cout << "Index out of range!";
                time::sleep(sleepMedium);
                graphIndex = integerInput(row, col, "Select stock index to display: ");
            }
            std::cout << textClear << setCursorPosition(5, 0);
            graph_plotting(playerName, 1, col * 2 / 3, row - 10);
        }
        else {
            std::cout << textClear << setCursorPosition(5, 0);
            print_table(stocks_list, balance); // Print the table of stocks
        }
        drawRoundInfo(row, col, rounds_played, balance);
        drawEventBar(row, col);
        drawButton(row, col);
        while (!optionsQuit) {
            optionsInput(row, col, balance, trading_fees_percent, stocks_list, viewMode,
                advance, optionsQuit, gameQuit);
        }

        if (advance) {
            next_round_routine(rounds_played, stocks_list);
            get_hsi(stocks_list, hsi_history);
            savestatus(rounds_played, stocks_list, balance, playerName);
            viewMode = 0;
            time::sleep(sleepLong);
        }
    }

    std::cout << "HSI: " << hsi_history[hsi_history.size() - 1] << std::endl;

    return 0;
}