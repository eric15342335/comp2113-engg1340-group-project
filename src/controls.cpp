/// @file controls.cpp
/// Human-computer interactions functions.
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

void optionsInput(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, const std::vector<Stock_event> & events,
    bool & viewMode, bool & advance, bool & overlayEvent, bool & flush,
    bool & gameQuit) {
    char input;
    while (true) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << "Choose an option from the bar above: ";
        std::cin >> input;
        switch (input) {
            case 'B':
            case 'b':
                buyStocks(row, col, balance, tax, stocks, flush);
                break;
            case 'S':
            case 's':
                sellStocks(row, col, balance, tax, stocks, flush);
                break;
            case 'T':
            case 't':
                toggleView(viewMode, flush);
                break;
            case 'E':
            case 'e':
                if (!overlayEvent) {
                    overlayEvent = true;
                    listEvents(row, col, events);
                }
                else {
                    flush = true;
                }
                break;
            case 'N':
            case 'n':
                advanceConfirmation(row, col, advance, flush);
                break;
            // case 'O':
            // case 'o':
            //     break;
            case 'X':
            case 'x':
                quitConfirmation(row, col, flush, gameQuit);
                break;
            default:
                std::cout << setCursorPosition(row, 3) << "\x1b[2K";
                std::cout << "nope";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                time::sleep(sleepMedium);
                continue;
        }
        break;
    }
}

int integerInput(int row, int col, const std::string & message) {
    std::ignore = col;
    int num;
    while (true) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << message;
        std::cin >> num;
        if (!std::cin) {
            std::cin.clear();
            std::cout << setCursorPosition(row, 3) << "\x1b[2K";
            std::cout << "don't";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            time::sleep(sleepMedium);
            continue;
        }
        return num;
    }
}

void buyStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & flush) {
    int index;
    int amount;

    index = integerInput(row, col, "Enter the index of the stock as shown: ");
    while (index < 1 || index > (int)stocks.size()) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << "Index out of range!";
        time::sleep(sleepMedium);
        index = integerInput(row, col, "Enter the index of the stock as shown: ");
    }
    amount = integerInput(row, col, "Enter the amount to buy (0 to skip): ");
    while (amount < 0) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << "You cannot purchase negative amounts!";
        time::sleep(sleepMedium);
        index = integerInput(row, col, "Enter the amount to buy (0 to skip): ");
    }
    while (amount > (int)stocks[index - 1].num_stocks_affordable(balance, tax)) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << "Cannot afford!";
        time::sleep(sleepMedium);
        amount = integerInput(row, col, "Enter the amount to buy (0 to skip): ");
    }
    stocks[index - 1].purchase(balance, amount, tax);
    flush = true;
}

void sellStocks(int row, int col, float & balance, float tax,
    std::vector<Stock> & stocks, bool & flush) {
    int index;
    int amount;

    index = integerInput(row, col, "Enter the index of the stock as shown: ");
    while (index < 1 || index > (int)stocks.size()) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << "Index out of range!";
        time::sleep(sleepMedium);
        index = integerInput(row, col, "Enter the index of the stock as shown: ");
    }
    amount = integerInput(row, col, "Enter the amount to sell (0 to skip): ");
    while (amount < 0) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << "You cannot sell negative amounts!";
        time::sleep(sleepMedium);
        index = integerInput(row, col, "Enter the amount to sell (0 to skip): ");
    }
    while (amount > (int)stocks[index - 1].get_quantity()) {
        std::cout << setCursorPosition(row, 3) << "\x1b[2K";
        std::cout << "You do not have this many stocks!";
        time::sleep(sleepMedium);
        amount = integerInput(row, col, "Enter the amount to sell (0 to skip): ");
    }
    stocks[index - 1].sell(balance, amount, tax);
    flush = true;
}

void toggleView(bool & viewMode, bool & flush) {
    viewMode = !viewMode;
    flush = true;
}

void advanceConfirmation(int row, int col, bool & advance, bool & flush) {
    std::ignore = col;
    char input;
    std::cout << setCursorPosition(row, 3) << "\x1b[2K";
    std::cout << "Press [Y] to confirm: ";
    std::cin >> input;
    if (input == 'Y' || input == 'y') {
        advance = true;
        flush = true;
    }
}

void quitConfirmation(int row, int col, bool & flush, bool & gameQuit) {
    std::ignore = col;
    char input;
    std::cout << setCursorPosition(row, 0) << "\x1b[2K";
    std::cout << "Press [Y] to confirm: ";
    std::cin >> input;
    if (input == 'Y' || input == 'y') {
        gameQuit = true;
        flush = true;
    }
}