#pragma once
#include "Resources.h"

class Supply : public Resources
{
public:
    int produce(unsigned int time)
    {
        // TODO
        return 0;
    }

    Resources::Type getType() { return Resources::Supply; }
};

