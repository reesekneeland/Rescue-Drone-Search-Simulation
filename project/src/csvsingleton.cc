#include "csvsingleton.h"
#include "entity.h"
// A singleton pattern class to read data from the web app and gather data into a CSV file.
// Each column of data is represented by the pair <column name, column data>
// as std::pair<std::string, std::vector<int>>

CSVSingleton* CSVSingleton::Instance() {
    static CSVSingleton *instance = new CSVSingleton();
    if (!instance) {
        instance = new CSVSingleton();
    }
    return instance;
}
void CSVSingleton::Create(std::vector<std::pair<std::string, std::vector<double>>> dataset) {
    std::ofstream myFile("statistics.csv");
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

// Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }
    // Close the file
    myFile.close();
}