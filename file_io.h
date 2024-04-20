#ifndef FILE_IO_H
#define FILE_IO_H
#include <vector>
#include <string>
#include "stock.h"

void createplayer(std::string &playername);
void savestatus(int rounds_played,std::vector<Stock> stocks_list, float balance,std::string playername);
#endif