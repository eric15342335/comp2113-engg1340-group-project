/// @file format.h
/// Header file for the ANSI Escape code related functions.
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

#ifndef FORMAT_H
#define FORMAT_H

#include <chrono>
#include <string>
#include <thread>

extern const std::string textClear;
extern const std::string textReset;

extern const std::string textBold;
extern const std::string textItalic;
extern const std::string textUnderline;
extern const std::string textStrikethrough;

extern const std::string textDefault;
extern const std::string textBlack;
extern const std::string textRed;
extern const std::string textGreen;
extern const std::string textYellow;
extern const std::string textBlue;
extern const std::string textMagenta;
extern const std::string textCyan;
extern const std::string textWhite;

extern const std::string bgDefault;
extern const std::string bgBlack;
extern const std::string bgRed;
extern const std::string bgGreen;
extern const std::string bgYellow;
extern const std::string bgBlue;
extern const std::string bgMagenta;
extern const std::string bgCyan;
extern const std::string bgWhite;

extern const int sleepShort;
extern const int sleepMedium;
extern const int sleepLong;

/// @brief Mimics python sleep() behaviour, with param milliseconds.
class time {
    public:
        static void sleep(int dur); // unit is in ms
};

extern std::string setCursorPosition(int offsetY, int offsetX); // same as below

extern void fetchConsoleDimensions(
    int & row, int & col); // number of characters each row and column can fit, not the
                           // number of pixels

#endif