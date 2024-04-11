#include "graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

string graphpriceformat(float price) {
    stringstream ss;
    ss << fixed << setprecision(2) << price;
    string pricestring = ss.str();
    while (pricestring.size() < 6) {
        pricestring = " " + pricestring;
    }
    return pricestring;
}

void printstocknameandoverall(string stockname, vector<float> stockpricehistory) {
    string stocknameprint = "Stock: " + stockname;
    float overall = (stockpricehistory[70] - stockpricehistory[0]) / stockpricehistory[0] * 100;
    cout << stocknameprint << "     %" << " change: ";
    cout << graphpriceformat(overall) << "%" << endl;
    cout << endl;
}

void printarray(string arrayname[80][21], string color[71]) {
    int colorint;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            colorint = j - 9;
            if (colorint < 0) {
                colorint = 70;
            }
            if (color[colorint] == "green") {
                cout << "\033[1;31m" << arrayname[j][i] << "\033[0m";
            }
            else if (color[colorint] == "red") {
                cout << "\033[1;32m" << arrayname[j][i] << "\033[0m";
            }
            else {
                cout << arrayname[j][i];
            }
        }
        cout << endl;
    }
}

// will delete print in the final version

vector<float> graphinput(string stockname) {
    string filename = stockname + ".log";
    ifstream fin;
    float x;
    vector<float> stockpricehistory;
    fin.open(filename.c_str());
    while (fin >> x) {
        stockpricehistory.push_back(x);
    }
    if (stockpricehistory.size() > 71) { // limit graph size to 71
        stockpricehistory.erase(stockpricehistory.begin(), stockpricehistory.end() - 71);
    }
    stockpricehistory.shrink_to_fit();
    return stockpricehistory;
}

void graph_plotting(string stockname) {
    float max, min;
    vector<float> stockpricehistory = graphinput(stockname);
    // convert the raw log input into the nearest 71 data points
    string color[71];
    color[70] = "white";
    if (stockpricehistory.size() <= 1) {
        return;
    }
    max = *max_element(stockpricehistory.begin(), stockpricehistory.end());
    min = *min_element(stockpricehistory.begin(), stockpricehistory.end());
    float interval = (max - min) / 21;
    string graph[80][21];
    // 21 column 80 rows, this is not in the usual 2d array format
    //  horizontal array and vertical array is inverted
    string maxstring = graphpriceformat(max);
    string minstring = graphpriceformat(min);
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 21; j++) {
            graph[i][j] = " ";
        }
    }
    for (int i = 0; i < 21; i++) {
        graph[8][i] = "┃";
    }
    for (int i = 9; i < 80; i++) {
        graph[i][20] = "━";
    }
    for (int i = 0; i < 6; i++) {
        graph[i][0] = maxstring[i];
        graph[i][20] = minstring[i];
    }
    graph[8][20] = "┗";

    for (int i = 0; i < 70; i++) {
        int start = 20 - (stockpricehistory[i] - min) / interval;
        int end = 20 - (stockpricehistory[i + 1] - min) / interval;
        if (start == end) {
            graph[i + 9][start] = "■";
            continue;
        }
        if (start > end) {
            for (int j = end; j <= start; j++) {
                graph[i + 9][j] = "■";
            }
            color[i] = "red";
        }
        else {
            for (int j = start; j <= end; j++) {
                graph[i + 9][j] = "■";
            }
            color[i] = "green";
        }
    }
    printstocknameandoverall(stockname, stockpricehistory);
    printarray(graph, color);
}

// int main(){
//     graph_plotting("StockA");
//     return 0;
// }
// this main is for testing purpose of this cpp only