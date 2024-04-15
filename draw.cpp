#include <iostream>
#include <string>
#include <vector>
#include "format.h"


void drawButton() {
    int row;
    int col;
    int width;
    int buttons;
    fetchConsoleDimensions(row, col);

    std::vector<std::string> options = {"[B] Buy", "[S] Sell", "[O] Options", "[E] Exit"}; // Add stuff here

    buttons = options.size();
    width = (int)col/buttons;
    std::cout << setCursorPosition(row-4, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << textBlack << bgWhite : std::cout << textWhite << bgBlack;
        for (int j = 0; j < width; j++) {
            std::cout << " ";
        }
    }
    std::cout << textReset << setCursorPosition(row-3, 3);
    for (int i = 0; i < buttons; i++) {
        i % 2 == 0 ? std::cout << bgWhite << textBlack : std::cout << bgBlack << textWhite;
        for (int j = 0; j < (width-options[i].length())/2; j++) {
            std::cout << " ";
        }
        std::cout << textBold << options[i] << "\x1b[22m";
        for (int j = 0; j < width-options[i].length()-(width-options[i].length())/2; j++) {
            std::cout << " ";
        }
    }
    std::cout << textReset << setCursorPosition(row-2, 3);
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
    while (1) {
        drawButton();
        sleep(200);
        std::cout << textClear;
    }
    return 0;
}
*/