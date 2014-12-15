#pragma once
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "Types.h"
#include "Resources.h"

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

        return Types::UnitType::Unknown;
    }

    static Types::BuildingType resolveBuildingType(const std::string name)
    {
        for (int i = 1; i < Types::numberOfUnitsTypes; i++)
        if (name == Types::unitTypeStrings[i])
            return static_cast<Types::BuildingType>(i);

        return Types::BuildingType::Unknown;
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
        Check for errors and if any return error message.

        file struct:
            name minerals vespen supply build-time buildings
    */
    static std::string getData(const std::string line, std::string& name, Resources::Data& data)
    {
        std::string error = "";
        std::stringstream ss(line);
        
        ss >> name;
        ss >> data.mineral;
        ss >> data.vespen;
        ss >> data.supply;
        ss >> data.time;

        std::string buildingName;
        Types::BuildingType buildingType = Types::BuildingType::Unknown;

        while (!ss.eof)
        {
            ss >> buildingName;
            buildingType = resolveBuildingType(buildingName);

            if (buildingType == Types::BuildingType::Unknown)
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

        return error;
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
            std::string unitName;
            Resources::Data data;

            std::string error = getData(line, unitName, data);
            
            if (error != "")
                errorMessage += error + "\n";

            Types::UnitType type = resolveUnitType(unitName);
            if (type == Types::UnitType::Unknown)
                errorMessage += "Unknown Unit type in file: " + _unitsFilePath + "\n";

            _unitsData[type] = data;
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
            std::string buildingName;
            Resources::Data data;

            std::string error = getData(line, buildingName, data);

            if (error != "")
                errorMessage += error + "\n";

            Types::BuildingType type = resolveBuildingType(buildingName);
            if (type == Types::BuildingType::Unknown)
                errorMessage += "Unknown Building type in file: " + _buildingsFilePath + "\n";

            _buildingsData[type] = data;
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

const std::string CsvReader::_unitsFilePath = ".\\units.xml";
const std::string CsvReader::_buildingsFilePath = ".\\buildings.xml";