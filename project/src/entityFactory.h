/**
* @file entityFactory.h
*
* @copyright 2021 3081W, All rights reserved.
*/


/*******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "entity.h"
#include "WebServer.h"
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

 /**
 * @brief The parent class for EntityFactories.
 */

class EntityFactory {
public:

/**
    * @brief Creates an entity
    *
    * @param entityData A picoJson object representing a charger and its attributes
    * 
    * @param cameraController An ICameraController object to control the objects cameras
    *
    * @return Returns an Entity pointer
    */
virtual Entity* Factory(picojson::object& entityData, ICameraController& cameraController)=0;

};

#endif