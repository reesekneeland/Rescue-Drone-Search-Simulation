/**
* @file robot.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

#define _USE_MATH_DEFINES
#include "robot.h"

Robot::Robot(const double& id) : id(id){ 
    // Drones have 3 components x,y,z
    position = {0,0,0};
    //velocity = {0,0,0};
    direction = {0,0,0};
}

Robot::~Robot(){
    position.clear();
    direction.clear();
    for (int x =0; x< cams.size(); x++){
        delete cams[x];
    }
}

void Robot::SetPos(double x, double y, double z){
    this->position = {x,y,z};
}

void Robot::SetDir(double x, double y, double z){
    this->direction = {x,y,z};
}

void Robot::AddCam(Camera* camera){
    this->cams.push_back(camera);
}

void Robot::Update(double dt) {

       // Take a picture every 5 seconds with front camera
       time += dt;
       if (time-lastPictureTime > 5.0) {
           cams[0]->TakePicture();
           lastPictureTime = time;
       }
    }

void Robot::printPos(std::vector<double> pos){
    std::cout << ", " << pos[0] << ", " << pos[1] << ", " << pos[2] << std::endl;
}
