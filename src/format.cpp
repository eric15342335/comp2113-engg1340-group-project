/// @file format.cpp
/// ANSI Escape Code related functions.
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

#include "format.h"

using namespace std;

const string textClear = "\x1b[2J";
const string textReset = "\x1b[0m";

const string textBold = "\x1b[1m";
const string textItalic = "\x1b[3m";
const string textUnderline = "\x1b[4m";
const string textStrikethrough = "\x1b[9m";

const string textDefault = "\x1b[39m";
const string textBlack = "\x1b[30m";
const string textRed = "\x1b[31m";
const string textGreen = "\x1b[32m";
const string textYellow = "\x1b[33m";
const string textBlue = "\x1b[34m";
const string textMagenta = "\x1b[35m";
const string textCyan = "\x1b[36m";
const string textWhite = "\x1b[37m";

const string bgDefault = "\x1b[49m";
const string bgBlack = "\x1b[40m";
const string bgRed = "\x1b[41m";
const string bgGreen = "\x1b[42m";
const string bgYellow = "\x1b[43m";
const string bgBlue = "\x1b[44m";
const string bgMagenta = "\x1b[45m";
const string bgCyan = "\x1b[46m";
const string bgWhite = "\x1b[47m";

const int sleepShort = 100;
const int sleepMedium = 500;
const int sleepLong = 1000;

void time::sleep(int dur) {
    std::this_thread::sleep_for(std::chrono::milliseconds(dur));
}

string setCursorPosition(int offsetY, int offsetX) {
    string base = "\x1b[";
    base = base + to_string(offsetY) + ";" + to_string(offsetX) + "H";
    return base;
}

void fetchConsoleDimensions(int & row, int & col) {
    /** @todo Suggest terminal sizes.
     * Dynamic size needs testing on windows.
     * Not implemented because of time constraints.
     */
    int mode = 2;
    // Before moving to production, we use the printTable() function with
    // the mode parameter set to "dev" for testing purposes.
    // However, in production, we will use the mode parameter set to "normal"
    // which will result in fewer columns being printed. This reduction in columns
    // may cause misalignment of the table, so we need to adjust the offset accordingly.
    // for dev mode, the offset is 0
    const int normalTableModeOffset = 20;
    switch (mode) {
        case 1:
            row = 30;
            col = 80 - normalTableModeOffset;
            break;
        case 2:
            row = 36;
            col = 120 - normalTableModeOffset;
            break;
        case 3:
            row = 48;
            col = 160 - normalTableModeOffset;
            break;
        default:
            row = 36;
            col = 120 - normalTableModeOffset;
            break;
    }
}