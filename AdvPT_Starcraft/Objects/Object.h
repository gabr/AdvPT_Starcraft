#pragma once
#include <string>
#include <algorithm>
#include <forward_list>

#include "../Types.h"
#include "../Resources/Resources.h"
#include "../CsvReader.h"

class Object
{
protected:

    // object informations
    std::string _name = "";

    Types::ObjectType _type = Types::Unknown;
    int _specificType = -1; // UnitType or BuildingType - depends on _type

    unsigned int _startTime = 0;
    Resources::Data _requirements;

    // private constructor
    Object(std::string objectName, Types::ObjectType objectType, int specificType) : _name(objectName), _type(objectType), _specificType(specificType)
    {
        if (objectType == Types::Unit)
            _requirements = CsvReader::getRequirements(static_cast<Types::UnitType>(_specificType));

        else if (objectType == Types::Building)
            _requirements = CsvReader::getRequirements(static_cast<Types::BuildingType>(_specificType));
    }

    // check requirements and decrement global 
    bool checkRequirements(unsigned int& globalMineral, unsigned int &globalVespen, unsigned int &globalSupply)
    {
        if (_requirements.mineral <= globalMineral
            && _requirements.vespen <= globalVespen
            && (_type == Types::Building || _requirements.supply <= globalSupply)) // if building no supply required
        {
            globalMineral -= _requirements.mineral;
            globalVespen -= _requirements.vespen;

            // only units drain supply
            if (_type == Types::Unit)
                globalSupply -= _requirements.supply;
            return true;
        }

        return false;
    }

public:

    static Object createObject(const std::string objectName)
    {
        // try to find object in Units list
        for (int i = 0; i < Types::numberOfUnitsTypes; i++)
            if (objectName == Types::unitTypeStrings[i])
                return Object(objectName, Types::Unit, i);

        // try to find object in Buildings list
        for (int i = 0; i < Types::numberOfBuildingsTypes; i++)
            if (objectName == Types::buildingTypeStrings[i])
                return Object(objectName, Types::Building, i);

        // return Unknown object type
        return Object(objectName, Types::Unknown, 0);
    }

    static Object createObject(const Types::ObjectType type, const int specificType)
    {
        if (type == 0 || specificType == 0) // unknown object
            return Object(Types::objectTypeStrings[0], Types::ObjectType::Unknown, 0);

        std::string name = type == Types::Unit ? Types::unitTypeStrings[specificType] : Types::buildingTypeStrings[specificType];
        return Object(name, type, specificType);
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

    bool isUnit() const { return _type == Types::ObjectType::Unit; }
    bool isBuilding() const { return _type == Types::ObjectType::Building; }
    bool isUnknown() const { return _type == Types::ObjectType::Unknown; }

    bool isUnit(const Types::UnitType unitType) const
    {
        if (!isUnit()) return false;
        if (static_cast<Types::UnitType>(_specificType) != unitType) return false;

        return true;
    }

    bool isBuilding(const Types::BuildingType buildingType) const
    {
        if (!isBuilding()) return false;
        if (static_cast<Types::BuildingType>(_specificType) != buildingType) return false;

        return true;
    }

    Types::ObjectType getType() const { return _type; }
    int getSpecificType() const { return _specificType; }
    unsigned int getSupply() const 
    {
        if (isBuilding())
            return _requirements.supply;

        return 0;
    }

    std::string toString() const { return _name; }
};