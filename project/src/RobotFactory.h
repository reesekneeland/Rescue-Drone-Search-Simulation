/**
* @file RobotFactory.h
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef ROBOT_FACTORY_H
#define ROBOT_FACTORY_H
#include "entity.h"
#include "WebServer.h"
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "robot.h"
#include "entityFactory.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief The main class for the Robot Factory. Under the factory pattern, this creates Robot entities and inherits from EntityFactory. 
 */

class RobotFactory: public EntityFactory {

public:
RobotFactory(){};
 /**
    * @brief Creates a Robot entity
    *
    * @param entityData A picoJson object representing a charger and its attributes
    * 
    * @param cameraController An ICameraController object to control the objects cameras
    *
    * @return Returns an Entity pointer
    */
Entity* Factory(picojson::object& entityData, ICameraController& cameraController);

private:
Robot* robot;

};

#endif