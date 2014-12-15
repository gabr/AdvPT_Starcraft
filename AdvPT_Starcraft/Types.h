#pragma once
#include <string>

namespace Types
{
    // enums
    enum ObjectType { Unit, Building, Unknown };
    const std::string objectTypeStrings[3] = { "unit", "building", "unknown" };

    enum UnitType
    {
        UnknownUnit, Probe, Zealot, Stalker, Sentry, Observer, Immortal, WarpPrism,
        Colossus, Phoenix, VoidRay, HighTemplar, DarkTemplar, Carrier, Mothership
    };
    const unsigned short numberOfUnitsTypes = 15;
    const std::string unitTypeStrings[numberOfUnitsTypes] = {
        "unknown_unit", "probe", "zealot", "stalker", "sentry", "observer", "immortal", "warp_prism",
        "colossus", "phoenix", "void_ray", "high_templar", "dark_templar", "carrier", "mothership" };

    enum BuildingType
    {
        UnknownBuilding, Nexus, Pylon, Assimilator, Gateway, Warpgate, Forge, CyberneticsCore,
        PhotonCannon, Stargate, RoboticsFacility, TwilightCouncil, FleetBeacon, RoboticsBay, DarkShrine, TemplarArchives
    };
    const unsigned short numberOfBuildingsTypes = 16;
    const std::string buildingTypeStrings[numberOfBuildingsTypes] = {
        "unknown_building", "nexus", "pylon", "assimilator", "gateway", "warpgate", "forge", "cybernetics_core",
        "photon_cannon", "stargate", "robotics_facility", "twilight_council", "fleet_beacon", "robotics_bay", "dark_shrine", "templar_archives" };
};