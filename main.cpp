#include <cstdlib> // srand()
#include <ctime> // time()
#include <iostream>
using namespace std;

const double trading_fees_percent = 0.01; // 1% trading fees
// trading fees are applied to both buying and selling
// see stock.cpp Stock::purchase and Stock::sell functions

int main(void){
    srand(time(NULL)); // srand should be called once in the program

    // todo: use a linked list to store all the stocks

    // todo: implement UI code
    // we don't want the game control be simply 'cin >> choice'
    // possible ideas:
    // 1. keyboard hotkeys, e.g. press B to buy, S to sell, etc.
    // 2. arrow keys selection (like a menu)
    // we will discuss the details in the next meeting

    // todo: intro game splash screen using ascii code or something
    
    cout << "Hello world!" << endl;
    return 0;
}
