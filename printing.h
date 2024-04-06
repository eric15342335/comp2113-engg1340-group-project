#ifndef PRINTING_H
#define PRINTING_H

#include <vector>
#include <string>
using namespace std;

void replace_screen_line(vector<string> & contents, string new_content, int line);
void print_vector(vector<string> contents);

#endif
