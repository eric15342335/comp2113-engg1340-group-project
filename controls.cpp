#include <ios>
#include <iostream>
#include <limits>
#include <tuple>
#include "draw.h"
#include "format.h"
#include "controls.h"

void optionsInput(int row, int col) {
    char input;
    while (1) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "Choose an option from the bar above: ";
        std::cin >> input;
        switch (input) {
        case 'B':
            buyStocks(row, col);
            break;
        case 'b':
            buyStocks(row, col);
            break;
        case 'S':
            sellStocks(row, col);
            break;
        case 's':
            sellStocks(row, col);
            break;
        case 'T':
            break;
        case 't':
            break;
        case 'E':
            break;
        case 'e':
            break;
        case 'O':
            break;
        case 'o':
            break;
        case 'X':
            quitConfirmation(row, col);
            break;
        case 'x':
            quitConfirmation(row, col);
            break;
        default:
            std::cout << setCursorPosition(row, 0) << "\x1b[2K";
            std::cout << "nope";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            time::sleep(200);
            continue;
        }
        break;
    }
}

int integerInput(int row, int col, std::string message) {
    std::ignore = col;
    int num;
    while (1) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << message;
        std::cin >> num;
        if (!std::cin) {
            std::cin.clear();
            std::cout << setCursorPosition(row, 0) << "\x1b[2K";
            std::cout << "don't";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            time::sleep(200);
            continue;
        }
        return num;
    }
}

void buyStocks(int row, int col) {
    int index;
    int amount = 1;

    index = integerInput(row, col, "Enter the index of the stock as shown: ");
    // stocks_list[index - 1].purchase(balance, amount, trading_fees_percent);

    std::ignore = index;
    std::ignore = amount;
}

void sellStocks(int row, int col) {
    int index;
    int amount = 1;

    index = integerInput(row, col, "Enter the index of the stock as shown: ");
    // stocks_list[index - 1].sell(balance, amount, trading_fees_percent);

    std::ignore = index;
    std::ignore = amount;
}

void quitConfirmation(int row, int col) {
    std::ignore = col;
    char input;
    std::cout << setCursorPosition(row, 0) << "\x1b[2K";
    std::cout << "Press [Y] to confirm: ";
    std::cin >> input;
    if (input == 'Y' || input == 'y') {
        std::exit(0);
    }
    else {
        optionsInput(row, col);
    }
}