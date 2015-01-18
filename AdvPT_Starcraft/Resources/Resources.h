#pragma once
#include <forward_list>

class Resources
{
public:

    static struct Data
    {
        unsigned int mineral = 0;
        unsigned int vespen = 0;
        unsigned int supply = 0;
        unsigned int time = 0;
        std::forward_list<std::string> required_buildings;
    };

    static enum Type { Unknown, Minerals, Vespene, Supply };

    virtual unsigned int produce(unsigned int time) = 0;
    virtual Resources::Type getType() = 0;

    virtual ~Resources() {}
};

