/**
* @file Charger.h
*
* @copyright 2021 3081W, All rights reserved.
*/


#ifndef CHARGER_H_
#define CHARGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "entity.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "camera_controller.h"
#include <fstream>
#include "util/base64.h"
#include "web_app.h"


/*******************************************************************************
 * Class Definitions
 ******************************************************************************/


 /**
 * @brief The main class for the Recharge Station Entity
 */

class Charger : public Entity {
public:

    // Constructor
    Charger(const double& id);
    // Destructor
    ~Charger();

    /**
    * @brief Gets the Recharge Station's ID
    */
    const double& GetID() { return id; };
    /**
    * @brief Gets the Recharge Station's vector position
    */
    std::vector<double> GetPosition() { return position; };
    /**
    * @brief Gets the Recharge Station's Speed. 0 because it is stationary.
    */
    double GetSpeed(){return 0;};
    /**
    * @brief Gets the Recharge Station's X Position
    */
    double GetPosX(){return position.at(0);};
    /**
    * @brief Gets the Recharge Station's y position
    */
    double GetPosY(){return position.at(1);};
    /**
    * @brief Gets the Recharge Station's z position
    */
    double GetPosZ(){return position.at(2);};
    void SetJoystick(double x, double y, double z, double a, double c){return;};
    /**
    * @brief The update function for the recharge station takes a picture with the front camera
     *
    * @param dt A double value representing elapsed time.
    */
    void Update(double dt);
    /**
    * @brief Outputs the given vector position.
     *
    * @param pos Vector to print out.
    */
    void printPos(std::vector<double> pos);
    /**
    * @brief Sets the position of the recharge station given the coordinates
    */
    void SetPos(double x, double y, double z);
    /**
    * @brief Adds a camera to the entities camera list
     *
    * @param camera A camera object to be added to the recharge station
    */
    void AddCam(Camera* camera);
    /**
    * @brief Gets the name of the object
    * @return A string representing the object type.
    */
    std::string GetName(){return "charger";};

    Charger(const Charger& charger) = delete;
    Charger& operator=(const Charger& charger) = delete;

private:
    const double id;
    std::vector<double> position;
    std::vector<Camera*> cams;
    float lastPictureTime = 0.0;
    float time = 0.0;
};

#endif
