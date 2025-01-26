#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
    ULListStr list;
    std::string s = "hello";
    list.push_back(s);
    std::cout << list.get(0) << std::endl;
    list.set(0, "goodbye");
    std::cout << list.get(0) << std::endl;
    list.push_back("world");
    std::cout << list.get(1) << std::endl;
    return 0;
}
