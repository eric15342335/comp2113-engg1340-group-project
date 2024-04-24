#include "controls.h"

#include "draw.h"
#include "format.h"

#include <ios>
#include <iostream>
#include <limits>
#include <tuple>

void optionsInput(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks, bool& advance, bool& gameQuit, bool& optionsQuit) {
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
            case 'N':
            case 'n':
                advanceConfirmation(row, col, advance, optionsQuit);
                break;
            case 'O':
            case 'o':
                break;
            case 'X':
            case 'x':
                quitConfirmation(row, col, gameQuit, optionsQuit);
                break;
            default:
                std::cout << setCursorPosition(row, 0) << "\x1b[2K";
                std::cout << "nope";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                time::sleep(1000);
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
            time::sleep(1000);
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
    while (index < 1 || index > (int)stocks.size()) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "Index out of range!";
        time::sleep(1000);
        index = integerInput(row, col, "Enter the index of the stock as shown: ");
    }
    amount = integerInput(row, col, "Enter the amount to buy (0 to skip): ");
    while (amount < 0) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "You cannot purchase negative amounts!";
        time::sleep(1000);
        index = integerInput(row, col, "Enter the amount to buy (0 to skip): ");
    }
    while (amount > (int)stocks[index - 1].num_stocks_affordable(balance, tax)) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "Cannot afford!";
        time::sleep(1000);
        amount = integerInput(row, col, "Enter the amount to buy (0 to skip): ");
    }
    stocks[index - 1].purchase(balance, amount, tax);
}

void sellStocks(
    int row, int col, float & balance, float tax, std::vector<Stock> & stocks) {
    int index;
    int amount;

    index = integerInput(row, col, "Enter the index of the stock as shown: ");
    while (index < 1 || index > (int)stocks.size()) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "Index out of range!";
        time::sleep(1000);
        index = integerInput(row, col, "Enter the index of the stock as shown: ");
    }
    amount = integerInput(row, col, "Enter the amount to sell (0 to skip): ");
    while (amount < 0) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "You cannot sell negative amounts!";
        time::sleep(1000);
        index = integerInput(row, col, "Enter the amount to sell (0 to skip): ");
    }
    while (amount > (int)stocks[index - 1].get_quantity()) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "You do not have this many stocks!";
        time::sleep(1000);
        amount = integerInput(row, col, "Enter the amount to sell (0 to skip): ");
    }
    stocks[index - 1].sell(balance, amount, tax);
}

void advanceConfirmation(int row, int col, bool& advance, bool& optionsQuit) {
    std::ignore = col;
    char input;
    std::cout << setCursorPosition(row, 0) << "\x1b[2K";
    std::cout << "Press [Y] to confirm: ";
    std::cin >> input;
    if (input == 'Y' || input == 'y') {
        advance = 1;
        optionsQuit = 1;
    }
}

void quitConfirmation(
    int row, int col, bool& gameQuit, bool& optionsQuit) {
    std::ignore = col;
    char input;
    std::cout << setCursorPosition(row, 0) << "\x1b[2K";
    std::cout << "Press [Y] to confirm: ";
    std::cin >> input;
    if (input == 'Y' || input == 'y') {
        gameQuit = 1;
        optionsQuit = 1;
    }
}