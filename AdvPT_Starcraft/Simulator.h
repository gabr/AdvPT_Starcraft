#pragma once
#include <string>
#include <fstream>
#include <forward_list>

#include "Objects\Object.h"
#include "Resources\Resources.h"

class Simulator
{
private:
    unsigned int _minerals = 0;
    unsigned int _vespenes = 0;
    unsigned int _supply = 0;

    unsigned int _time = 0;
    static const unsigned int timeLimit;

    std::forward_list<Object> _objects;
    std::forward_list<std::string> _data;
    std::forward_list<Resources> _resources;

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

const unsigned int Simulator::timeLimit = 1000; // 1000 [s]