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
    ofstream fout;
    string stocksave;
    for (int i = 0; i < stocks_list.size();i++){
    }
}

int main(){
    string playername;
    createplayer(playername);
    return 0;
}