#pragma once
#include <string>
#include <algorithm>
#include <forward_list>

#include "../Resources/Resources.h"
#include "../CsvReader.h"

enum ObjectType { Unknown, Unit, Building };
const std::string objectTypeStrings[3] = { "unknown", "unit", "building" };

class Object
{
protected:

    // object informations
    std::string _name = "";

    ObjectType _type = Unknown;

    unsigned int _startTime = 0;
    Resources::Data _requirements;

    // private constructor
    Object(std::string objectName, ObjectType objectType) : _name(objectName), _type(objectType)
    {
        _requirements = CsvReader::getRequirements(objectType, objectName);
    }

    // check requirements and decrement global 
    bool checkRequirements(unsigned int& globalMineral, unsigned int &globalVespen, unsigned int &globalSupply)
    {
        if (_type == Unknown)
            return false;

        if (_requirements.mineral <= globalMineral
            && _requirements.vespen <= globalVespen
            && (_type == Building || _requirements.supply <= globalSupply)) // if building no supply required
        {
            globalMineral -= _requirements.mineral;
            globalVespen -= _requirements.vespen;

            // only units drain supply
            if (_type == Unit)
                globalSupply -= _requirements.supply;
            return true;
        }

        return false;
    }

public:

    static Object createObject(const ObjectType type, const std::string name)
    {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        // return object
        return Object(name, type);
    }

    // initialize object creatino
    bool init(const unsigned int currentTime, unsigned int& globalMineral, unsigned int &globalVespen, unsigned int &globalSupply)
    {
        // check requirements and decrement values if creating object is possible
        if (!checkRequirements(globalMineral, globalVespen, globalSupply))
            return false;

        // starting object creation is possible
        // set _startTime to currentTime and return success
        _startTime = currentTime;
        return true;
    }

    // returns object status: true - created; false - not created or in progress
    bool status(const unsigned int currentTime) const 
    {
        if (_startTime == -1) return false; // not created
        if (currentTime >= _startTime + _requirements.time) // created
            return true;
        else                                                // in progress
            return false;
    }

    ObjectType getType() const { return _type; }
    unsigned int getSupply() const 
    {
        if (_type == Building)
            return _requirements.supply;

        return 0;
    }

    bool compareName(std::string name)
    {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        return _name == name;
    }

    std::string toString() const { return _name; }
};