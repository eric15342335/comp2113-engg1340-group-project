#ifndef FILE_IO_H
#define FILE_IO_H
#include "stock.h"

//linker command failed with exit code 1 (use -v to see invocation)
//https://stackoverflow.com/questions/12573816/linker-command-failed-with-exit-code-1-use-v-to-see-invocation

void createplayer(std::string &playername);
void savestatus(int rounds_played,std::vector<Stock> stocks_list, float balance,std::string playername);
void loadstatus(int rounds_played,std::vector<Stock> stocks_list, float balance,std::string playername);
#endif