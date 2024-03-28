// code related to randomness
#include <cstdlib>
using namespace std;

unsigned int random_integer(unsigned int max_integer) {
    // Return a random integer from 0 to max - 1
    return rand() % max_integer;
}
