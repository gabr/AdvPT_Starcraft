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
    unsigned int _totalVespene = 0;

public:

    Vespene(unsigned int numberOfVespenes) : _numberOfVespenes(numberOfVespenes) {}

    unsigned int produce(unsigned int time)
    {
        _remainTime += secondsPerVespen * time;

        unsigned int vespen = _remainTime / multiplier;
        _remainTime -= vespen * multiplier;

        unsigned int result = vespen * _numberOfAssimilators * _probesCount;
        _totalVespene += result;

        return result;
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
        if (!assimilator.compareName("assimilator"))
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
    bool assignProbe(const unsigned int numberOfProbessToAssign, std::string& error)
    {
        if (_probesCount + numberOfProbessToAssign > probesPerVespene * _numberOfAssimilators)
        {
            error += "You tried to add to much Probes!";
            return false;
        }

        // add unit
        _probesCount += numberOfProbessToAssign;

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

    unsigned int freeProbesSlots()
    {
        return probesPerVespene * _numberOfAssimilators - _probesCount;
    }

    unsigned int getTotalVespene() { return _totalVespene; }
};

const int Vespene::multiplier = 100;
const int Vespene::secondsPerVespen = 35;
const unsigned int Vespene::probesPerVespene = 3;