#pragma once
#include "Object.h"

class Unit :
    public Object
{
private:
    UnitType _type;

public:
    Unit(std::string unitName, Requirements &requirements)
    {
        this->_requirements = requirements;

        // resolve unit type
        for (unsigned int i = 0; i < _numberOfUnitsTypes; i++)
        if (unitName == unitTypeStrings[i])
        {
            this->_type = static_cast<UnitType>(i);
            return;
        }
    }
    virtual ~Unit() {}

    bool init()
    {

    }
};

