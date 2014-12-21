#pragma once
#include <string>
#include <fstream>
#include <forward_list>

class Simulator
{
private:
    std::forward_list<std::string> _data;

public:

    Simulator(std::ifstream& file)
    {
        // get all data from file and omit empty lines
        std::string line;
        while (std::getline(file, line))
        {
            if (line != "")
                _data.push_front(line);
        }
    }

    bool run(std::string& result, std::string& error)
    {
        // todo
        return false;
    }
};

