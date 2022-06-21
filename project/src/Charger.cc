/**
* @file Charger.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

#define _USE_MATH_DEFINES
#include "Charger.h"

// Drones have 3 components x,y,z
Charger::Charger(const double& id) : id(id){ 
    position = {0,0,0};
}

// Destructor
Charger::~Charger(){
    position.clear();

    // Deletes allocated memory for camera list
    for (int x =0; x< cams.size(); x++){
        delete cams[x];
    }
}

void Charger::SetPos(double x, double y, double z){
    this->position = {x,y,z};
}

void Charger::AddCam(Camera* camera){
    this->cams.push_back(camera);
}

void Charger::Update(double dt) {

       // Takes a picture every 5 seconds with front camera
       time += dt;
       if (time-lastPictureTime > 5.0) {
           cams[0]->TakePicture();
           lastPictureTime = time;
       }
    }

void Charger::printPos(std::vector<double> pos){
    std::cout << ", " << pos[0] << ", " << pos[1] << ", " << pos[2] << std::endl;
}
