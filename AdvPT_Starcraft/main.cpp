#include <iostream>

#include "CsvReader.h"

int main(int argc, char* argv[])
{
    std::cout << "Program: " << argv[0] << std::endl;
    std::cout << CsvReader::updateUnits() << std::endl;
    std::cout << CsvReader::updateBuildings() << std::endl;

    return 0;
}