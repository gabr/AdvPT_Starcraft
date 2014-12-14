#pragma once
#include <string>
#include <algorithm>
#include <forward_list>

#include "Types.h"
#include "Resources.h"
#include "XmlReader.h"

class Object
{
protected:

    // requirements
    Resources::Data _requirements;

    // object informations
    std::string _name = "";

    Types::ObjectType _type = Types::Unknown;
    int _specificType = -1; // UnitType or BuildingType - depends on _type

    unsigned int _startTime = 0;

    // private constructor
    Object(Types::ObjectType objectType, int specificType) : _type(objectType), _specificType(specificType)
    {
        if (objectType == Types::Unit)
        {
            _name = Types::unitTypeStrings[specificType];
        }

        else if (objectType == Types::Building)
        {
            _name = Types::buildingTypeStrings[specificType];
        }
    }

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

    static Object& createObject(const std::string objectName)
    {
        // try to find object in Units list
        for (int i = 0; i < Types::_numberOfUnitsTypes; i++)
            if (objectName == Types::unitTypeStrings[i])
                return Object(Types::Unit, i);

        // try to find object in Buildings list
        for (int i = 0; i < Types::_numberOfBuildingsTypes; i++)
            if (objectName == Types::buildingTypeStrings[i])
                return Object(Types::Building, i);

        // return Unknown object type
        return Object(Types::Unknown, -1);
    }

    bool init() {};
    std::string toString() { return _name; }
};