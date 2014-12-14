#pragma once
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

#include "Types.h"
#include "Resources.h"

class XmlReader
{
private:
	static const std::string _unitsXmlFilePath;
	static const std::string _buildingsXmlFilePath;
	static std::map<Types::UnitType, Resources::Data> _unitsData;
	static std::map<Types::BuildingType, Resources::Data> _buildingsData;
public:

	XmlReader() = delete;

	static std::string getData(std::string l) //taking data contained in <>
	{
		std::string tmp;

		for (int i = 0; i < l.length; i++)
		{
			if (l[i] != '<' && l[i] != '>' && l[i] != ' ')
				tmp.append = l[i];
		
		}

		
		return tmp;
		
	}

	static int getCoefficient(std::string l) // taking coefficient from xml (f.ex. number of minerals)
	{
		std::string coeff;
		bool syntax_end = false;

		for (int i = 0; i < l.length; i++)
		{
			if (l[i] == '>')
				syntax_end = true;

			if (l[i] == '<')
				syntax_end = false;

			if (l[i] != '<' && l[i] != '>' && syntax_end == true)
				coeff.append = l[i];

		}

		
		return std::stoi(coeff);
	}

	static std::string updateUnits()
	{	
		std::string line, tmp;

		std::fstream file;
		file.open(_unitsXmlFilePath, std::fstream::out);
		while (!EOF)
		{
			std::getline(file, line);
			line = getData(line); 
			//tbc...
		}
		
		file.close();
		
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

const std::string XmlReader::_unitsXmlFilePath = "./units.xml";
const std::string XmlReader::_buildingsXmlFilePath = "./buildings.xml";