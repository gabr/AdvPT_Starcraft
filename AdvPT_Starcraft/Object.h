#pragma once
#include <string>
#include <algorithm>
#include <forward_list>

class Object
{
protected:

    // enums
    static enum ObjectType {Unit, Building, Unknown};
    static const std::string objectTypeStrings[3];

    static const unsigned short _numberOfUnitsTypes = 14;
    static enum UnitType {
        Probe, Zealot, Stalker, Sentry, Observer, Immortal, WarpPrism,
        Colossus, Phoenix, VoidRay, HighTemplar, DarkTemplar, Carrier, Mothership};
    static const std::string unitTypeStrings[_numberOfUnitsTypes];

    static const unsigned short _numberOfBuildingsTypes = 15;
    static enum BuildingType {
        Nexus, Pylon, Assimilator, Gateway, Warpgate, Forge, CyberneticsCore,
        PhotonCannon, Stargate, RoboticsFacility, TwilightControl, FleetBeacon, RoboticsBay, DarkShrine, TemplarArchives};
    static const std::string buildingTypeStrings[_numberOfBuildingsTypes];

    // requirements
    unsigned int _required_mineral = 0;
    unsigned int _required_vespen = 0;
    unsigned int _required_supply = 0;

    std::forward_list<BuildingType> _required_buildings;

    // object informations
    std::string _name;
    ObjectType _type;

public:
    virtual bool init() = 0;
    virtual std::string toString() { return _name; }

    static ObjectType resolveType(std::string objectName)
    {
        // check all units
        for (unsigned int i = 0; i < _numberOfUnitsTypes; i++)
            if (objectName == unitTypeStrings[i]) return Unit;

        // check all buildings
        for (unsigned int i = 0; i < _numberOfBuildingsTypes; i++)
            if (objectName == buildingTypeStrings[i]) return Building;

        // unknown object name
        return Unknown;
    }
};

// statics initializations
const std::string Object::objectTypeStrings[3] = { "Unit", "Building", "Unknown" };

const std::string Object::unitTypeStrings[Object::_numberOfUnitsTypes] = {
    "Probe", "Zealot", "Stalker", "Sentry", "Observer", "Immortal", "WarpPrism",
    "Colossus", "Phoenix", "VoidRay", "HighTemplar", "DarkTemplar", "Carrier", "Mothership" };

const std::string Object::buildingTypeStrings[Object::_numberOfBuildingsTypes] = {
    "Nexus", "Pylon", "Assimilator", "Gateway", "Warpgate", "Forge", "CyberneticsCore",
    "PhotonCannon", "Stargate", "RoboticsFacility", "TwilightControl", "FleetBeacon", "RoboticsBay", "DarkShrine", "TemplarArchives" };