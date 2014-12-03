#pragma once
#include <string>
#include <forward_list>

class Object
{
protected:

    // enums
    enum ObjectType {Unit, Building};
    const std::string objectTypeStrings[2] = { "Unit", "Building" };

    enum UnitType {
        Probe, Zealot, Stalker, Sentry, Observer, Immortal, WarpPrism,
        Colossus, Phoenix, VoidRay, HighTemplar, DarkTemplar, Carrier, Mothership};
    const std::string unitTypeStrings[14] = {
        "Probe", "Zealot", "Stalker", "Sentry", "Observer", "Immortal", "WarpPrism",
        "Colossus", "Phoenix", "VoidRay", "HighTemplar", "DarkTemplar", "Carrier", "Mothership"};

    enum BuildingType {
        Nexus, Pylon, Assimilator, Gateway, Warpgate, Forge, CyberneticsCore,
        PhotonCannon, Stargate, RoboticsFacility, TwilightControl, FleetBeacon, RoboticsBay, DarkShrine, TemplarArchives};
    const std::string buildingTypeStrings[15] = {
        "Nexus", "Pylon", "Assimilator", "Gateway", "Warpgate", "Forge", "CyberneticsCore",
        "PhotonCannon", "Stargate", "RoboticsFacility", "TwilightControl", "FleetBeacon", "RoboticsBay", "DarkShrine", "TemplarArchives"};

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
};

