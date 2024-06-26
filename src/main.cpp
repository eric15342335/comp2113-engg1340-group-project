/// @file main.cpp
/// file with the main() function
/*
This program is free software: you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this
program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "controls.h"
#include "draw.h"
#include "events.h"
#include "file_io.h"
#include "format.h"
#include "graph.h"
#include "random_price.h"
#include "stock.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif
#include "nonstdlibs/VariadicTable.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#include <cmath>
#include <fstream>
#include <numeric>

#ifdef _WIN32
#define NOMINMAX 1          // Prevent Windows.h from defining min and max macros
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>
/** @brief Enable Windows VT processing for ANSI escape codes
 * @details Without this, ANSI escape codes will not work on Windows 10.
 * E.g. text color, cursor position, etc.
 */
void enableWindowsVTProcessing(void) {
    // Set the console to UTF-8 mode
    SetConsoleOutputCP(65001);
    // Get the current console mode
    DWORD consoleMode;
    GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &consoleMode);
    // Enable virtual terminal processing
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), consoleMode);
    std::cout << "Experimental Windows VT processing enabled." << std::endl;
}
#else
#define enableWindowsVTProcessing() // Do nothing
#endif

/**
 * <value> / 100 means charging <value>% more/portion of the money involved in stock
 * operations.
 */
const float trading_fees_percent = 0.1 / 100;

/** Player's balance */
float balance = 1000.0f;
/** Number of rounds played */
unsigned int rounds_played = 1;

/** Player's name */
std::string playerName;

std::string vectorToString(const std::vector<unsigned int> & vec) {
    return std::accumulate(
        vec.begin(), vec.end(), std::string(), [](const std::string & s, int v) {
            return s.empty() ? std::to_string(v) : s + " " + std::to_string(v);
        });
}

void get_hsi(std::vector<Stock> stocks_list, std::vector<float> & hsi_history) {
    float hsi = 0;
    std::string filesave =
        SAVE_FOLDER_PREFIX + playerName + "/hsi" + SAVE_FILE_EXTENSION_TXT;
    std::vector<float> total;
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        total.emplace_back(
            stocks_list[i].get_price() / stocks_list[i].get_initial_price() * 1000 *
            static_cast<float>(std::pow(2, stocks_list[i].get_split_count())));
        // HSI formula = (price/initial price) * 1000 * 2^split count
    }
    hsi = std::reduce(total.begin(), total.end()) / total.size();
    hsi_history.emplace_back(hsi);
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
 * @param _playerBal How much money the player has.
 * @param m mode to hide mean/sd/uplim/lowlim/event_id columns in the table
 */
void print_table(std::vector<Stock> stocks_list, float _playerBal, mode m = dev) {
    std::vector<std::string> defaultColumns = {
        "#", "Category", "Name", "$Price", "Change", R"(%Change)", "#Has", "#Max"};
    VariadicTable<unsigned int, std::string, std::string, float, float, float,
        unsigned int, unsigned int>
        defaultTable(defaultColumns);
    if (m == dev) {
        defaultColumns.emplace_back(" Mean ");
        defaultColumns.emplace_back(" SD ");
        defaultColumns.emplace_back(" up ");
        defaultColumns.emplace_back(" low ");
        defaultColumns.emplace_back("event_id");
        // Create a table, note that R"(% Change)" is a raw string literal (C++11
        // feature).
        VariadicTable<unsigned int, std::string, std::string, float, float, float,
            unsigned int, unsigned int, float, float, float, float, std::string>
            devTable({defaultColumns});
        /* Set the precision and format of the columns.
         * Note: Precision and Format is ignored for std::string columns. */
        devTable.setColumnPrecision({0, 0, 0, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0});
        devTable.setColumnFormat({VariadicTableColumnFormat::AUTO,
            VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::AUTO,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::AUTO});
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            std::map<stock_modifiers, float> modifiers =
                getProcessedModifiers(stocks_list[i]);
            devTable.addRow(i + 1, stocks_list[i].category_name(),
                stocks_list[i].get_name(), stocks_list[i].get_price(),
                stocks_list[i].delta_price(),
                stocks_list[i].delta_price_percentage() * 100,
                stocks_list[i].get_quantity(),
                stocks_list[i].num_stocks_affordable(_playerBal, trading_fees_percent),
                modifiers[mean], modifiers[standard_deviation], modifiers[upper_limit],
                modifiers[lower_limit], vectorToString(stocks_list[i].get_event_ids()));
        }
        devTable.print(std::cout);
    }
    else {
        /* Set the precision and format of the columns.
         * Note: Precision and Format is ignored for std::string columns. */
        defaultTable.setColumnPrecision({0, 0, 0, 2, 2, 2, 0, 0});
        defaultTable.setColumnFormat(
            {VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::AUTO,
                VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::FIXED,
                VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
                VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED});
        for (unsigned int i = 0; i < stocks_list.size(); i++) {
            defaultTable.addRow(i + 1, stocks_list[i].category_name(),
                stocks_list[i].get_name(), stocks_list[i].get_price(),
                stocks_list[i].delta_price(),
                stocks_list[i].delta_price_percentage() * 100,
                stocks_list[i].get_quantity(),
                stocks_list[i].num_stocks_affordable(_playerBal, trading_fees_percent));
        }
        defaultTable.print(std::cout);
    }
    // Modify the stringstream so that for the column "Change", the text
    // "Increase" is green and "Decrease" is red.
    // @note This is a workaround because VariadicTable does not support
    // modifying the text color of a specific cell.
    // Warning: This is a hack and may not work in the future!
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        std::string index = std::to_string(i + 1);
        if (i < 10 - 1) {
            index = " " + index;
        }
        if (stocks_list[i].delta_price() > 0) {
            std::cout << setCursorPosition(i + 9, 3) << textGreen << index;
        }
        else if (stocks_list[i].delta_price() < 0) {
            std::cout << setCursorPosition(i + 9, 3) << textRed << index;
        }
    }
    std::cout << textWhite;
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
        for (const Stock_event & event : events) {
            // Side note: Events with duration <= 0 are automatically removed from the
            // stock's event list. By stock.cpp Stock::next_round() which uses
            // Stock::remove_obselete_event()
            if (event.duration > 0) {
                // If the event is not in the ongoing_events, add it.
                if (std::find(ongoing_events.begin(), ongoing_events.end(), event) ==
                    ongoing_events.end()) {
                    ongoing_events.emplace_back(event);
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
    /** @note numEvents is the sum of these three values:
     * - 1
     * - A random integer between 0 and 1 (uniform distribution)
     * - 1 if more than 10 rounds have been played
     * If there was already more than 5 events, we will not generate more events.
     */
    unsigned int numEvents = 1 + random_integer(1) + (rounds_played / 5 > 2) * 1;
    if (get_ongoing_events(stocks_list).size() > 5) {
        return;
    }
    std::vector<Stock_event> picked_events = pick_events(all_stock_events, numEvents);
    for (const Stock_event & event : picked_events) {
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
                while (!stocks_list.empty() &&
                       stocks_list.size() < stocks_indices_not_suitable.size()) {
                    // Pick a random stock
                    unsigned int choice = random_integer(stocks_list.size());
                    Stock lucky_stock = stocks_list[choice];
                    if (!lucky_stock.can_add_event(event)) {
                        stocks_indices_not_suitable.emplace_back(choice);
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

void next_round_routine(unsigned int & _rounds, std::vector<Stock> & stocks_list) {
    _rounds++; // Increment the round number
    new_events_next_round(
        stocks_list); // Generate new events and apply them to the stocks
    for (unsigned int i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].next_round(); // Update the stock price
    }
}

void initializePlayerSaves(
    std::vector<Stock> & stocks_list, std::vector<float> & hsi_history) {
    std::string EMPTY_INPUT = "";
    std::string loadsave = EMPTY_INPUT;
    while (loadsave.compare(EMPTY_INPUT) == 0) {
        std::cout << USER_SAVE_OPTION_PROMPT;
        std::cin >> loadsave;
        while (!checkValidInput(loadsave)) {
            std::cout << "Invalid input.\n" << USER_SAVE_OPTION_PROMPT;
            std::cin >> loadsave; // choose new file or load previous file
        }
        if (loadsave.compare(USER_SAVE_OPTION::NEW_GAME) == 0) {
            createplayer(playerName);
            savestatus(rounds_played, stocks_list, balance, playerName);
        }
        if (loadsave.compare(USER_SAVE_OPTION::LOAD_GAME) == 0) {
            loadstatus(rounds_played, stocks_list, balance, playerName, hsi_history);
        }
        if (loadsave.compare(USER_SAVE_OPTION::DELETE_GAME) == 0) {
            delsave(loadsave);
            loadsave = EMPTY_INPUT;
        }
        if (loadsave.compare(USER_SAVE_OPTION::EXIT_GAME) == 0) {
            std::cout << "Goodbye! Hope you had a good luck in the stock market!"
                      << std::endl;
            exit(EXIT_SUCCESS);
        }
    }
}

int main(void) {
    enableWindowsVTProcessing();
    std::cout << "The game was compiled on " << __DATE__ << " at " << __TIME__
              << std::endl;

    bool advance;          // Whether to advance to the next round
    bool gameQuit = false; // Whether the player wants to quit the game
    bool viewMode = false; // 0 to view table, 1 to view graph
    bool overlayEvent;     // Whether the event bar is being shown
    bool flush;            // Whether the screen needs updating
    int row;               // Number of characters to fit in a column
    int col;               // Number of characters to fit in a row
    fetchConsoleDimensions(row, col);

    std::vector<Stock> stocks_list;
    stocks_list.reserve(initial_stock_count);
    for (int i = 0; i < initial_stock_count; i++) {
        stocks_list.emplace_back();
    }

    sortStocksList(stocks_list, by_category, ascending);

    assertion_check_uniq_events();
    if (assertion_check_mutual_exclusivity()) {
        exit(1);
    }

    drawLogo(row, col);
    time::sleep(sleepMedium);
    std::vector<float> hsi_history;

    initializePlayerSaves(stocks_list, hsi_history);

    if (hsi_history.empty()) {
        get_hsi(stocks_list, hsi_history);
    }

    // Done loading/creating a new file.
    std::cout << "Current trading fees are charged at " << trading_fees_percent * 100
              << " %" << std::endl;
    time::sleep(sleepMedium * 2);

    while (!gameQuit) {
        advance = false;
        overlayEvent = false;
        flush = false;
        if (viewMode) {
            int indexGraph =
                integerInput(row, col, "Select stock index to display (0 for HSI): ");
            while (
                indexGraph < 0 || indexGraph > static_cast<int>(stocks_list.size())) {
                std::cout << setCursorPosition(row, 3) << "\x1b[2K";
                std::cout << "Index out of range!";
                time::sleep(sleepMedium);
                indexGraph = integerInput(
                    row, col, "Select stock index to display (0 for HSI): ");
            }
            std::cout << textClear << setCursorPosition(6, 0);
            graph_plotting(playerName, indexGraph - 1, col * 2 / 3, row - 10);
        }
        else {
            std::cout << textClear << setCursorPosition(6, 0);
            print_table(stocks_list, balance); // Print the table of stocks
        }
        drawRoundInfo(row, col, rounds_played, balance, playerName,
            hsi_history[hsi_history.size() - 1]);
        drawEventBar(row, col);
        drawButton(row, col);
        while (!flush) {
            optionsInput(row, col, balance, trading_fees_percent, stocks_list,
                get_ongoing_events(stocks_list), viewMode, advance, overlayEvent, flush,
                gameQuit);
        }

        if (advance) {
            next_round_routine(rounds_played, stocks_list);
            get_hsi(stocks_list, hsi_history);
            savestatus(rounds_played, stocks_list, balance, playerName);
            viewMode = false;
            time::sleep(sleepLong);
        }
    }
    return EXIT_SUCCESS;
}
