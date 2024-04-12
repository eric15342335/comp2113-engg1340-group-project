#include "VariadicTable.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>

int main() {
    VariadicTable<std::string, double, int, std::string> vt({"Name", "Weight", "Age", "Brother"});
    vt.addRow("Fred", 193.4, 35, "Sam");
    vt.addRow("Fred", 193.4, 35, "Sam");
    std::stringstream ss;
    vt.print(ss);
    std::string line;
    int newlineCount = 0;
    while (std::getline(ss, line)) {
        newlineCount++;
    }
    std::cout << ss.str() << std::endl;
    std::cout << "Number of newlines: " << newlineCount << std::endl;
    return 0;
}