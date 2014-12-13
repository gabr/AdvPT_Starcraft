#pragma once
#include <string>
#include <algorithm>
#include <forward_list>

struct Requirements
{
    unsigned int mineral = 0;
    unsigned int vespen = 0;
    unsigned int supply = 0;
    unsigned int time = 0;
};

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
    Requirements _requirements;
    std::forward_list<BuildingType> _required_buildings;

    // object informations
    std::string _name = "";
    ObjectType _type = Unknown;
    unsigned int _startTime = 0;

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
const std::string Object::objectTypeStrings[3] = { "unit", "building", "unknown" };

const std::string Object::unitTypeStrings[Object::_numberOfUnitsTypes] = {
    "probe", "zealot", "stalker", "sentry", "observer", "immortal", "warp_prism",
    "colossus", "phoenix", "void_ray", "high_templar", "dark_templar", "carrier", "mothership" };

const std::string Object::buildingTypeStrings[Object::_numberOfBuildingsTypes] = {
    "nexus", "pylon", "assimilator", "gateway", "warpgate", "forge", "cybernetics_core",
    "photon_cannon", "stargate", "robotics_facility", "twilight_control", "fleet_beacon", "robotics_bay", "dark_shrine", "templar_archives" };