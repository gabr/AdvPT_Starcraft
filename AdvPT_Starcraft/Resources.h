#pragma once
#include <forward_list>

#include "Types.h"

class Resources
{
public:
    virtual int produce() = 0;
    virtual ~Resources() {}

    static struct Data
    {
        unsigned int mineral = 0;
        unsigned int vespen = 0;
        unsigned int supply = 0;
        unsigned int time = 0;
        std::forward_list<Types::BuildingType> required_buildings;
    };
};

