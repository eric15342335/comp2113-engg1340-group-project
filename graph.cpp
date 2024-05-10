// This file should be saved in UTF-8 with BOM encoding
// to display the unicode characters correctly,
#include "graph.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string graphpriceformat(float price) { // lock the max/min value between 6 chars
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
    string stockname, vector<float> stockpricehistory, int stocknum) {
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

void printvector(
    vector<vector<string>> vectorname, vector<string> color, int width, int height) {
    int colorint;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            colorint = j - 9;
            if (colorint < 0) {
                colorint = width - 10;
            }
            if (color[colorint] == "green") {
                cout << "\033[1;31m" << vectorname[j][i] << "\033[0m";
            }
            else if (color[colorint] == "red") {
                cout << "\033[1;32m" << vectorname[j][i] << "\033[0m";
            }
            else {
                cout << vectorname[j][i];
            }
        }
        cout << endl;
    }
}

// will delete print in the final version

vector<float> graphinput(
    string player, int stocknum, string & stockname, unsigned int width) {
    string filename;
    if (stocknum != -1) {
        filename = "saves/" + player + "/" + to_string(stocknum) + ".save";
    }
    else {
        filename = "saves/" + player + "/hsi.save";
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

void graph_plotting(string player, int stocknum, int width, int height) {
    float max, min;
    string stockname;
    vector<float> stockpricehistory = graphinput(player, stocknum, stockname, width);
    // convert the raw log input into the nearest "width" data points
    vector<string> color(width - 9, "white");
    color[width - 10] = "white";
    if (stockpricehistory.size() <= 1) {
        cout << "Why do you want to plot graph if there is only one data point?"
             << endl;
        return;
    }
    max = *max_element(stockpricehistory.begin(), stockpricehistory.end());
    min = *min_element(stockpricehistory.begin(), stockpricehistory.end());
    float interval = (max - min) / height;
    vector<vector<string>> graph(width, vector<string>(height, " "));
    // height column width rows, this is not in the usual 2d array format
    //  horizontal array and vertical array is inverted
    string maxstring, minstring;
    if (interval == 0) {
        maxstring = graphpriceformat(max + 1);
        minstring = graphpriceformat(min - 1);
    }
    else {
        maxstring = graphpriceformat(max);
        minstring = graphpriceformat(min);
    }

    for (int i = 0; i < 6; i++) {
        graph[i][0] = maxstring[i];
        graph[i][height - 1] = minstring[i];
    }
    // \DeclareUnicodeCharacter{2517}{\L}

    for (unsigned int i = 0; i < stockpricehistory.size() - 1; i++) {
        int start = 10, end = 10;
        if (interval != 0) {
            start = (height - 1) - (stockpricehistory[i] - min) / interval;
            end = (height - 1) - (stockpricehistory[i + 1] - min) / interval;
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
                color[i] = "green";
            }
            else if (stockpricehistory[i] < stockpricehistory[i + 1]) {
                color[i] = "red";
            }
            else {
                color[i] = "white";
            }
            continue;
        }
        if (start > end) {
            for (int j = end; j <= start; j++) {
                graph[i + 9][j] = "■";
            }
            color[i] = "red";
        }
        else if (start < end) {
            for (int j = start; j <= end; j++) {
                graph[i + 9][j] = "■";
            }
            color[i] = "green";
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
    printvector(graph, color, width, height);
}