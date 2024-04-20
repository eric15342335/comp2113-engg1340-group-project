#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include "file_io.h"
using namespace std;
 
void createplayer(string &playername){
    ofstream fout;
    string savefolder = "saves";
    string foldername;
    mkdir(savefolder.c_str(), 0777);
    cout << "Enter player name:" << endl;
    cin >> playername;
    foldername = "saves/" + playername;
    while (mkdir(foldername.c_str(), 0777) == -1)
    {
        cout << "Error : Player already existed. Please enter a different player name" << endl;
        cin >> playername;
        foldername = "saves/" + playername;
    }
    fout.open("saves/Savenames.abc",ios::app);
    fout << playername << endl;
    fout.close();
    cout << "Player created" << endl;
}

void savestatus(int rounds_played,vector<Stock> stocks_list, float balance, string playername){
    string stocksave;
    ofstream fout;
    stocksave = "saves/" + playername + "/playerstatus.save";
    fout.open(stocksave);
    fout << playername << " " << rounds_played << " " << balance << endl;
    fout.close();
    for (unsigned long i = 0; i < stocks_list.size();i++){
        stocks_list[i].save(playername);
    }
}