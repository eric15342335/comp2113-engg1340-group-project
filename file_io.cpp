#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>
#include "file_io.h"
using namespace std;
 
void createplayer(string &playername){
    ofstream fout;
    string savefolder = "saves";
    string foldername;
    std::__fs::filesystem::create_directory("saves");
    cout << "Enter player name:" << endl;
    cin >> playername;
    foldername = "saves/" + playername;
    while (std::__fs::filesystem::exists(foldername)){
        cout << "Player name already exists, please enter a new name:" << endl;
        cin >> playername;
        foldername = "saves/" + playername;
    }
    std::__fs::filesystem::create_directory(foldername);
}

void savestatus(int rounds_played,vector<Stock> stocks_list, float balance, string playername){
    string stocksave;
    ofstream fout;
    stocksave = "saves/" + playername + "/playerstatus.save";
    fout.open(stocksave);
    fout << playername << " " << rounds_played << " " << balance << endl;
    fout.close();
    for (unsigned long i = 0; i < stocks_list.size();i++){
        stocks_list[i].save(playername,i);
    }
}

void loadstatus(int rounds_played,vector<Stock> stocks_list, float balance, string playername){
    string stocksave,stockname;
    ifstream fin;
    stocksave = "saves/" + playername + "/playerstatus.save";
    fin.open(stocksave);
    fin >> playername >> rounds_played >> balance;
    fin.close();
    
    for (unsigned long i = 0; i < 20;i++){ //hard code 20 stocks
        stocks_list[i].load(playername,i);
    }
}