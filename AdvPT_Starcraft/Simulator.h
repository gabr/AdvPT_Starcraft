#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <forward_list>
#include <memory>

#include "Objects\Object.h"

#include "Resources\Minerals.h"
#include "Resources\Vespene.h"
#include "Resources\Supply.h"

class Simulator
{
private:
    unsigned int _mineralsCounter = 0;
    unsigned int _vespenesCounter = 0;
    unsigned int _supplyCounter = 0;

    unsigned int _time = 0;
    static const unsigned int timeLimit;

    std::forward_list<std::string> _data;

    std::forward_list<Object> _objects;
    std::forward_list<Object> _objectsInProgress;

    /*
        [0] - Minerals
        [1] - Vespene
        [2] - Supply
    */
    std::vector<std::unique_ptr<Resources>> _resources;

    /*
        50 minerals
        2 Vespenes

        6 Probes
        1 main building - nexus
    */
    bool initState(std::string& error)
    {
        bool no_error = true;

        // create resources
        _resources.push_back(std::unique_ptr<Resources>(new Minerals(50)));
        _resources.push_back(std::unique_ptr<Resources>(new Vespene(2)));
        _resources.push_back(std::unique_ptr<Resources>(new Supply()));

        // create objects
        for (int i = 0; i < 6; i++) // probes
            _objects.push_front(Object::createObject(Types::Unit, Types::Probe));

        // nexus
        _objects.push_front(Object::createObject(Types::Building, Types::Nexus));


        // move all probes to Minerals
        Minerals m = *dynamic_cast<Minerals*>(_resources[0].get());

        for (auto o : _objects)
        if (o.isUnit(Types::UnitType::Probe))
            no_error = no_error && m.assignProbe(o, error);

        // push nexus to Supply
        no_error = no_error && dynamic_cast<Supply*>(_resources[2].get())->extractSupply(_objects.front(), error);

        return no_error;
    }

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
        // start from init state
        if (!initState(error))
            return false;


        return false;
    }
};

const unsigned int Simulator::timeLimit = 1000; // 1000 [s]