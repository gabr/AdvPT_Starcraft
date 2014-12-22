#pragma once
#include <stack>

#include "Resources.h"

class Minerals : public Resources
{
private:
    const static int multiplier;
    const static int secondsPerMineral;

    unsigned int _remainTime = 0;
    unsigned int _probesCount = 0;
    unsigned int _totalMinerals = 0;

public:

    unsigned int produce(unsigned int time)
    {
        _remainTime += secondsPerMineral * time;

        unsigned int minerals = _remainTime / multiplier;
        _remainTime -= minerals * multiplier;

        _totalMinerals += minerals * _probesCount;
        return minerals * _probesCount;
    }

    Resources::Type getType() { return Resources::Minerals; }

    unsigned int getNumberOfProbes() { return _probesCount; }

    /*
        Add Probe to Minerals.
        Checks Unit type and returns false if it is wrong
            - in that case puts message in error reference.
    */
    bool assignProbe(const unsigned int numberOfProbessToAssign)
    {
        // add unit
        _probesCount += numberOfProbessToAssign;

        // return no errors
        return true;
    }

    /*
        Remove Probes from Minerals.
    */
    bool removeProbes(const unsigned int numberOfProbessToRemove, std::string& error)
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

    unsigned int getTotalMinerals() { return _totalMinerals; }
};

const int Minerals::multiplier = 100;
const int Minerals::secondsPerMineral = 70;