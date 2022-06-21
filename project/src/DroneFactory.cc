/**
* @file DroneFactory.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
******************************************************************************/

#include "DroneFactory.h"

// Creates and populates a new object by parsing the picoJson
Entity* DroneFactory::Factory(picojson::object& entityData, ICameraController& cameraController){
    double droneid = entityData["entityId"].get<double>();

    this->drone = new Drone(droneid);
    
    if(entityData["speed"].is<double>()){
        drone->SetSpeed(entityData["speed"].get<double>());
    }

    if(entityData["position"].is<picojson::array>()){
    picojson::array position = entityData["position"].get<picojson::array>();
    drone->SetPos(position[0].get<double>(), position[1].get<double>(),position[2].get<double>());
    }
    // Get the direction as an array
    if(entityData["direction"].is<picojson::array>()){
    picojson::array dir = entityData["direction"].get<picojson::array>();
    drone->SetDir(dir[0].get<double>(), dir[1].get<double>(),dir[2].get<double>());
    }


    if(entityData["cameras"].is<picojson::array>()){
    picojson::array cameras = entityData["cameras"].get<picojson::array>();
    for (int i = 0; i < cameras.size(); i++) {
        int id = cameras[i].get<double>();
        Camera* camera = new Camera(id, &cameraController);
        drone->AddCam(camera);
        }
    }
    
    // returns the created entity
    return this->drone;
}
