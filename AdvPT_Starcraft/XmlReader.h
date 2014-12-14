#pragma once
#include <string>
#include <map>

class XmlReader
{
private:
	static std::string _unitsXmlFilePath = "./units.xml";
	static std::map<UnitType, Resources> _unitsData;
public:

	XmlReader() = delete;

	static std::string updateUnits()
	{
	
	}

	static Resources getRequirements(UnitType type)
	{
		return _unitsData.getItem(type);
	};

	static Resources getRequirements(BuildingType type)
	{
		return _unitsData.getItem(type);
	}

	
};

