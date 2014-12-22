#pragma once
#include <stack>

#include "../Objects/Object.h"
#include "Resources.h"

class Minerals : public Resources
{
private:
    const static int multiplier;
    const static int secondsPerMineral;

    unsigned int _numberOfMinerals;
    unsigned int _remainTime = 0;
    unsigned int _probesCount = 0;
public:

    Minerals(unsigned int numberOfMinerals) : _numberOfMinerals(numberOfMinerals) {}

    int produce(unsigned int time)
    {
        int tmp = (time * multiplier) + _remainTime;;

        // counting number of minerals to return
        int minerals = tmp / secondsPerMineral;
        minerals *= _probesCount;
        
        // store remainig time
        _remainTime = tmp % secondsPerMineral;

        return minerals;
    }

    Resources::Type getType() { return Resources::Minerals; }

    unsigned int getNumberOfProbes() { return _probesCount; }
    unsigned int getNumberOfMinerals() { return _numberOfMinerals; }

    /*
        Add Probe to Minerals.
        Checks Unit type and returns false if it is wrong
            - in that case puts message in error reference.
    */
   bool assignProbe(const Object probe, std::string& error)
    {
        // check if Unit and Probe
       if (!probe.isUnit(Types::UnitType::Probe))
       {
           error += "Wrong object type, only Probes can be assign.";
           return false;
       }

        // add unit
        ++_probesCount;

        // return no errors
        return true;
    }

    /*
        Remove Probes from Minerals.
    */
    bool removeProbes(unsigned int numberOfProbessToRemove, std::string& error)
    {
        // check if there any nearby Units
        if (_probesCount == 0)
        {
            error += "No assigned Probes.";
            return false;
        }

        if (numberOfProbessToRemove > _probesCount)
        {
            error += "Number of Probes to remove is greater then Probes assigned to Minerals.";
            return false;
        }

        // get last Unit and remove it
        _probesCount -= numberOfProbessToRemove;

        // return no errors
        return true;
    }
};

const int Minerals::multiplier = 100;
const int Minerals::secondsPerMineral = 70;