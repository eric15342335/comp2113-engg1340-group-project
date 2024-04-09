#ifndef NAMES_H
#define NAMES_H

#include <string>
using namespace std;

// the index map to the names, e.g. category = 0 is tech
// we will decide what category we will include later
const unsigned int category_list_size = 5;
// we use extern since we will define the array in names.cpp
// we don't want to define the array in names.h since it's not a good practice
// and will cause multiple definition error
extern string category_list[category_list_size];

string generate_name(unsigned int category);

#endif
