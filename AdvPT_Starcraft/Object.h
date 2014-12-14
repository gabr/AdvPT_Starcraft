#pragma once
#include <string>
#include <algorithm>
#include <forward_list>

#include "Types.h"
#include "Resources.h"

class Object
{
protected:

    // requirements
    Resources::Data _requirements;

    // object informations
    std::string _name = "";
    Types::ObjectType _type = Types::Unknown;
    unsigned int _startTime = 0;

    // private constructor
    Object(Types::ObjectType objectType) : _type(objectType) {};

    // check requirements and decrement global 
    bool checkRequirements(unsigned int& globalMineral, unsigned int &globalVespen, unsigned int &globalSupply)
    {
        if (_requirements.mineral <= globalMineral
            && _requirements.vespen <= globalVespen
            && _requirements.supply <= globalSupply)
        {
            globalMineral -= _requirements.mineral;
            globalVespen -= _requirements.vespen;
            globalSupply -= _requirements.supply;
            return true;
        }

        return false;
    }

public:
    virtual bool init() = 0; // <--- todo
    std::string toString() { return _name; }
};