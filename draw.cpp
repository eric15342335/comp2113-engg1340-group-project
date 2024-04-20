#include <iostream>
#include <string>
#include <vector>
#include "draw.h"
#include "format.h"

void drawLogo(int row, int col) {
    const int wordWidth = 73; // Width of the longest word
    const int wordHeight = 8; // Height for each word

    std::cout << textClear << setCursorPosition(0, 0);

    // Will not print logo if terminal cannot fit
    if (row > wordHeight && col > wordWidth) {
        // Will use fileIO for this
        std::cout << "Insert"
                  << "\n";
        time::sleep(1000);
        std::cout << textClear;
        time::sleep(250);
        std::cout << "Logo"
                  << "\n";
        time::sleep(1000);
        std::cout << textClear;
        time::sleep(250);
        std::cout << "Here"
                  << "\n";
    }
    else {
        std::cout << "Welcome to Stock Market Simulator!"
                  << "\n";
    }
}

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
    row++;
    // broken rn
    int height = 10; // placeholder
    int width = col - 30;

    std::cout << setCursorPosition(2, 15) << "\u250C";
    for (int i = 0; i < width - 1; i++) {
        std::cout << "\u2500";
    }
    std::cout << "\u2510";
    for (int i = 0; i < height; i++) {
        std::cout << setCursorPosition(i + 3, 15);
        std::cout << "\u2502";
        std::cout << setCursorPosition(i + 3, width + 15);
        std::cout << "\u2502";
    }
}

void drawButton(int row, int col) {
    int width;
    int buttons;

    std::vector<std::string> options = {"[B] Buy", "[S] Sell", "[T] Toggle View", "[E] Events", "[O] Options", "[X] Exit"}; // Add stuff here

    buttons = options.size();
    width = (int)(col / buttons);

    /*
    std::cout << setCursorPosition(row - 2, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << textBlack << bgWhite : std::cout << textWhite << bgBlack;
        for (int j = 0; j < width; j++) {
            std::cout << " ";
        }
    }
    */

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
    /*
    std::cout << textReset << setCursorPosition(row, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << textBlack << bgWhite : std::cout << textWhite << bgBlack;
        for (int j = 0; j < width; j++) {
            std::cout << " ";
        }
    }
    */
    std::cout << textReset << "\n";
}