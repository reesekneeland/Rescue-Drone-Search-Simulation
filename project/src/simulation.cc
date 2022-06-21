/**
* @file simulation.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

#include "simulation.h"

Simulation::Simulation(){}

Simulation::~Simulation(){
    for (int x =0; x<entitylist.size();x++){
        std::cout<<"deleting entity"<<std::endl;
        delete entitylist[x];
    }
}

    void Simulation::Update(double dt){
    }
    void Simulation::CreateEntity(picojson::object& entityData, ICameraController& cameraController){
       // Creates an entity based on JSON data stored as an object.
        if (entityData["name"].get<std::string>().find("drone") != std::string::npos) {
            DroneFactory factory = DroneFactory();
            Entity* entity = factory.Factory(entityData, cameraController);
            entitylist.push_back(entity);
        }

          if (entityData["name"].get<std::string>().find("robot") != std::string::npos) {
            RobotFactory factory = RobotFactory();
            Entity* entity = factory.Factory(entityData, cameraController);
            entitylist.push_back(entity);
        }
          if (entityData["name"].get<std::string>().find("recharge station") != std::string::npos) {
            ChargerFactory factory = ChargerFactory();
            entitylist.push_back(factory.Factory(entityData, cameraController));
        }
    }
        
      void Simulation::FinishUpdate(picojson::object& returnValue){
      }


void Simulation::AddObserver(ICameraObserver& observer) {
    cameraObservers.push_back(&observer);
}

void Simulation::RemoveObserver(ICameraObserver& observer) {
    cameraObservers.erase(std::remove(cameraObservers.begin(), cameraObservers.end(), &observer), cameraObservers.end()); 
}

void Simulation::TakePicture(int cameraId) {
    // std::cout<<"CAM ID: "<<(double)cameraId<<std::endl;
    picojson::object obj;
    picojson::value val;
    obj["takePicture"] = picojson::value((double)cameraId);
    picojson::value v(obj);
    sendJSON(v);
}

void Simulation::Results (ICameraResult* result, picojson::object& data){
    Camera::CameraResult& res = *static_cast<Camera::CameraResult*>(result);
    if(res.found) {
        std::cout<<"FOUND"<<std::endl;
            Drone* drone = dynamic_cast<Drone*>(entitylist[0]);
            std::cout<<entitylist.size()<<std::endl;
            std::cout<<"found correct entity"<<std::endl;
            std::vector<double> vec = {res.pos[0],res.pos[1],res.pos[2]} ;
            drone->SetTarget(vec);
            
            std::cout<<"robot found at: "<<res.pos[0]<<","<<res.pos[1]<<","<<res.pos[2]<<std::endl;
            drone->SetPatrol(false);
                // std::vector<double> vec = {res.pos[0],res.pos[1],res.pos[2]} ;
                // drone->SetTarget(vec);
            }

}