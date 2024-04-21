#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include "format.h"
#include "input_events.h"

void charInput(int row, int col) {
    col++; // Shutup compiler
    char input;
    while (1) {
        std::cout << setCursorPosition(row, 0);
        std::cout << "whatdoyouwant: ";
        std::cin >> input;
        switch (input) {
            case 'x':
                std::exit(0);
            default:
                std::cout << "\x1b[K";
                std::cout << "nope";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int integerInput(int row, int col) {
    col++; // Shutup compiler
    int num;
    while (1) {
        std::cout << setCursorPosition(row, 0);
        std::cout << "gimme integer: ";
        std::cin >> num;
        if (!std::cin) {
            std::cin.clear();
            std::cout << "\x1b[K";
            std::cout << "don't";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return num;
    }
}