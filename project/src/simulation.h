/**
* @file simulation.h
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
******************************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include "entity.h"
#include "DroneFactory.h"
#include "RobotFactory.h"
#include "ChargerFactory.h"
#include "csvuser.h"
#include <sqlite3.h>
#include "graph.h"
//#include "camera.cc"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief The main class for Simulation facade.
 */

class Simulation : public JSONSession, public ICameraController{
public:

    Simulation();
    ~Simulation();

    void Update(double dt);
    /**
    * @brief Creates an entity based on JSON data stored as an object.
    */
    void CreateEntity(picojson::object& entityData, ICameraController& cameraController);
    /**
    * @brief Called after all updating is done.  Entity is returned to the UI.
    */
    void FinishUpdate(picojson::object& returnValue);
    /**
    * @brief Accesses the list of creaed entities
    *
    * @return Returns a list of created Entity pointers
    */
    std::vector<Entity*> getEntities(){return entitylist;};
    /**
    * @brief Takes picture for a specific camera
    */
     void TakePicture(int cameraId);
    /**
    * @brief Adds camera observers to the application
    */
    void AddObserver(ICameraObserver& observer);
    /**
    * @brief Removes camera observers from the application
    */
    void RemoveObserver(ICameraObserver& observer);

    ICameraResult* ProcessImages(ICameraObserver* observer, int cameraId, double xPos, double yPos, double zPos, const std::vector<RawCameraImage>& images, picojson::object& details);

    std::vector<Entity*> entitylist;
    
    void Results (ICameraResult* result, picojson::object& data);

private:
    
    std::vector<ICameraObserver*> cameraObservers;
};

#endif
