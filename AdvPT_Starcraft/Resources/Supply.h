#pragma once
#include <string>

#include "../Types.h"
#include "Resources.h"
#include "../Objects/Object.h"

class Supply : public Resources
{
private:
    unsigned int _tmp = 0;
    unsigned int _supply = 0;

public:
    unsigned int produce(unsigned int time)
    {
        unsigned int tmp = _tmp;
        _tmp = 0;
        return tmp;
    }

    Resources::Type getType() { return Resources::Type::Supply; }

    bool extractSupply(Object building, std::string& error)
    {
        // check if object is building
        if (!building.getType() == Types::ObjectType::Building)
        {
            error += "Supply can be extract only from buildings";
            return false;
        }

        _supply += _tmp = building.getSupply();

        return true;
    }

    unsigned int getTotalSupply() { return _supply; }
};

