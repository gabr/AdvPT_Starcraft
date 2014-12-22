#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <memory>

#include "Objects\Object.h"

#include "Resources\Minerals.h"
#include "Resources\Vespene.h"
#include "Resources\Supply.h"

class Simulator
{
private:
    unsigned int _mineralsCounter = 0;
    unsigned int _vespeneCounter = 0;
    unsigned int _supplyCounter = 0;

    std::unique_ptr<Minerals> _minerals;
    std::unique_ptr<Vespene> _vespene;
    std::unique_ptr<Supply> _supply;

    unsigned int _time = 0;
    static const unsigned int timeLimit;

    std::list<std::string> _data;

    std::list<Object> _objects;
    std::list<Object> _objectsInProgress;

    void clearState()
    {
        _mineralsCounter = _vespeneCounter = _supplyCounter = _time = 0;

        _objects.clear();
        _objectsInProgress.clear();
    }

    /*
        Set simulation init state:

        50 minerals
        2 Vespenes

        6 Probes
        1 main building - nexus
    */
    bool initState(std::string& error)
    {
        clearState();

        bool no_error = true;

        // create resources
        _minerals.reset(new Minerals());
        _vespene.reset(new Vespene(2));
        _supply.reset(new Supply());

        _mineralsCounter = 50;

        // create objects
        for (int i = 0; i < 6; i++) // probes
            _objects.push_back(Object::createObject(Types::Unit, Types::Probe));

        // nexus
        _objects.push_back(Object::createObject(Types::Building, Types::Nexus));


        // move all probes to Minerals
        _minerals.get()->assignProbe(6);

        // push nexus to Supply and return status
        no_error = _supply.get()->extractSupply(_objects.back(), error);
        _supplyCounter = _supply.get()->produce(1);

        return no_error;
    }

    void printMsg(std::string action, std::string name, unsigned int& minerals, unsigned int& vespene)
    {
        std::cout << " " << _time << "\t" << "workers" << "\t\t"
            << "minerals:" << minerals << ",vespene:" << vespene << std::endl;
        std::cout << " " << _time << "\t" << action << "\t" << name << std::endl;

        minerals = vespene = 0;
    }

public:

    Simulator(std::ifstream& file)
    {
        // get all data from file and omit empty lines
        std::string line;
        while (std::getline(file, line))
        {
            if (line != "")
                _data.push_back(line);
        }
    }

    bool run(std::string& error)
    {
        // start from init state
        if (!initState(error))
            return false;

        // simulation
        unsigned int tmp = 0;
        unsigned int minerals = 0;
        unsigned int vespene = 0;
        bool action = false;

        auto currentData = std::begin(_data);
        Object& currentObject = Object::createObject(Types::ObjectType::Unknown, 0);

        while (_time <= timeLimit)
        {
            // check if any build finished
            for (auto o = std::begin(_objectsInProgress); o != std::end(_objectsInProgress);)
            {
                if (o->status(_time)) // object build finished
                {
                    _objects.push_back(*o);

                    if (o->isUnit(Types::Probe))
                        _minerals.get()->assignProbe(1);

                    if (o->isBuilding(Types::Assimilator))
                        _vespene.get()->assignAssimilator(*o, error);

                    if (o->isBuilding())
                        _supply.get()->extractSupply(*o, error);

                    // if there any empty slots near Vespenes then get Probes from minerals
                    unsigned int freeProbesSlots = _vespene.get()->freeProbesSlots();
                    if (freeProbesSlots && _minerals.get()->getNumberOfProbes() > freeProbesSlots)
                    {
                        _minerals.get()->removeProbes(freeProbesSlots, error);
                        _vespene.get()->assignProbe(freeProbesSlots, error);
                    }

                    // print message
                    printMsg("build-end", o->toString(), minerals, vespene);

                    // remove object from list
                    o = _objectsInProgress.erase(o);
                }
                else
                {
                    ++o;
                }
            }

            if (currentData != std::end(_data))
            {
                currentObject = Object::createObject(*currentData);

                // if unknown then data in file was corrupted
                if (currentObject.getType() == Types::ObjectType::Unknown)
                {
                    error += "Wrong data in file. Can not create Object from: " + *currentData;
                    return false;
                }

                // try to init current object
                if (currentObject.init(_time, _mineralsCounter, _vespeneCounter, _supplyCounter))
                {
                    // if initialization succeeded  push object to the In Progress list and set iterator to the next data
                    _objectsInProgress.push_back(currentObject);
                    ++currentData;

                    // print message
                    printMsg("build-start", currentObject.toString(), minerals, vespene);
                }
            }

            if (!(currentData != std::end(_data) || _objectsInProgress.size() != 0))
            {
                break; // end simulation
            }
            else
            {

                // calculate resources
                tmp = _minerals.get()->produce(1);
                _mineralsCounter += tmp; minerals += tmp;

                tmp = _vespene.get()->produce(1);
                _vespeneCounter += tmp; vespene += tmp;

                _supplyCounter += _supply.get()->produce(1);

                // each iteratino increase time
                ++_time;
            }
        }

        // print summary
        std::cout << " " << _time << "\t" << "resources" << "\t"
            << "minerals:" << _mineralsCounter
            << ",vespene:" << _vespeneCounter
            << ",usedSupply:" << _supply.get()->getTotalSupply() - _supplyCounter
            << ",availableSupply:" << _supply.get()->getTotalSupply()
            << std::endl;

        return true;
    }
};

const unsigned int Simulator::timeLimit = 1000; // 1000 [s]