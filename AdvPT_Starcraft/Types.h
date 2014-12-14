#pragma once
#include <string>

class Types
{
private:
    static const unsigned short _numberOfUnitsTypes = 14;
    static const unsigned short _numberOfBuildingsTypes = 15;

public:
    Types() = delete;

    // enums
    static enum ObjectType { Unit, Building, Unknown };
    static const std::string objectTypeStrings[3];

    static enum UnitType
    {
        Probe, Zealot, Stalker, Sentry, Observer, Immortal, WarpPrism,
        Colossus, Phoenix, VoidRay, HighTemplar, DarkTemplar, Carrier, Mothership
    };
    static const std::string unitTypeStrings[_numberOfUnitsTypes];

    static enum BuildingType
    {
        Nexus, Pylon, Assimilator, Gateway, Warpgate, Forge, CyberneticsCore,
        PhotonCannon, Stargate, RoboticsFacility, TwilightControl, FleetBeacon, RoboticsBay, DarkShrine, TemplarArchives
    };
    static const std::string buildingTypeStrings[_numberOfBuildingsTypes];
};


// statics initializations
const std::string Types::objectTypeStrings[3] = { "unit", "building", "unknown" };

const std::string Types::unitTypeStrings[Types::_numberOfUnitsTypes] = {
    "probe", "zealot", "stalker", "sentry", "observer", "immortal", "warp_prism",
    "colossus", "phoenix", "void_ray", "high_templar", "dark_templar", "carrier", "mothership" };

const std::string Types::buildingTypeStrings[Types::_numberOfBuildingsTypes] = {
    "nexus", "pylon", "assimilator", "gateway", "warpgate", "forge", "cybernetics_core",
    "photon_cannon", "stargate", "robotics_facility", "twilight_control", "fleet_beacon", "robotics_bay", "dark_shrine", "templar_archives" };