/**
* @file RobotFactory.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "RobotFactory.h"

// Creates and populates a new object by parsing the picoJson
Entity* RobotFactory::Factory(picojson::object& entityData, ICameraController& cameraController){
    double robotid = entityData["entityId"].get<double>();

    this->robot = new Robot(robotid);

    if(entityData["position"].is<picojson::array>()){
    picojson::array position = entityData["position"].get<picojson::array>();
    robot->SetPos(position[0].get<double>(), position[1].get<double>(),position[2].get<double>());
    std::cout<<"ROBOT ACTUAL POSITION IS: "<<position[0].get<double>()<<","<<position[1].get<double>()<<","<<position[2].get<double>()<<std::endl;
    }
    // Get the direction as an array
    if(entityData["direction"].is<picojson::array>()){
    picojson::array dir = entityData["direction"].get<picojson::array>();
    robot->SetDir(dir[0].get<double>(), dir[1].get<double>(),dir[2].get<double>());
    }


    if(entityData["cameras"].is<picojson::array>()){
    picojson::array cameras = entityData["cameras"].get<picojson::array>();
    for (int i = 0; i < cameras.size(); i++) {
        Camera* camera = new Camera(cameras[i].get<double>(), &cameraController);
        robot->AddCam(camera);
        }
    }
     // returns the created entity
    return robot;
}
