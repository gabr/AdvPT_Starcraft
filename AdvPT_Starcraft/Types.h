#pragma once
#include <string>

namespace Types
{
    // enums
    enum ObjectType { Unit, Building, Unknown };
    const std::string objectTypeStrings[3] = { "unit", "building", "unknown" };

    enum UnitType
    {
        Probe, Zealot, Stalker, Sentry, Observer, Immortal, WarpPrism,
        Colossus, Phoenix, VoidRay, HighTemplar, DarkTemplar, Carrier, Mothership
    };
    const unsigned short _numberOfUnitsTypes = 14;
    const std::string unitTypeStrings[_numberOfUnitsTypes] = {
        "probe", "zealot", "stalker", "sentry", "observer", "immortal", "warp_prism",
        "colossus", "phoenix", "void_ray", "high_templar", "dark_templar", "carrier", "mothership" };

    enum BuildingType
    {
        Nexus, Pylon, Assimilator, Gateway, Warpgate, Forge, CyberneticsCore,
        PhotonCannon, Stargate, RoboticsFacility, TwilightControl, FleetBeacon, RoboticsBay, DarkShrine, TemplarArchives
    };
    const unsigned short _numberOfBuildingsTypes = 15;
    const std::string buildingTypeStrings[_numberOfBuildingsTypes] = {
        "nexus", "pylon", "assimilator", "gateway", "warpgate", "forge", "cybernetics_core",
        "photon_cannon", "stargate", "robotics_facility", "twilight_control", "fleet_beacon", "robotics_bay", "dark_shrine", "templar_archives" };
};