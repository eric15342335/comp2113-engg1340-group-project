// stock name generation algorithm
#include "names.h"
using namespace std;

// the index map to the names, e.g. category = 0 is tech
string category_list[category_list_size] = {"tech", "finance", "healthcare", "consumer", "energy"};

string generate_name(unsigned int category) {
    // Generate a name based on the category
    switch (category) {
    case 0:
        //
    case 1:
        //
    case 2:
        //
    case 3:
        //
    case 4:
        //
    // etc.
    default:
        return "Unknown";
    }
}
