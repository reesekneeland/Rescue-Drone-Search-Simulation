/**
* @file drone.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

#include "drone.h"
#define _USE_MATH_DEFINES

Drone::Drone(const double& id) : id(id){
    // Drones have 3 components x,y,z
    position = {0,0,0};
    //velocity = {0,0,0};
    direction = {0,0,0};
    isPatrol = true;
    UmnGraph = new Graph("1719996961");
    SetTargetNode("1719996961");
    counter = 0;
    speed =0;
}

Drone::~Drone() {
    // Delete dynamically allocated variables
    position.clear();
    direction.clear();
    delete UmnGraph;
    for (int x =0; x< cams.size(); x++){
        delete cams[x];
    }
}

void Drone::SetSpeed(double speed){
    this->speed = speed;
}
void Drone::SetPos(double x, double y, double z){
    this->position = {x,y,z};
}
void Drone::SetDir(double x, double y, double z){
    this->direction = {x,y,z};
}
void Drone::SetPatrol(bool state){
    isPatrol = state;
}

void Drone::AddCam(Camera* camera){
    this->cams.push_back(camera);
}

void Drone::Update(double dt, bool flag) {
    counter = counter + 1;
    if(flag == true) // manual movement
    {
        // yaw 
        if(theta != 0)
        {
            double newx = direction[0]*std::cos(theta) - direction[1]*std::sin(theta);
            double newz = direction[0]*std::sin(theta) + direction[2]*std::cos(theta);
            direction[0] = newx;
            //std::cout << dir[0] << std::endl;
            direction[2] = newz;
            //std::cout << dir[2] << std::endl;
        }
        // pitch (already sort of implemented)
        if(phi != 0)
        {
            double newx = direction[0]*std::cos(phi) - direction[1]*std::sin(phi);
            double newy = direction[0]*std::sin(phi) + direction[1]*std::cos(phi);
            direction[0] = newx;
            //std::cout << dir[0] << std::endl;
            direction[1] = newy;
            //std::cout << dir[1] << std::endl;
        }
       for (int i = 0; i < 3; i++) {
           position[i] += speed*direction[i]*dt;
       }
    }
    else // patrol
    {
        //checks to see if its at the targetnode, if its not, then move the drone towards the target
        if(GetDist(position, targetPosition)>1.0){
            for (int i = 0; i < 3; i++) {
                    SetDirection();
                    position[i] += speed*direction[i]*dt;
                }
            }
        //checks to see if the patrol flag is enabled, if it is then we update the target to the
        //next node in the priority queue.
        else if(isPatrol){
            SetTargetNode(UmnGraph->VisitNode(targetNode));
        }
    }
       
       // Take a picture every 5 seconds with front camera
       time += dt;
       if (time-lastPictureTime > 5.0) {
           cams[0]->TakePicture();
           lastPictureTime = time;
       }
        double speed = this->speed;
        double x = this->GetPosX();
        double y = this->GetPosY();
        double z = this->GetPosZ();
        /*
        if(counter % 100 == 0)
        {
            sqlite3* DB;
            int exit = 0;
            exit = sqlite3_open("statistics.db", &DB);
            std::string query = "CREATE TABLE data("
                            "iteration INTEGER PRIMARY KEY NOT NULL, "
                            "speed REAL NOT NULL, "
                            "xpos REAL NOT NULL, "
                            "ypos REAL NOT NULL, "
                            "zpos REAL NOT NULL);";
            char* messageError;
            exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);
            CSVUser::DoSomething(speed, x, y, z);
            query = std::string("INSERT INTO data (speed, xpos, ypos, zpos)"
                    "VALUES(") + std::to_string(speed) + ", " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ");";
            exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);
            sqlite3_close(DB);
        }
        */
    }

void Drone::SetTargetNode(string node){
    targetNode = node;
    SetTarget(UmnGraph->GetPos(node));
    // cout << "TARGET" << targetPosition[0] << targetPosition[1] << targetPosition[2] << endl;
    // cout << "DIRECTION" << direction[0] << direction[1] << direction[2] << endl;
}

void Drone::UpdateTarget(string node){
    SetTargetNode(UmnGraph->VisitNode(node));
}

void Drone::SetTarget(std::vector<double> target){
    targetPosition = target;
}

double Drone::GetDist(std::vector<double> start, std::vector<double> end){
    std::vector<double> positionDifference;
    for(int i = 0; i< start.size(); i++){
        positionDifference.push_back(end[i]-start[i]); 
    }
    return(sqrt(pow(positionDifference[0], 2) + pow(positionDifference[2], 2)));
}

void Drone::SetDirection(){
    std::vector<double> positionDifference;
    for(int i = 0; i< targetPosition.size(); i++){
        positionDifference.push_back(targetPosition[i]-position[i]); 
    }
    double euclidDist = sqrt(pow(positionDifference[0], 2) + pow(positionDifference[2], 2));
            direction[0] = positionDifference[0]/euclidDist;
            // std::cout << direction[0] << std::endl;
            direction[2] = positionDifference[2]/euclidDist;;
            // std::cout << direction[2] << std::endl;
}

std::vector<double> Drone::GetTarget(){
    return targetPosition;
}

string Drone::GetTargetNode(){
    return targetNode;
}

void Drone::SetJoystick(double x, double y, double z, double a, double c) {
        direction[0] = x; direction[1] = y; direction[2] = z; theta = a; phi = c;
    }

void Drone::printPos(){
    std::cout << ", " << position[0] << ", " << position[1] << ", " << position[2] << std::endl;
}