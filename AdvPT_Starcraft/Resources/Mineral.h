#pragma once
#include <stack>

#include "../Objects/Object.h"
#include "Resources.h"

class Mineral : public Resources
{
private:
    unsigned int remainTime = 0;
    const static int multiplier;
    const static int secondsPerMineral;

    std::stack<Object> _nearbyUnits; // todo : chcia³eœ przechowywaæ referencjê, ale to nie da rady

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

    Resources::Type getType() { return Resources::Mineral; }

    /*
        Add ojbect of Unit type.
        Returns error if any.
    */
    std::string pushUnit(Object pushUnit)
    {
        // check if unit
        if (pushUnit.getType() != Types::ObjectType::Unit)
            return "Wrong object type: " + Types::objectTypeStrings[pushUnit.getType()];

        // add unit
        _nearbyUnits.push(pushUnit);

        // return no errors
        return "";
    }

    /*
        Pop Unit from list if it is posible.
        Returns error if any.
    */
    // TODO : fix return and args
    std::string popUnit(Object& popUnit)
    {
        // check if there any nearby Units
        if (_nearbyUnits.size() == 0)
            return "No Units nearby mineral";

        // get last Unit and remove it
        popUnit = _nearbyUnits.top();
        _nearbyUnits.pop();

        // return no errors
        return "";
    }
};

const int Mineral::multiplier = 100;
const int Mineral::secondsPerMineral = 70;