#include <iostream>
#include <string>
#include <vector>
#include "draw.h"
#include "format.h"

void drawRoundInfo(int row, int col, int round, float balance) {
    row++; // Shutup compiler
    std::cout << setCursorPosition(3, 5);
    std::cout << "Round " << round;
    std::cout << setCursorPosition(3, col - 10);
    std::cout << "$" << balance;
}

void drawEventBar(int row, int col) {
    row++; // Shutup compiler
    int width = col - 30;

    std::cout << setCursorPosition(2, 15) << "\u250C";
    for (int i = 0; i < width - 1; i++) {
        std::cout << "\u2500";
    }
    std::cout << "\u2510" << setCursorPosition(3, 15) << "\u2502";
    std::cout << setCursorPosition(3, width + 15) << "\u2502";
    std::cout << setCursorPosition(4, 15) << "\u2514";
    for (int i = 0; i < width - 1; i++) {
        std::cout << "\u2500";
    }
    std::cout << "\u2518";
}

void listEvents(int row, int col) {
    // later do
    row++;
    col++;
}

void drawButton(int row, int col) {
    int width;
    int buttons;

    std::vector<std::string> options = {"[B] Buy", "[S] Sell", "[E] Events", "[O] Options", "[X] Exit"}; // Add stuff here

    buttons = options.size();
    width = (int)(col / buttons);
    std::cout << setCursorPosition(row - 2, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << textBlack << bgWhite : std::cout << textWhite << bgBlack;
        for (int j = 0; j < width; j++) {
            std::cout << " ";
        }
    }
    std::cout << textReset << setCursorPosition(row - 1, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << bgWhite << textBlack : std::cout << bgBlack << textWhite;
        for (int j = 0; j < (int)((width - options[i].length()) / 2); j++) {
            std::cout << " ";
        }
        std::cout << textBold << options[i] << "\x1b[22m";
        for (int j = 0; j < (int)(width - options[i].length() - (width - options[i].length()) / 2); j++) {
            std::cout << " ";
        }
    }
    std::cout << textReset << setCursorPosition(row, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << textBlack << bgWhite : std::cout << textWhite << bgBlack;
        for (int j = 0; j < width; j++) {
            std::cout << " ";
        }
    }
    std::cout << textReset << "\n";
}

/*
int main() {
    int row;
    int col;
    while (1) {
        fetchConsoleDimensions(row, col);
        drawEventBar(row, col);
        drawButton(row, col);
        sleep(200);
        std::cout << textClear;
    }
    return 0;
}
*/