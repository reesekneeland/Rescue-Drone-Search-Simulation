/**
* @file robot.h
*
* @copyright 2021 3081W, All rights reserved.
*/

#ifndef ROBOT_H_
#define ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "entity.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "camera_controller.h"
#include <fstream>
#include "util/base64.h"
#include "web_app.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/


 /**
 * @brief The main class for the Robot Entity
 */

class Robot : public Entity {
public:

    Robot(const double& id);
       // Destructor
    ~Robot();

    /**
    * @brief Gets the robot's ID
    */
    const double& GetID() { return id; };
    /**
    * @brief Gets the robot's vector position
    */
    std::vector<double> GetPosition() { return position; };
    /**
    * @brief The update function for the robot takes a picture with the front camera
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
    * @brief Sets the position of the robot given the coordinates
    */
    void SetPos(double x, double y, double z);
    /**
    * @brief Sets the direction of the robot given the coordinates
    */
    void SetDir(double x, double y, double z);
    /**
    * @brief Adds a camera to the entities camera list
     *
    * @param camera A camera object to be added to the robot
    */
    void AddCam(Camera* camera);
    /**
    * @brief Gets the name of the object
    * @return A string representing the object type.
    */
    std::string GetName(){return "robot";};

    /**
    * @brief Gets the robot's coordinate position
    */
    double GetPosX(){return position.at(0);};
    double GetPosY(){return position.at(1);};
    double GetPosZ(){return position.at(2);};

    /**
    * @brief Set's the robot's manual movement commands
    */
    void SetJoystick(double x, double y, double z, double a, double c){return;};
    Robot(const Robot& robot) = delete;
    Robot& operator=(const Robot& robot) = delete;

private:
    const double id;
    std::vector<double> position;
    std::vector<double> direction;
    std::vector<Camera*> cams;
    float lastPictureTime = 0.0;
    float time = 0.0;
};

#endif
