#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "file_io.h"
using namespace std;


void createplayer(string &playername){
    ofstream fout;
    string savefolder = "saves";
    string foldername;
    filesystem::create_directory("saves");
    cout << "Enter player name:" << endl;
    cin >> playername;
    foldername = "saves/" + playername;
    while (filesystem::exists(foldername)){
        cout << "Player name already exists, please enter a new name:" << endl;
        cin >> playername;
        foldername = "saves/" + playername;
    }
    filesystem::create_directory(foldername);
}

void savestatus(unsigned int rounds_played,vector<Stock> stocks_list, float balance, string playername){
    string stocksave;
    ofstream fout;
    stocksave = "saves/" + playername + "/playerstatus.save";
    fout.open(stocksave.c_str());
    fout << playername << " " << rounds_played << " " << balance << endl;
    fout.close();
    for (unsigned long i = 0; i < stocks_list.size();i++){
        stocks_list[i].save(playername,i);
    }
}

void loadstatus(unsigned int &rounds_played,vector<Stock> &stocks_list, float &balance, string &playername){
    string stockload,stockname,inputname;
    ifstream fin;
    vector<string> players;
    players = get_saves();
    cout << "Enter player name from the following:" << endl;

    printvector(players);
    cin >> inputname;
    while (std::find(players.begin(), players.end(), inputname) == players.end()){
        cout << "Player name does not exist, please enter a new name from the following:" << endl;
        printvector(players);
        cin >> inputname;
    }

    stockload = "saves/" + inputname + "/playerstatus.save";
    playername = inputname;
    fin.open(stockload.c_str());
    fin >> playername >> rounds_played >> balance;
    fin.close();
    
    for (unsigned long i = 0; i < 20;i++){ //hard code 20 stocks
        stocks_list[i].load(inputname,i);
    }
}

vector<string> get_saves(){
    vector<string> saves;
    for (const auto & entry : std::filesystem::directory_iterator("saves")){
        saves.push_back(entry.path().string().substr(6));
    }
    return saves;
}

void printvector(vector<string> avector){
    for (unsigned long i = 0; i < avector.size();i++){
        cout << avector[i] << ", ";
    }
    cout << endl;
}