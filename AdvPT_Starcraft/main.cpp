#include <iostream>

#include "CsvReader.h"

int main(int argc, char* argv[])
{
    std::cout << argv[0] << std::endl;
    std::cout << CsvReader::updateUnits() << std::endl;

    return 0;
}