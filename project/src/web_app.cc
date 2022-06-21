#include "web_app.h"
#include <fstream>
#include "util/base64.h"
#include "entityFactory.h"
#include "simulation.h"
#include "csvsingleton.h"
#include "csvuser.h"
#include "drone.h"
//*****************************************************************************************
// Edit the following functions to suit your needs.  Do most of the work inside the
// simulation facade and not here.  The primary purpositione of these functions are to
// communicate with the UI.
//*****************************************************************************************


Simulation Sim;
void WebApp::CreateEntity(picojson::object& entityData, ICameraController& cameraController) {
    // Creates an entity based on JSON data stored as an object.

    // Print out actual json:
    picojson::value val(entityData);
    std::cout << val.serialize() << std::endl;
    Sim.CreateEntity(entityData,cameraController);

}

void WebApp::Update(double dt) {
    std::vector<Entity*> entitylist = Sim.getEntities();
    for(int i = 0; i < entitylist.size(); i++){
        Drone* drone = dynamic_cast<Drone*>(entitylist[i]);
        if(drone != NULL)
        {
            bool flag = true;
            if((IsKeyDown("ArrowRight")) || (IsKeyDown("ArrowLeft")) || 
            (IsKeyDown("w")) ||(IsKeyDown("s")) ||
            (IsKeyDown("ArrowUp")) ||(IsKeyDown("ArrowDown")) ||
            (IsKeyDown("a")) || (IsKeyDown("d")) ||
            (IsKeyDown("j")) || (IsKeyDown("k")))
            {
                drone->SetJoystick(
                IsKeyDown("ArrowRight") ? 1 : (IsKeyDown("ArrowLeft") ? -1 : 0),
                IsKeyDown("w") ? 1 : (IsKeyDown("s") ? -1 : 0),
                IsKeyDown("ArrowUp") ? -1 : (IsKeyDown("ArrowDown") ? 1 : 0),
                IsKeyDown("a") ? 1 : (IsKeyDown("d") ? -1 : 0),
                IsKeyDown("j") ? 1 : (IsKeyDown("k") ? -1 : 0));
                drone->Update(dt, flag);
            }
            else
            {
                flag = false;
                drone->Update(dt, flag);
            }
        }
    }
}

void WebApp::FinishUpdate(picojson::object& returnValue) {
    picojson::object entity;
    entity["entityId"] = picojson::value((double)0);
    std::vector<Entity*> entitylist = Sim.getEntities();
    for(int i = 0; i < entitylist.size(); i++){
        Drone* drone = dynamic_cast<Drone*>(entitylist[i]);
        if(drone != NULL)
        {
            // Save the positionition as an array
            picojson::array pos;
            pos.push_back(picojson::value(drone->GetPosX()));
            pos.push_back(picojson::value(drone->GetPosY()));
            pos.push_back(picojson::value(drone->GetPosZ()));
            entity["pos"] = picojson::value(pos);

            // Save the direction as an array
            picojson::array dir;
            dir.push_back(picojson::value(drone->GetDirX()));
            dir.push_back(picojson::value(drone->GetDirY()));
            dir.push_back(picojson::value(drone->GetDirZ()));
            entity["dir"] = picojson::value(dir);

            counter = counter + 1;
            double speed = drone->GetSpeed();
            double x = drone->GetPosX();
            double y = drone->GetPosY();
            double z = drone->GetPosZ();
            if(counter % 250 == 0)
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
        }
    returnValue["entity0"] = picojson::value(entity);
    }
}







//*****************************************************************************************
// The code below you probably will not need to touch.  These are the functions 
// that will talk to the UI over web sockets.
//*****************************************************************************************

WebApp::WebApp() : start(std::chrono::system_clock::now()), time(0.0), running(true) {
    imageProcessThread = new std::thread(&WebApp::ProcessImageQueue, this);
    counter = 0;
}

WebApp::~WebApp() {
    running = false;
    imageProcessCond.notify_all();
    imageProcessThread->join();
    std::cout << "destroying imageprocessthread \n" << std::endl;
    delete imageProcessThread;
}

void WebApp::receiveJSON(picojson::value& val) {
    picojson::object data = val.get<picojson::object>();
    std::string cmd = data["command"].get<std::string>();
    picojson::object returnValue;
    returnValue["id"] = data["id"];
    ReceiveCommand(cmd, data, returnValue);
    picojson::value retVal(returnValue);
    sendJSON(retVal);
}

void WebApp::ReceiveCommand(const std::string& cmd, picojson::object& data, picojson::object& returnValue) {
    if (cmd == "image") {
        std::unique_lock<std::mutex> lock(imageProcessMutex);
        data["time"].set<double>(time);
        imageQueue.push(data);
        imageProcessCond.notify_all();
        return;
    }


    std::unique_lock<std::mutex> updateLock(updateMutex);
    if (cmd == "createEntity") {
        CreateEntity(data, *this);
    } 
    else if (cmd == "update") {
        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        double delta = diff.count() - time;
        time += delta;

        double simSpeed = data["simSpeed"].get<double>();
        delta *= simSpeed;

        if (delta > 0.1) {
            for (float f = 0.0; f < delta; f+=0.01) {
                Update(0.01);
            }
        }
        else {
            Update(delta);
        }
        FinishUpdate(returnValue);
    }
    else if (cmd == "keyup") {
        KeyUp(data["key"].get<std::string>(), data["keyCode"].get<double>());
    }
    else if (cmd == "keydown") {
        KeyDown(data["key"].get<std::string>(), data["keyCode"].get<double>());
    }
    else {
        std::cout << "Unknown command: " << cmd << " - " << picojson::value(data).serialize() << std::endl;
    }
}

void WebApp::KeyUp(const std::string& key, int keyCode) {
    keyValue[key] = 0;
}

void WebApp::KeyDown(const std::string& key, int keyCode) {
    keyValue[key] = 1;
}

bool WebApp::IsKeyDown(const std::string& key) {
    std::map<std::string,int>::iterator it = keyValue.find(key);
    if (it != keyValue.end()) {
        return it->second;
    } 

    return false;
}

void WebApp::TakePicture(int cameraId) {
    picojson::object obj;
    picojson::value val;
    obj["takePicture"] = picojson::value((double)cameraId);
    picojson::value v(obj);
    sendJSON(v);
}

void WebApp::ProcessImageQueue() {
    while (running) {
        std::unique_lock<std::mutex> lock(imageProcessMutex);
        if (imageQueue.size() > 0) {
            picojson::object data = imageQueue.front();
            imageQueue.pop();
            lock.unlock();

            std::vector<std::string> decodedImages;
            std::vector<RawCameraImage> imageData;

            const picojson::array& images = data["images"].get<picojson::array>();

            for (int i = 0; i < images.size(); i++) {
                std::string decoded = base64_decode(images[i].get<std::string>().substr(23));
                decodedImages.push_back(decoded);
                RawCameraImage rawImage;
                rawImage.data = reinterpret_cast<const unsigned char*>(decodedImages[i].c_str());
                rawImage.length = decoded.length();
                imageData.push_back(rawImage);
            }

            int cameraId = data["cameraId"].get<double>();
            const picojson::array& pos = data["position"].get<picojson::array>();

            for (int i = 0; i < cameraObservers.size(); i++) {
                ICameraResult* result = cameraObservers[i]->ProcessImages(
                    cameraId,
                    pos[0].get<double>(),
                    pos[1].get<double>(),
                    pos[2].get<double>(),
                    imageData,
                    data
                );
                if (result) {
                    Sim.Results(result,data);
                    std::unique_lock<std::mutex> updateLock(updateMutex);
                    cameraObservers[i]->ImageProcessingComplete(result);
                }
            }
        }
        else {
          imageProcessCond.wait(lock);
        }
    }
}

void WebApp::AddObserver(ICameraObserver& observer) {
    cameraObservers.push_back(&observer);
}

void WebApp::RemoveObserver(ICameraObserver& observer) {
    cameraObservers.erase(std::remove(cameraObservers.begin(), cameraObservers.end(), &observer), cameraObservers.end()); 
} 
