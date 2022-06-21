/**
* @file entity.h
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef ENTITY_H_
#define ENTITY_H_

#include <fstream>
#include "util/base64.h"
#include <iostream>
#include <vector>
#include <string>
#include "WebServer.h"
#include "camera_controller.h"
#include "camera.cc"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief Entity is the base class for any object and is inherited by each object
 */

class Entity {
public:

    // Destructor
    virtual ~Entity() {};
     /**
    * @brief Gets the Entity's ID
    */
    virtual const double& GetID();
    /**
    * @brief Gets the entity vector position
    */
    virtual std::vector<double> GetPosition()=0;
    /**
    * @brief Gets the entity's type
    */
    virtual std::string GetName()=0;
    virtual void SetJoystick(double x, double y, double z, double a, double c){};
    /**
    * @brief Gets the entity speed. 0 if is stationary.
    *
    * @return a double value representing speed
    */
    virtual double GetSpeed(){return 0;};
    /**
    * @brief Gets the Entity's X Position
    */
    virtual double GetPosX()=0;
    /**
    * @brief Gets the entity's y position
    */
    virtual double GetPosY()=0;
    /**
    * @brief Gets the entity's z position
    */
    virtual double GetPosZ()=0;
     /**
    * @brief Outputs the given vector position.
     *
    * @param pos Vector to print out.
    */
    virtual void printPos(std::vector<double> pos){};
    /**
    * @brief The update function for the entity takes a picture with its camera
     *
    * @param dt A double value representing elapsed time.
    */
    virtual void Update(double dt){};

};


#endif