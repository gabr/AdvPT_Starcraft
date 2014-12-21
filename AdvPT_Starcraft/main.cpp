#include <iostream>
#include <string>
#include <fstream>

#include "CsvReader.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;


int main(int argc, char* argv[])
{
    // Getting files list

    if (argc <= 1) // no files specified
    {
        cout << " ! error: No file specified." << endl;
        cout << endl;
        cout << " Usage: " << endl;
        cout << "        " << argv[0] << " <path_to_file>" << endl;
        return 1;
    }

    // for errors messages
    string error = "";

    // Gettings Units and Buildings data
    if (!CsvReader::updateUnits(error))
    {
        cout << " ! error: " << error << endl;
        return 1;
    }
    if (!CsvReader::updateBuildings(error))
    {
        cout << " ! error: " << error << endl;
        return 1;
    }

    // Simulate for each file
    for (int i = 1; i < argc; i++)
    {
        // check file path
        ifstream file(argv[i]);

        // if given path is wrong print error and check the next one
        if (!file)
        {
            cout << " ! error: Wrong path to file: " << argv[i] << endl;
            continue;
        }

        cout << " > Simulating file: " << argv[i] << endl << endl;
        Simulator s(file);
        
        string result = "";
        bool state = s.run(result, error);

        if (state)
            cout << result << endl;
        else
            cout << error << endl;
    }

    return 0;
}