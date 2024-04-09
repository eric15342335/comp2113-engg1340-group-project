#ifndef NAMES_H
#define NAMES_H

#include <string>
#include <vector>
using namespace std;

// the index map to the names, e.g. category = 0 is tech
// we will decide what category we will include later
const int category_list_size = 19;
// we use extern since we will define the array in names.cpp
// we don't want to define the array in names.h since it's not a good practice
// and will cause multiple definition error
extern string category_list[category_list_size];

vector<string> generate_name(unsigned int category, int num);


#endif
