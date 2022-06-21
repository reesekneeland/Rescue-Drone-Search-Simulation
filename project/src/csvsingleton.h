/**
* @file csvsingleton.h
*
* @copyright 2021 3081W, All rights reserved.
*/

#ifndef CSVSINGLETON_H_
#define CSVSINGLETON_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "entity.h"
#include "drone.h"
#include <sqlite3.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/


 /**
 * @brief The main class for the CSV Singleton pattern, which creates a CSV file containing speed and ending coordinates
 */

class CSVSingleton {
public:
    // Creates an Instance of the CSVSingleton
    static CSVSingleton* Instance();
    /**
    * @brief Creates a CSV file using a dataset of vectors and iterating through them to fill the CSV file.
    *
    * @param dataset A vector of a pair containing a string and a vector of doubles. The string contains the column name and the vector of doubles contains the column data.
    */
    void Create(std::vector<std::pair<std::string, std::vector<double>>> dataset);
private:
    // Constructor for CSVSingleton
    CSVSingleton() {}
    static CSVSingleton* instance;
};
#endif