/**
* @file DroneFactory.h
*
* @copyright 2021 3081W, All rights reserved.
*/

#ifndef DRONE_FACTORY_H
#define DRONE_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "entity.h"
#include "WebServer.h"
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "drone.h"
#include "entityFactory.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief The main class for the Drone Factory. Under the factory pattern, this creates Drone entities and inherits from EntityFactory. 
 */

class DroneFactory: public EntityFactory {

public:
DroneFactory(){};
 /**
    * @brief Creates a Drone entity
    *
    * @param entityData A picoJson object representing a charger and its attributes
    * 
    * @param cameraController An ICameraController object to control the objects cameras
    *
    * @return Returns an Entity pointer
    */
Entity* Factory(picojson::object& entityData, ICameraController& cameraController);

private:
    Drone* drone;
};

#endif