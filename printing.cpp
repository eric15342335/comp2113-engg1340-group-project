#include "printing.h"
#include <iostream>
using namespace std;

void replace_screen_line(vector<string> & contents, string new_content, int line) {
    // Given a vector of strings, replace the line-th line with new_content
    // And then print the vector to cout
    // first clean the screen
    for (int i = 0; i < contents.size(); i++){
        cout << "\033[2J\033[1;1H"; // clear screen
    }
    contents[line] = new_content;
    print_vector(contents);
    return;
}


void print_vector(vector<string> contents) {
    // Print the vector to cout
    for (int i = 0; i < contents.size(); i++) {
        cout << contents[i] << endl;
    }
    return;
}
