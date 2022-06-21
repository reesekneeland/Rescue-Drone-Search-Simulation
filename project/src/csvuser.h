/**
* @file csvuser.h
*
* @copyright 2021 3081W, All rights reserved.
*/

#ifndef CSVUSER_H_
#define CSVUSER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "csvsingleton.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

 /**
 * @brief The main class for using the CSV Singleton pattern, which creates a CSV file containing speed and ending coordinates
 */

class CSVUser {
public:
    /**
    * @brief Inserts each parameter into a vector, then passes the vectors into another vector containing the title of a column and the paramter vector. Calls CSVSingleton to creatue the CSV file.
    *
    * @param speed A double representing the speed of the drone.
    * 
    * @param x A double representing the X Coordinate of the drone.
    *
    * @param y A double representing the Y Coordinate of the drone.
    *
    * @param z A double representing the Z Coordinate of the drone.
    */
    static void DoSomething(double speed, double x, double y, double z);
};


#endif