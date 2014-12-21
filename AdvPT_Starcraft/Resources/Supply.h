#pragma once
#include <string>

#include "Resources.h"
#include "../Objects/Object.h"

class Supply : public Resources
{
private:
    unsigned int _supply = 0;

public:
    int produce(unsigned int time)
    {
        unsigned int tmp = _supply;
        _supply = 0;

        return tmp;
    }

    Resources::Type getType() { return Resources::Type::Supply; }

    bool extractSupply(Object building, std::string& error)
    {
        // check if object is building
        if (!building.isBuilding())
        {
            error += "Supply can be extract only from buildings";
            return false;
        }

        _supply += building.getSupply();

        return true;
    }
};

