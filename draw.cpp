#include "draw.h"

#include "file_io.h"

void drawLogo(int row, int col) {
    const int wordWidth = 73; // Width of the longest word
    const int wordHeight = 8; // Height for each word
    std::vector<std::string> logo = parseLogo();

    std::cout << textClear << setCursorPosition(0, 0);

    // Will not print logo if terminal cannot fit
    if (row > wordHeight && col > wordWidth) {
        // Will use fileIO for this
        for (int i = 0; i < 9; i++) {
            std::cout << logo[i] << "\n";
        }
        time::sleep(sleepMedium);
        std::cout << textClear << setCursorPosition(0, 0);
        time::sleep(sleepShort);
        for (int i = 9; i < 18; i++) {
            std::cout << logo[i] << "\n";
        }
        time::sleep(sleepMedium);
        std::cout << textClear << setCursorPosition(0, 0);
        time::sleep(sleepShort);
        for (int i = 18; i < 27; i++) {
            std::cout << logo[i] << "\n";
        }
        time::sleep(sleepMedium);
    }
    else {
        std::cout << "Welcome to Stock Market Simulator!\n";
    }
    std::cout << textClear << setCursorPosition(0, 0);
}

void drawRoundInfo(
    int row, int col, int round, float balance, std::string player, float indexHSI) {
    std::ignore = row; // Shutup compiler
    std::cout << setCursorPosition(2, 5);
    std::cout << "Round " << round;

    if (player.size() > 15) {
        std::cout << setCursorPosition(4, 0);
        std::cout << player.erase(12) << "...";
    }
    else {
        std::cout << setCursorPosition(4, (int)((15 - player.size()) / 2 + 1));
        std::cout << player;
    }
    std::cout << setCursorPosition(2, col - 10);
    std::cout << "$" << balance;
    std::cout << setCursorPosition(4, col - 12);
    std::cout << "  HSI: " << indexHSI;
}

void drawEventBar(int row, int col) {
    std::ignore = row; // Shutup compiler
    int width = col - 32;

    std::cout << setCursorPosition(2, 16) << "\u250C";
    for (int i = 0; i < width - 1; i++) {
        std::cout << "\u2500";
    }
    std::cout << "\u2510" << setCursorPosition(3, 16) << "\u2502";
    std::cout << setCursorPosition(3, width + 16) << "\u2502";
    std::cout << setCursorPosition(4, 16) << "\u2514";
    for (int i = 0; i < width - 1; i++) {
        std::cout << "\u2500";
    }
    std::cout << "\u2518";
}

void listEvents(int row, int col, std::vector<Stock_event> events) {
    int height;
    int width = col - 20;

    if ((int)events.size() < row - 10) {
        if ((int)events.size() != 0) {
            height = (int)events.size() + 2;
        }
        else {
            height = 3;
        }
    }
    else {
        height = row - 10;
    }

    std::cout << setCursorPosition(6, 10) << "\u250C";
    for (int i = 0; i < width - 1; i++) {
        std::cout << "\u2500";
    }
    std::cout << "\u2510";
    for (int i = 0; i < height; i++) {
        std::cout << setCursorPosition(i + 7, 10);
        std::cout << "\u2502";
        std::cout << setCursorPosition(i + 7, width + 10);
        std::cout << "\u2502";
    }
    std::cout << setCursorPosition(height + 7, 10) << "\u2514";
    for (int i = 0; i < width - 1; i++) {
        std::cout << "\u2500";
    }
    std::cout << "\u2518";

    std::cout << setCursorPosition(7, 11);
    for (int i = 0; i < width - 1; i++) {
        std::cout << " ";
    }
    if ((int)events.size() == 0) {
        std::cout << setCursorPosition(8, 11);
        std::cout << "There are currently no events!";
        for (int i = 0; i < width - 31; i++) {
            std::cout << " ";
        }
        std::cout << setCursorPosition(9, 11);
        for (int i = 0; i < width - 1; i++) {
            std::cout << " ";
        }
    }
    else {
        for (int i = 1; i < (int)events.size() + 1; i++) {
            std::cout << setCursorPosition(i + 7, 11);
            std::cout << i << ". " << events[i - 1].text;
            int digits = (int)(((i) / 10) + 1);
            for (int j = 0; j < width - (int)events[i - 1].text.size() - 3 - digits;
                 j++) {
                std::cout << " ";
            }
        }
        std::cout << setCursorPosition((int)events.size() + 8, 11);
        for (int i = 0; i < width - 1; i++) {
            std::cout << " ";
        }
    }
}

void drawButton(int row, int col) {
    int width;
    int buttons;

    std::vector<std::string> options = {"[B] Buy", "[S] Sell", "[T] Toggle View",
        "[E] Events", "[N] Next Round", "[X] Exit"}; // Add stuff here

    buttons = options.size();
    width = (int)(col / buttons);

    std::cout << textReset << setCursorPosition(row - 1, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << bgWhite << textBlack
                   : std::cout << bgBlack << textWhite;
        for (int j = 0; j < (int)((width - options[i].length()) / 2); j++) {
            std::cout << " ";
        }
        std::cout << textBold << options[i] << "\x1b[22m";
        for (int j = 0;
             j < (int)(width - options[i].length() - (width - options[i].length()) / 2);
             j++) {
            std::cout << " ";
        }
    }
    std::cout << textReset << "\n";
}