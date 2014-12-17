#pragma once
#include <stack>

#include "Object.h"
#include "Resources.h"

class Mineral : public Resources
{
private:
    unsigned int remainTime = 0;
    const static int multiplier;
    const static int secondsPerMineral;

    std::stack<Object&> _nearbyUnits;

public:

    int produce(unsigned int time)
    {
        int tmp = (time * multiplier) + remainTime;;

        // counting number of minerals to return
        int minerals = tmp / secondsPerMineral;
        minerals *= _nearbyUnits.size();
        
        // store remainig time
        remainTime += tmp % secondsPerMineral;

        return minerals;
    }
};

const int Mineral::multiplier = 100;
const int Mineral::secondsPerMineral = 70;