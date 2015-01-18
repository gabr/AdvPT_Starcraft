#include <fstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <random>



int coolRandom()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0,27); //27 is max index of unit

	return floor(dist(mt));
}


void unitsToTab(std::string tab[])
{
	const std::string _filePath = ".\\Data\\units.csv";

	std::ifstream file(_filePath);

	if (!file)
	{
		file.close();
		std::cout << "Reading file failed" << std::endl;
	}

	std::string line;

	int i = 0;
	while (std::getline(file, line))
	{
		tab[i] = line;
		i++;
	}
}


void randomUnitToFile(std::string tab[],std::string path)
{
	
	// create path and name
	std::string name = path + ".txt";
	// create file
	std::ofstream result(name);
	// fill file with random units

	for (int j = 0; j < 20; j++)
	{
		int i = coolRandom();
		result << tab[i] << "\n";
	}
}

void main()
{
	//rewrite unit from file to tab
	std::string units[28];
	unitsToTab(units);

	// generate file with random list
	int n = 5; //number of files
	for (int i = 0; i < n; i++)
	{
		std::string name = std::to_string(i);
		randomUnitToFile(units, name);
	}
}