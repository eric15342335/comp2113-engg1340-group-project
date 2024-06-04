/// @file file_io.cpp
/// Implementation of the file input/output functions.
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

#include "file_io.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace std;

vector<string> parseLogo() {
    vector<string> logo;
    // clang-format off
    logo.reserve(27);
    logo.emplace_back(R"(            __                       __)");
    logo.emplace_back(R"(           |  \                     |  \)");
    logo.emplace_back(R"(  _______ _| $$_    ______   _______| $$   __)");
    logo.emplace_back(R"( /       |   $$ \  /      \ /       | $$  /  \)");
    logo.emplace_back(R"(|  $$$$$$$\$$$$$$ |  $$$$$$|  $$$$$$| $$_/  $$)");
    logo.emplace_back(R"( \$$    \  | $$ __| $$  | $| $$     | $$   $$)");
    logo.emplace_back(R"( _\$$$$$$\ | $$|  | $$__/ $| $$_____| $$$$$$\)");
    logo.emplace_back(R"(|       $$  \$$  $$\$$    $$\$$     | $$  \$$\)");
    logo.emplace_back(R"( \$$$$$$$    \$$$$  \$$$$$$  \$$$$$$$\$$   \$$)");
    logo.emplace_back(R"(                                __                 __)");
    logo.emplace_back(R"(                               |  \               |  \)");
    logo.emplace_back(R"( ______ ____   ______   ______ | $$   __  ______ _| $$_)");
    logo.emplace_back(R"(|      \    \ |      \ /      \| $$  /  \/      |   $$ \)");
    logo.emplace_back(R"(| $$$$$$\$$$$\ \$$$$$$|  $$$$$$| $$_/  $|  $$$$$$\$$$$$$)");
    logo.emplace_back(R"(| $$ | $$ | $$/      $| $$   \$| $$   $$| $$    $$| $$ __)");
    logo.emplace_back(R"(| $$ | $$ | $|  $$$$$$| $$     | $$$$$$\| $$$$$$$$| $$|  \)");
    logo.emplace_back(R"(| $$ | $$ | $$\$$    $| $$     | $$  \$$\\$$     \ \$$  $$)");
    logo.emplace_back(R"( \$$  \$$  \$$ \$$$$$$$\$$      \$$   \$$ \$$$$$$$  \$$$$)");
    logo.emplace_back(R"(          __                       __           __)");
    logo.emplace_back(R"(         |  \                     |  \         |  \)");
    logo.emplace_back(R"(  _______ \$$______ ____  __    __| $$ ______ _| $$_    ______   ______)");
    logo.emplace_back(R"( /       |  |      \    \|  \  |  | $$|      |   $$ \  /      \ /      \)");
    logo.emplace_back(R"(|  $$$$$$| $| $$$$$$\$$$$| $$  | $| $$ \$$$$$$\$$$$$$ |  $$$$$$|  $$$$$$\)");
    logo.emplace_back(R"( \$$    \| $| $$ | $$ | $| $$  | $| $$/      $$| $$ __| $$  | $| $$   \$$)");
    logo.emplace_back(R"( _\$$$$$$| $| $$ | $$ | $| $$__/ $| $|  $$$$$$$| $$|  | $$__/ $| $$)");
    logo.emplace_back(R"(|       $| $| $$ | $$ | $$\$$    $| $$\$$    $$ \$$  $$\$$    $| $$)");
    logo.emplace_back(R"( \$$$$$$$ \$$\$$  \$$  \$$ \$$$$$$ \$$ \$$$$$$$  \$$$$  \$$$$$$ \$$      )");
    // clang-format on
    return logo;
}

void createplayer(string & playerName) {
    ofstream fout;
    string savefolder =
        SAVE_FOLDER_PREFIX; // create folder when it does not exist (first run)
    string foldername;
    filesystem::create_directory(SAVE_FOLDER_PREFIX);
    cout << "Enter player name:" << endl;
    getline(cin, playerName);
    foldername = SAVE_FOLDER_PREFIX + playerName;
    while ((filesystem::exists(foldername) || playerName.find(' ') != string::npos) ||
           playerName.empty()) { // check whether file already exists
        if (!playerName.empty()) {
            cout << "Invalid Playername. ";
            cout << "Playername should not contain spaces or cannot be the same as "
                    "existing ";
            cout << "playername" << endl << "Please enter a new player name: " << endl;
        }
        getline(cin, playerName);
        foldername = SAVE_FOLDER_PREFIX + playerName;
    }
    filesystem::create_directory(foldername); // create a empty folder for new save
}

void load_hsi(std::vector<float> hsi_history, const string & playerName) {
    std::string filesave =
        SAVE_FOLDER_PREFIX + playerName + "/hsi" + SAVE_FILE_EXTENSION_TXT;
    std::ifstream fin;
    fin.open(filesave.c_str());
    float hsi;
    while (fin >> hsi) {
        hsi_history.emplace_back(hsi);
    }
    fin.close();
}

void savestatus(unsigned int rounds_played, vector<Stock> stocks_list, float balance,
    const string & playerName) {
    string stocksave;
    ofstream fout;
    stocksave =
        SAVE_FOLDER_PREFIX + playerName + "/playerstatus" + SAVE_FILE_EXTENSION_TXT;
    fout.open(stocksave.c_str());
    fout << playerName << " " << rounds_played << " " << balance
         << endl; // saving basic info out of class inside playerstatus.save
    fout.close();
    for (unsigned long i = 0; i < stocks_list.size(); i++) {
        stocks_list[i].save(
            playerName, i); // save stock info inside class in seperate file
    }
}

void loadstatus(unsigned int & rounds_played, vector<Stock> & stocks_list,
    float & balance, string & playerName, vector<float> & hsi_history) {
    string stockload;
    string stockname;
    ifstream fin;
    vector<string> players;
    filesystem::create_directory(
        SAVE_FOLDER_PREFIX); // prevent error when no folder exists
    players = get_saves();   // generate a vector of name of folders
    if (players.empty()) {
        cout << "No player saves found, please create a new player." << endl;
        createplayer(playerName);
        return; // rejection of loading when no save files exist
    }
    cout << "Enter player name from the following:" << endl;
    printvector(players);
    while (std::find(players.begin(), players.end(), playerName) ==
           players.end()) { // reject incorrect input
        if (!playerName.empty()) {
            cout << "Player name does not exist, please enter a new name from the "
                    "following:"
                 << endl;
            printvector(players);
        }
        getline(cin, playerName);
    }
    stockload =
        SAVE_FOLDER_PREFIX + playerName + "/playerstatus" + SAVE_FILE_EXTENSION_TXT;
    fin.open(stockload.c_str());
    fin >> playerName >> rounds_played >> balance;
    fin.close(); // output basic info from playerstatus.save and return by reference
    load_hsi(hsi_history, playerName);
    for (unsigned long i = 0; i < initial_stock_count; i++) {
        stocks_list[i].load(
            playerName, i); // load stocks info to class in seperate files
    }
}

void delsave(string & mode) {
    string stockdel;
    string stockname;
    string inputname;
    string confirm;
    ifstream fin;
    vector<string> players;
    filesystem::create_directory(
        SAVE_FOLDER_PREFIX); // prevent error when no folder exists
    players = get_saves();   // generate a vector of name of folders
    if (players.empty()) {
        cout << "No player saves found, please enter 0 for new save or enter 3 to "
                "quit: ";
        std::cin >> mode;
        while (mode != "0" && mode != "3") {
            std::cout
                << "Invalid input. Please enter 0 for new save or enter 3 to quit: ";
            std::cin >> mode; // choose new file or load previous file
        }
        return;
    }
    cout << "Enter player name from the following:" << endl;
    printvector(players);
    while (std::find(players.begin(), players.end(), inputname) ==
           players.end()) { // reject incorrect input
        if (!inputname.empty()) {
            cout << "Player name does not exist, please enter a new name from the "
                    "following: "
                 << endl;
            printvector(players);
        }
        getline(cin, inputname);
    }

    cout << "WARNING! This action is irreversible and will delete all data associated "
            "with the player save."
         << endl;
    cout << "Player save " << inputname
         << " is going to be deleted, please enter Y to confirm" << endl;
    cin >> confirm;
    if (confirm == "Y" || confirm == "y") {
        stockdel = SAVE_FOLDER_PREFIX + inputname;
        std::filesystem::remove_all(stockdel);
        cout << "Player save " << inputname << " has been deleted." << endl;
    }
    else {
        cout << "The deletion has been cancelled." << endl;
    }

    // choosing mode again
    std::cout << "Please enter 0 for new save, enter 1 for loading old save,\n enter 2 "
                 "for deleting more save or enter 3 to quit: ";
    std::cin >> mode;
    while (mode != "0" && mode != "1" && mode != "2" && mode != "3") {
        std::cout << "Invalid input. Please enter 0 for new save, enter 1 for loading "
                     "old save, enter 2 for deleting more save or enter 3 to quit: ";
        std::cin >> mode; // choose new file or load previous file
    }
    if (mode == "2") {
        delsave(mode);
    }
}

vector<string> get_saves() {
    vector<string> saves;
    for (const auto & entry : std::filesystem::directory_iterator(SAVE_FOLDER_PREFIX)) {
        saves.emplace_back(entry.path().string().substr(SAVE_FOLDER_PREFIX.size()));
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
