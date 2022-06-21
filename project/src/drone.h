/**
* @file drone.h
*
* @copyright 2021 3081W, All rights reserved.
*/

#ifndef DRONE_H_
#define DRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity.h"
#include <vector>
#include "graph.h"
#include <cmath>
#include <iostream>
#include "camera_controller.h"
#include <fstream>
#include "util/base64.h"
#include "web_app.h"
#include "math.h"
#include "csvuser.h"
#include <sqlite3.h>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the Drone entity, which operates in a physical system
 *
 *  Drones move using euler itegration based on a specified velocity and direction.
 */
class Drone : public Entity {
public:
    // Drones are created with an id
    Drone(const double& id);
    // Destructor
    ~Drone();
    /**
    * @brief Gets the drone ID.
    *
    * @return A double representing the ID of the drone.
    */
    const double& GetID() { return id; };
    /**
    * @brief Gets the drone position.
    *
    * @return A vector of doubles representing its coordinate position in 3d space.
    */
    std::vector<double> GetPosition() { return position; };
    /**
    * @brief Updates the drones position based on the frame duration of the current update. 
    * Moves the drone towards the targetPosition variable.
    *
    * @param dt A double representing the frame duration of the current update.
    * 
    * @param flag Boolean flag, true represents a manual movement mode that uses the keyboard
    * while false represents the patrolling search algorithm that moves automatically.
    */
    void Update(double dt, bool flag);
    /**
    * @brief sets the drones target to a new node, calls SetTarget to update position as well
    *
    * @param node A string representing the node ID that the drone should target and move towards.
    */
    void SetTargetNode(string node);
    /**
    * @brief updates the graph priority queue and the drone target node
    *
    * @param node a string representing the node to be visted.
    */
    void UpdateTarget(string node);
    /**
    * @brief sets the drones target position to a given set of coordinates.
    *
    * @param targetPosition A vector of doubles representing the target position in 3d space.
    */
    void SetTarget(std::vector<double> targetPosition);
    /**
    * @brief gets the target node
    *
    * @return a string containing the node id of the target node
    */
    string GetTargetNode();
    /**
    * @brief Euclidean distance calculator helper function.
    *
    * @param start A vector of doubles representing the starting position for the distance calculation.
    *
    * @param end A vector of doubles representing the ending position for the distance calculation.
    *
    * @return A double representing the Euclidean distance between the points.
    */
    double GetDist(std::vector<double> start, std::vector<double> end);
    /**
    * @brief updates the direction towards the stored target position.
    */
    void SetDirection();
    /**
    * @brief Gets the drones target position
    *
    * @return A vector of doubles representing the current target position of the drone.
    */
    std::vector<double> GetTarget();
    void SetJoystick(double x, double y, double z, double a, double c);
    /**
    * @brief prints the current position of the drone
    */
    void printPos();
    /**
    * @brief Sets the current speed of the drone.
    *
    * @param speed a double representing the new speed of the drone.
    */
    void SetSpeed(double speed);
    /**
    * @brief Gets the current speed of the drone.
    *
    * @return a double representing the speed of the drone.
    */
    double GetSpeed(){return speed;};
    /**
    * @brief Sets the current position of the drone.
    *
    * @param x a double representing new X coordinate of the drone.
    *
    * @param y a double representing new Y coordinate of the drone.
    *
    * @param z a double representing new Z coordinate of the drone.
    */
    void SetPos(double x, double y, double z);
    /**
    * @brief Gets the current X position of the drone.
    *
    * @return a double representing the X coordinate of the drone.
    */
    double GetPosX(){return position.at(0);};
    /**
    * @brief Gets the current Y position of the drone.
    *
    * @return a double representing the Y coordinate of the drone.
    */
    double GetPosY(){return position.at(1);};
    /**
    * @brief Gets the current Z position of the drone.
    *
    * @return a double representing the Z coordinate of the drone.
    */
    double GetPosZ(){return position.at(2);};
    /**
    * @brief Gets the current X direction of the drone.
    *
    * @return a double representing the X direction magnitude of the drone.
    */
    double GetDirX(){return direction.at(0);};
    /**
    * @brief Gets the current Y direction of the drone.
    *
    * @return a double representing the Y direction magnitude of the drone.
    */
    double GetDirY(){return direction.at(1);};
    /**
    * @brief Gets the current Z direction of the drone.
    *
    * @return a double representing the Z direction magnitude of the drone.
    */
    double GetDirZ(){return direction.at(2);};
    /**
    * @brief Sets the current direction of the drone.
    *
    * @param x a double representing new X direction magnitude of the drone.
    *
    * @param y a double representing new Y direction magnitude of the drone.
    *
    * @param z a double representing new Z direction magnitude of the drone.
    */
    void SetDir(double x, double y, double z);
    std::vector<Camera*> getCams(){return cams;};

    /**
    * @brief sets whether the patrol behavior is enabled or not
    *
    * @param camera A pointer to a camera object to be added to the drone.
    */
    void SetPatrol(bool state);
    /**
    * @brief Adds a camera to the drone object
    *
    * @param camera A pointer to a camera object to be added to the drone.
    */
    void AddCam(Camera* camera);
    /**
    * @brief Gets the name of the entity, in this class it will always return drone.
    *
    * @return A string representing the entity name, for this class it will always return drone.
    */
    std::string GetName(){return "drone";};

    Drone(const Drone& drone) = delete;
    Drone& operator=(const Drone& drone) = delete;
    /**
    * @brief Gets the name of the entity, in this class it will always return drone.
    */
    std::vector<double> position;
    std::vector<double> direction;
private:
    const double id;
    double speed;
    std::vector<double> targetPosition;
    string targetNode;
    double theta;
    double phi;
    double psi;
    std::vector< Camera* > cams;
    float lastPictureTime = 0.0;
    float time = 0.0;
    bool isPatrol = true;
    Graph *UmnGraph;
    int counter;
};

#endif