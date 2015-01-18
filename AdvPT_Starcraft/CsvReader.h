#pragma once
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>

#include "Objects/Object.h"
#include "Resources/Resources.h"

class CsvReader
{
private:
	static const std::string _unitsFilePath;
	static const std::string _buildingsFilePath;

	static std::map<std::string, Resources::Data> _unitsData;
	static std::map<std::string, Resources::Data> _buildingsData;

    /*
      Removes additional whitechars at the beggining and at the end of the buff.
      Removes doubled whitechars inside the buff.
    */
    static void trim(std::string& buff)
    {
        int currentIndex = 0;
        bool whitespace = false;

        for (unsigned int i = 0; i < buff.length(); i++)
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
        for (unsigned int i = buff.length() - 1; i >= currentIndex; i--)
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
        bool firstError = true;

        std::string name;
        Resources::Data data;

        std::stringstream ss(line);
        
        ss >> name;
        ss >> data.mineral;
        ss >> data.vespen;
        ss >> data.supply;
        ss >> data.time;

        std::string buildingName;

        while (!ss.eof())
        {
            ss >> buildingName;
            data.required_buildings.push_front(buildingName);
        }

        return std::make_tuple(name, data);
    }

    static bool update(const ObjectType type, std::string& error)
    {
        std::string errorMessage = error;
        std::string filePath;

        if (type == Unit) {
            filePath = _unitsFilePath;
        } if (type == Building) {
            filePath = _unitsFilePath;
        } else {
            error += "\nWrong Object type";
            return false;
        }

        // read file
        std::ifstream file(filePath);

        if (!file)
        {
            error += "\nOpening file " + filePath + " failed";
            file.close();
            return false;
        }

        std::string line;

        // get header
        std::getline(file, line);

        while (std::getline(file, line))
        {
            trim(line);

            auto result = getData(line, error);

            // get resources data
            _unitsData[std::get<0>(result)] = std::get<1>(result);
        }

        return true;
    }

public:

	CsvReader() = delete;

	static bool updateUnits(std::string& error)
	{	
        return update(Unit, error);
	}

    static bool updateBuildings(std::string& error)
    {
        return update(Building, error);
    }

	static Resources::Data getRequirements(const ObjectType type, const std::string name)
	{
        if (type == Unit)
		    return _unitsData[name];
        else
            return _buildingsData[name];
	}

    static ObjectType resolveType(const std::string name)
    {
        // check if unit
        for (auto unit : _unitsData)
            if (unit.first == name)
                return Unit;

        // check if building
        for (auto building : _buildingsData)
            if (building.first == name)
                return Building;

        // unknown
        return Unknown;
    }
};

const std::string CsvReader::_unitsFilePath = ".\\Data\\units.csv";
const std::string CsvReader::_buildingsFilePath = ".\\Data\\buildings.csv";

std::map<std::string, Resources::Data> CsvReader::_unitsData;
std::map<std::string, Resources::Data> CsvReader::_buildingsData;