/**
* @file ChargerFactory.h
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef CHARGER_FACTORY_H
#define CHARGER_FACTORY_H
#include "entity.h"
#include "WebServer.h"
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "Charger.h"
#include "entityFactory.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief The main class for the Charger Factory. Under the factory pattern, this creates Charger entities and inherits from EntityFactory. 
 */

class ChargerFactory: public EntityFactory {

public:
ChargerFactory(){};
 /**
    * @brief Creates a Charger entity
    *
    * @param entityData A picoJson object representing a charger and its attributes
    * 
    * @param cameraController An ICameraController object to control the objects cameras
    *
    * @return Returns an Entity pointer
    */
Entity* Factory(picojson::object& entityData, ICameraController& cameraController);

private:
Charger* charger;

};

#endif