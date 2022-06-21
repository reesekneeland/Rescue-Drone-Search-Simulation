 #include "csvuser.h"

void CSVUser::DoSomething(double speed, double x, double y, double z){
    std::vector<double> vec1{speed};
    std::vector<double> vec2{x};
    std::vector<double> vec3{y};
    std::vector<double> vec4{z};
    
    // Wrap into a vector
    std::vector<std::pair<std::string, std::vector<double>>> vals = {{"Ending Speed", vec1}, {"Ending X Coordinate", vec2}, {"Ending Y Coordinate", vec3}, {"Ending Z Coordinate", vec4}};

    CSVSingleton::Instance()->Create(vals);
    };