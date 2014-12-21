#pragma once
#include <stack>

#include "Resources.h"
#include "..\Objects\Object.h"

class Vespene : public Resources
{
private:
    unsigned int remainTime = 0;
    const static int multiplier;
    const static int secondsPerVespen;
    const static unsigned int probesPerVespene;

    unsigned int _numberOfVespenes = 0;
    unsigned int _numberOfAssimilators = 0;
    unsigned int _remainTime = 0;
    unsigned int _probesCount = 0;

public:

    Vespene(unsigned int numberOfVespenes) : _numberOfVespenes(numberOfVespenes) {}

    int produce(unsigned int time)
    {
        int tmp = (time * multiplier) + _remainTime;;

        // counting number of minerals to return
        int minerals = tmp / secondsPerVespen;
        minerals *= _probesCount;

        // store remainig time
        _remainTime = tmp % secondsPerVespen;

        return minerals;
    }

    Resources::Type getType() { return Resources::Vespene; }

    unsigned int getNumberOfProbes() { return _probesCount; }
    unsigned int getNumberOfAssimilators() { return _numberOfAssimilators; }
    unsigned int getNumberOfVespenes() { return _numberOfVespenes; }

    bool assignAssimilator(Object assimilator, std::string& error)
    {
        if (_numberOfAssimilators == _numberOfVespenes)
        {
            error += "All Vespenes has Assimilators";
            return false;
        }

        // check type
        if (!assimilator.isBuilding(Types::BuildingType::Assimilator))
        {
            error += "Wrong object type, olny Assimilators can be assign.";
            return false;
        }

        // add assimilator
        ++_numberOfAssimilators;

        // no errors
        return true;
    }

    /*
    Add Probe to Vespenes.
    Checks Unit type and returns false if it is wrong
    - in that case puts message in error reference.
    */
    bool assignProbe(Object probe, std::string& error)
    {
        if (_probesCount == probesPerVespene * _numberOfAssimilators)
        {
            error += "All assigned Assimilators has already max number of Probes.";
            return false;
        }

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
    Remove Probes from Vespenes.
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
            error += "Number of Probes to remove is greater then Probes assigned to Vespenes.";
            return false;
        }

        // get last Unit and remove it
        _probesCount -= numberOfProbessToRemove;

        // return no errors
        return true;
    }
};

const int Vespene::multiplier = 100;
const int Vespene::secondsPerVespen = 35;
const unsigned int Vespene::probesPerVespene = 3;