#pragma once
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>

#include "Types.h"
#include "Resources/Resources.h"

class CsvReader
{
private:
	static const std::string _unitsFilePath;
	static const std::string _buildingsFilePath;

	static std::map<Types::UnitType, Resources::Data> _unitsData;
	static std::map<Types::BuildingType, Resources::Data> _buildingsData;

    static Types::UnitType resolveUnitType(const std::string name)
    {
        for (int i = 1; i < Types::numberOfUnitsTypes; i++)
            if (name == Types::unitTypeStrings[i])
                return static_cast<Types::UnitType>(i);

        return Types::UnitType::UnknownUnit;
    }

    static Types::BuildingType resolveBuildingType(const std::string name)
    {
        for (int i = 1; i < Types::numberOfBuildingsTypes; i++)
        if (name == Types::buildingTypeStrings[i])
            return static_cast<Types::BuildingType>(i);

        return Types::BuildingType::UnknownBuilding;
    }

    /*
      Removes additional whitechars at the beggining and at the end of the buff.
      Removes doubled whitechars inside the buff.
    */
    static void trim(std::string& buff)
    {
        int currentIndex = 0;
        bool whitespace = false;

        for (int i = 0; i < buff.length(); i++)
        {
            if (!isspace(buff[i]))
            {
                buff[currentIndex] = buff[i];
                ++currentIndex;
                whitespace = false;
            }
            else if (!whitespace)
            {
                buff[currentIndex] = buff[i];
                ++currentIndex;
                whitespace = true;
            }
        }

        // clean the tail
        for (int i = buff.length() - 1; i >= currentIndex; i--)
            buff[i] = '\0';

        // clean the head
        currentIndex = -1;
        for (int i = 0; i < buff.length(); i++)
            if (isspace(buff[i])) currentIndex = i;
            else break;

        buff = buff.substr(currentIndex + 1);
    }

    /*
        Takes data from single line.
        Check for errors and if any put in error reference.

        file struct:
            name minerals vespen supply build-time buildings
    */
    static std::tuple<std::string, Resources::Data> getData(const std::string line, std::string& error)
    {
        std::string name;
        Resources::Data data;

        error = ""; // clean error reference

        std::stringstream ss(line);
        
        ss >> name;
        ss >> data.mineral;
        ss >> data.vespen;
        ss >> data.supply;
        ss >> data.time;

        std::string buildingName;
        Types::BuildingType buildingType = Types::BuildingType::UnknownBuilding;

        while (!ss.eof())
        {
            ss >> buildingName;
            buildingType = resolveBuildingType(buildingName);

            if (buildingType == Types::BuildingType::UnknownBuilding)
            {
                if (error == "")
                    error = "Wrong building name for " + name + " : ";

                error += buildingName + ", ";
            }
            else
            {
                data.required_buildings.push_front(buildingType);
            }

        }

        return std::make_tuple(name, data);
    }

public:

	CsvReader() = delete;

	static std::string updateUnits()
	{	
        std::string errorMessage = "";

        // read whole file
        std::ifstream file(_unitsFilePath);

        if (!file)
            return "Opening file " + _unitsFilePath + " failed";

        std::string line;

        // get header
        std::getline(file, line);

        while (std::getline(file, line))
        {
            trim(line);
            std::string error;

            auto result = getData(line, error);
            
            if (error != "")
                errorMessage += error + "\n";

            // get the unit type from name
            Types::UnitType type = resolveUnitType(std::get<0>(result));
            if (type == Types::UnitType::UnknownUnit)
                errorMessage += "Unknown Unit type in file: " + _unitsFilePath + "\n";

            // get resources data
            _unitsData[type] = std::get<1>(result);
        }
		
        return errorMessage;
	}

    static std::string updateBuildings()
    {
        std::string errorMessage = "";

        // read whole file
        std::ifstream file(_buildingsFilePath);

        if (!file)
            return "Opening file " + _buildingsFilePath + " failed";

        std::string line;

        // get header
        std::getline(file, line);

        while (std::getline(file, line))
        {
            trim(line);
            std::string error;

            auto result = getData(line, error);

            if (error != "")
                errorMessage += error + "\n";

            // get building type by name
            Types::BuildingType type = resolveBuildingType(std::get<0>(result));
            if (type == Types::BuildingType::UnknownBuilding)
                errorMessage += "Unknown Building type in file: " + _buildingsFilePath + "\n";

            // get resources data
            _buildingsData[type] = std::get<1>(result);
        }

        return errorMessage;
    }

	static Resources::Data getRequirements(Types::UnitType type)
	{
		return _unitsData[type];
	}

	static Resources::Data getRequirements(Types::BuildingType type)
	{
		return _buildingsData[type];
	}
};

const std::string CsvReader::_unitsFilePath = ".\\Data\\units.csv";
const std::string CsvReader::_buildingsFilePath = ".\\Data\\buildings.csv";

std::map<Types::UnitType, Resources::Data> CsvReader::_unitsData;
std::map<Types::BuildingType, Resources::Data> CsvReader::_buildingsData;