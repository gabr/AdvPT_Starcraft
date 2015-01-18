#pragma once
#include <string>

namespace Types
{
    enum ObjectType { Unknown, Unit, Building };
    const std::string objectTypeStrings[3] = { "unknown", "unit", "building" };
}