/**
* @file ChargerFactory.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ChargerFactory.h"

// Creates and populates a new object by parsing the picoJson
Entity* ChargerFactory::Factory(picojson::object& entityData, ICameraController& cameraController){
    double chargerid = entityData["entityId"].get<double>();

    this->charger = new Charger(chargerid);

    if(entityData["position"].is<picojson::array>()){
    picojson::array position = entityData["position"].get<picojson::array>();
    charger->SetPos(position[0].get<double>(), position[1].get<double>(),position[2].get<double>());
    }

    if(entityData["cameras"].is<picojson::array>()){
    picojson::array cameras = entityData["cameras"].get<picojson::array>();
    for (int i = 0; i < cameras.size(); i++) {
        Camera* camera = new Camera(cameras[i].get<double>(), &cameraController);
        charger->AddCam(camera);
        }
    }
    // returns the created entity
    return charger;
}
