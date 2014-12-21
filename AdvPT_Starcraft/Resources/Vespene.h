#pragma once
#include <stack>

#include "Resources.h"

class Vespene : public Resources
{
private:
    unsigned int remainTime = 0;
    const static int multiplier;
    const static int secondsPerVespen;

public:
    int produce(unsigned int time)
    {
        // TODO
        return 0;
    }

    Resources::Type getType() { return Resources::Vespene; }
};

const int Vespene::multiplier = 100;
const int Vespene::secondsPerVespen = 35;