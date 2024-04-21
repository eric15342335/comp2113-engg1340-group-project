#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include "draw.h"
#include "format.h"
#include "input_events.h"

void optionsInput(int row, int col) {
    char input;
    while (1) {
        std::cout << setCursorPosition(row, 0) << "\x1b[2K";
        std::cout << "whatdoyouwant: ";
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
    col++; // Shutup compiler
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

    index = integerInput(row, col, "give index pls: ");
    index++;
}

void sellStocks(int row, int col) {
    int index;

    index = integerInput(row, col, "give index pls: ");
    index++;
}