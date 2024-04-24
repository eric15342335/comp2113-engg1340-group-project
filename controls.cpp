#include "controls.h"

#include "draw.h"
#include "format.h"

#include <ios>
#include <iostream>
#include <limits>
#include <tuple>

void optionsInput(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks) {
    char input;
    while (1) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "Choose an option from the bar above: ";
        std::cin >> input;
        switch (input) {
            case 'B':
            case 'b':
                buyStocks(row, col, balance, tax, stocks);
                break;
            case 'S':
            case 's':
                sellStocks(row, col, balance, tax, stocks);
                break;
            case 'T':
            case 't':
                break;
            case 'E':
            case 'e':
                break;
            case 'O':
            case 'o':
                break;
            case 'X':
                quitConfirmation(row, col, balance, tax, stocks);
                break;
            case 'x':
                quitConfirmation(row, col, balance, tax, stocks);
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

void buyStocks(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks) {
    int index;
    int amount;

    index = integerInput(row, col, "Enter the index of the stock as shown: ");
    amount = integerInput(row, col, "Enter the amount to buy: ");
    stocks[index - 1].purchase(balance, amount, tax);
}

void sellStocks(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks) {
    int index;
    int amount;

    index = integerInput(row, col, "Enter the index of the stock as shown: ");
    amount = integerInput(row, col, "Enter the amount to buy: ");
    stocks[index - 1].sell(balance, amount, tax);
}

void quitConfirmation(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks) {
    std::ignore = col;
    char input;
    std::cout << setCursorPosition(row, 0) << "\x1b[2K";
    std::cout << "Press [Y] to confirm: ";
    std::cin >> input;
    if (input == 'Y' || input == 'y') {
        std::exit(0);
    }
    else {
        optionsInput(row, col, balance, tax, stocks);
    }
}