#ifndef NAMES_H
#define NAMES_H

#include <string>
using namespace std;

// the index map to the names, e.g. category = 0 is tech
// we will decide what category we will include later
const unsigned int category_list_size = 5;
string category_list[category_list_size] = {"tech", "finance", "healthcare", "consumer", "energy"};

string generate_name(unsigned int category);

#endif
