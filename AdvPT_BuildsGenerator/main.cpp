#include <fstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <random>
#include <sstream>



int coolRandom(int min, int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(min,max); 

	return floor(dist(mt));
}


void unitsToTab(std::string tab[])
{
	const std::string _filePath = ".\\Data\\units_generator.csv";

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


void randomUnitToFile(std::string tab[],std::string fname,std::string fpath)
{
	
	// create path and name
	std::string name = fname + ".txt";
	// create file
	std::ofstream result(fpath+name);
	// fill file with random units

	int r = floor(coolRandom(15, 50));

	for (int j = 0; j < r; j++)
	{
		int i = coolRandom(0, 27); //27 is max index of unit
		result << tab[i] << "\n";
	}
}

int main(int argc, char* argv[])
{
	// Getting files list

	if (argc < 3) // no files specified
	{
		std::cout << " ! error: No file specified." << std::endl;
		std::cout << std::endl;
		std::cout << " Usage: " << std::endl;
		std::cout << "        " << argv[0] << " <path_to_file>" << std::endl;
		return 1;
	}

	std::string path = argv[1];

	//number of files
	int n = 0;
	std::stringstream ss(argv[2]);
	ss >> n;  
	
	//rewrite unit from file to tab
	std::string units[28];
	unitsToTab(units);

	// generate file with random list
 
	for (int i = 0; i < n; i++)
	{
		std::string name = std::to_string(i);
		randomUnitToFile(units, name,path);
	}

	return 0;
}