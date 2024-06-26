﻿/// @file graph.cpp
/// Graph plotting functions.
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
// This file should be saved in UTF-8 with BOM encoding
// to display the unicode characters correctly.
#include "graph.h"

#include "file_io.h"
#include "format.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

string graphpriceformat(float price) {
    // lock the max/min value between 6 chars
    stringstream ss;
    unsigned int exponent;
    ss << fixed << setprecision(2) << price;
    string pricestring = ss.str();
    if (price >= 100000) {
        exponent = pricestring.length() - 3;
        pricestring = string(1, pricestring[0]) + "." + string(1, pricestring[1]) + "e";
        if (exponent < 10) {
            pricestring += "0";
        }
        pricestring += to_string(exponent);
    } // change the max/min value to scientific notation if needed
    while (pricestring.size() < 6) {
        pricestring = " " + pricestring;
    }
    return pricestring;
}

void printstocknameandoverall(
    const string & stockname, vector<float> stockpricehistory, int stocknum) {
    string stocknameprint;
    if (stocknum != -1) {
        stocknameprint = "Stock: " + stockname;
    }
    else {
        stocknameprint = "HSI:";
    }
    float overall =
        (stockpricehistory[stockpricehistory.size() - 1] - stockpricehistory[0]) /
        stockpricehistory[0] * 100;
    cout << stocknameprint << R"(     % change: )";
    cout << graphpriceformat(overall) << "%" << endl;
    cout << endl;
}

void printgraphblocks(const vector<vector<string>> & screenElements,
    const vector<string> & specifiedColorCoordinates, const int width,
    const int height) {
    // Boundary check of width and height, otherwise may access screenElements out of
    // bounds
    assert(width <= static_cast<int>(screenElements.size()) &&
           "Width exceeds screenElements width");
    assert(height <= static_cast<int>(screenElements[0].size()) &&
           "Height exceeds screenElements height");
    int colorIndex;
    for (int heightIndex = 0; heightIndex < height; heightIndex++) {
        for (int widthIndex = 0; widthIndex < width; widthIndex++) {
            colorIndex = widthIndex - 9;
            if (colorIndex < 0) {
                colorIndex = width - 10;
            }
            string colorCode = textDefault;
            if (specifiedColorCoordinates[colorIndex] == textGreen) {
                colorCode = textGreen;
            }
            else if (specifiedColorCoordinates[colorIndex] == textRed) {
                colorCode = textRed;
            }
            cout << colorCode << screenElements[widthIndex][heightIndex] << textDefault;
        }
        cout << endl;
    }
}

// will delete print in the final version

vector<float> graphinput(
    const string & player, int stocknum, string & stockname, unsigned int width) {
    string filename;
    if (stocknum != -1) {
        filename = SAVE_FOLDER_PREFIX + player + "/" + to_string(stocknum) + "" +
                   SAVE_FILE_EXTENSION_TXT;
    }
    else {
        filename = SAVE_FOLDER_PREFIX + player + "/hsi" + SAVE_FILE_EXTENSION_TXT;
    }
    ifstream fin;
    float x;
    vector<float> stockpricehistory;
    fin.open(filename.c_str());
    if (stocknum != -1) {
        fin.ignore(256, '\n');
        getline(fin, stockname);
        fin >> x;
        while (x != -1) {
            stockpricehistory.emplace_back(x);
            fin >> x;
        }
    }
    else {
        float loadedPrice;
        while (fin >> loadedPrice) {
            stockpricehistory.emplace_back(loadedPrice);
        }
    }
    if (stockpricehistory.size() > (width - 9)) { // limit graph size to width
        stockpricehistory.erase(
            stockpricehistory.begin(), stockpricehistory.end() - (width - 9));
    }
    stockpricehistory.shrink_to_fit();
    return stockpricehistory;
}

void graph_plotting(const string & player, int stocknum, int width, int height) {
    float highest_price;
    float lowest_price;
    string stockname;
    vector<float> stockpricehistory = graphinput(player, stocknum, stockname, width);
    // convert the raw log input into the nearest "width" data points
    vector<string> color(width - 9, textWhite);
    color[width - 10] = textWhite;
    if (stockpricehistory.size() <= 1) {
        cout << "Why do you want to plot graph if there is only one data point?"
             << endl;
        return;
    }
    highest_price = *max_element(stockpricehistory.begin(), stockpricehistory.end());
    lowest_price = *min_element(stockpricehistory.begin(), stockpricehistory.end());
    float interval = (highest_price - lowest_price) / height;
    vector<vector<string>> graph(width, vector<string>(height, " "));
    // height column width rows, this is not in the usual 2d array format
    //  horizontal array and vertical array is inverted
    string maxstring;
    string minstring;
    if (interval == 0) {
        maxstring = graphpriceformat(highest_price + 1);
        minstring = graphpriceformat(lowest_price - 1);
    }
    else {
        maxstring = graphpriceformat(highest_price);
        minstring = graphpriceformat(lowest_price);
    }

    for (int i = 0; i < 6; i++) {
        graph[i][0] = maxstring[i];
        graph[i][height - 1] = minstring[i];
    }
    // \DeclareUnicodeCharacter{2517}{\L}

    for (unsigned int i = 0; i < stockpricehistory.size() - 1; i++) {
        int start = 10;
        int end = 10;
        if (interval != 0) {
            start = (height - 1) - (stockpricehistory[i] - lowest_price) / interval;
            end = (height - 1) - (stockpricehistory[i + 1] - lowest_price) / interval;
            // Checks to prevent out of bounds (SEGFAULT)
            if (start < 0) {
                start = 0;
            }
            if (end < 0) {
                end = 0;
            }
            if (start >= height) {
                start = height - 1;
            }
            if (end >= height) {
                end = height - 1;
            }
        }
        if (start == end) {
            graph[i + 9][start] = "■";
            if (stockpricehistory[i] > stockpricehistory[i + 1]) {
                color[i] = textGreen;
            }
            else if (stockpricehistory[i] < stockpricehistory[i + 1]) {
                color[i] = textRed;
            }
        }
        if (start > end) {
            for (int j = end; j <= start; j++) {
                graph[i + 9][j] = "■";
            }
            color[i] = textGreen;
        }
        else if (start < end) {
            for (int j = start; j <= end; j++) {
                graph[i + 9][j] = "■";
            }
            color[i] = textRed;
        }
        // idk why the colour is inverted using the normal setup method but i dont care
        // anyway it is running in normal HK stock colour indentations
    }
    for (int i = 0; i < height; i++) {
        graph[8][i] = "┃";
    }
    for (int i = 9; i < width; i++) {
        graph[i][height - 1] = "━";
    }
    graph[8][height - 1] = "┗";
    printstocknameandoverall(stockname, stockpricehistory, stocknum);
    printgraphblocks(graph, color, width, height);
}
