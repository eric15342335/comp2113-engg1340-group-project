/**
 * @file file_io.cpp
 * @brief This file contains the implementation of the file input/output functions.
 * @author Comet13579
 */

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "file_io.h"
using namespace std;

void createplayer(string & playerName) {
    ofstream fout;
    string savefolder = "saves"; // create folder when it does not exist (first run)
    string foldername;
    filesystem::create_directory("saves");
    cout << "Enter player name:" << endl;
    cin >> playerName;
    foldername = "saves/" + playerName;
    while (filesystem::exists(foldername)) { // check whether file already exists
        cout << "Player name already exists, please enter a new name:" << endl;
        cin >> playerName;
        foldername = "saves/" + playerName;
    }
    filesystem::create_directory(foldername); // create a empty folder for new save
}

void savestatus(unsigned int rounds_played, vector<Stock> stocks_list, float balance, string playerName) {
    string stocksave;
    ofstream fout;
    stocksave = "saves/" + playerName + "/playerstatus.save";
    fout.open(stocksave.c_str());
    fout << playerName << " " << rounds_played << " " << balance << endl; // saving basic info out of class inside playerstatus.save
    fout.close();
    for (unsigned long i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].save(playerName, i); // save stock info inside class in seperate file
    }
}

void loadstatus(unsigned int & rounds_played, vector<Stock> & stocks_list, float & balance, string & playerName) {
    string stockload, stockname, inputname;
    ifstream fin;
    vector<string> players;
    filesystem::create_directory("saves"); // prevent error when no folder exists
    players = get_saves();                 // generate a vector of name of folders
    if (players.empty()) {
        cout << "No player saves found, please create a new player." << endl;
        createplayer(playerName);
        return; // rejection of loading when no save files exist
    }
    cout << "Enter player name from the following:" << endl;
    printvector(players);
    cin >> inputname;
    while (std::find(players.begin(), players.end(), inputname) == players.end()) { // reject incorrect input
        cout << "Player name does not exist, please enter a new name from the following:" << endl;
        printvector(players);
        cin >> inputname;
    }

    stockload = "saves/" + inputname + "/playerstatus.save";
    playerName = inputname;
    fin.open(stockload.c_str());
    fin >> playerName >> rounds_played >> balance;
    fin.close(); // output basic info from playerstatus.save and return by reference

    for (unsigned long i = 0; i < 20; i++) { // hard code 20 stocks
        stocks_list[i].load(inputname, i);   // load stocks info to class in seperate files
    }
}

vector<string> get_saves() {
    vector<string> saves;
    for (const auto & entry : std::filesystem::directory_iterator("saves")) {
        saves.push_back(entry.path().string().substr(6));
    }
    return saves;
}

void printvector(vector<string> avector) {
    cout << avector[0];
    for (unsigned long i = 1; i < avector.size(); i++) {
        cout << ", " << avector[i];
    }
    cout << endl;
}