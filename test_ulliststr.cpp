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
    return 0;
}
