#include "graph.h"

using namespace std;

Graph::Graph(string node){
    //JSON PARSING FOR NODES.JSON
    ifstream nodes("nodes.json");
    stringstream buf;
    buf << nodes.rdbuf();
    string json = buf.str();
    picojson::value v;
    string err = picojson::parse(v, json);
    if (!err.empty()) {
        std:cerr << err << endl;
    }

    if (v.is<picojson::array>()) {
        picojson::array arr = v.get<picojson::array>();
        int prefix = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].is<picojson::object>()) {
                picojson::object o = arr[i].get<picojson::object>();
                for (picojson::object::const_iterator it = o.begin(); it != o.end(); it++) {
                    // can uncomment for printed visualization of data
                    // cout << prefix << " " << it->first << ": " << it->second << endl;
                    picojson::object pos = it->second.get<picojson::object>();
                    picojson::object::const_iterator it2 = pos.begin();
                    picojson::object coords = it2->second.get<picojson::object>();
                    vector<double> coordArr;
                    int i=0;
                    for (picojson::object::const_iterator it3 = coords.begin(); it3 != coords.end(); it3++) {    
                        string coord = picojson::value(it3->second).serialize();
                        coordArr.push_back((1.4 * atof(coord.c_str()))/20.0);
                        i++;
                    }
                    prefix++;
                    if((coordArr[0] > -110.0) && (coordArr[0] < 115.0) && (coordArr[2] > -60.0) && (coordArr[2] < 65)){
                        positions[it->first] = coordArr;
                    }
                    else{
                        deleted[it->first] = true;
                    }
                    
                }
            }
        }
    } else {
        printf("value is not an array\n");
    }
    //JSON PARSING FOR EDGES.JSON
    ifstream edges("edges.json");
    stringstream buf2;
    buf2 << edges.rdbuf();
    string json2 = buf2.str();
    picojson::value v2;
    string err2 = picojson::parse(v2, json2);
    if (!err2.empty()) {
        cerr << err2 << endl;
    }

    if (v.is<picojson::array>()) {
        picojson::array arr2 = v2.get<picojson::array>();
        int prefix = 0;
        for (int i = 0; i < arr2.size(); i++) {
            if (arr2[i].is<picojson::object>()) {
                picojson::object o = arr2[i].get<picojson::object>();
                for (picojson::object::const_iterator it = o.begin(); it != o.end(); it++) {
                    // can uncomment for printed visualization of data
                    // cout << prefix << " " << it->first << ": " << it->second << endl;
                    auto deletedCheck2 = deleted.find(it->first);
                    if (deletedCheck2 == deleted.end()){
                        picojson::array edge = it->second.get<picojson::array>();
                        prefix++;
                        vector<string> adjList;
                        for(int i = 0; i < edge.size(); i++){
                            string nodeStr = edge[i].serialize();
                            auto deletedCheck = deleted.find(nodeStr.substr(1, nodeStr.size()-2));
                            if (deletedCheck == deleted.end()){
                                adjList.push_back(nodeStr.substr(1, nodeStr.size()-2));
                            }
                        }
                        adjacency[it->first] = adjList;
                    }
                }
            } else {
                printf("array value is not a picojson::object\n");
            }
        }
    } else {
        printf("value is not an array\n");
    }
    // Mark all the vertices as not visited
    visited.clear();
 
    // Mark the current node as visited and enqueue it
    visited[node] = true;
    queue.push_back(node);
    visitedNodes = 0;
    returnedNodes = 0;
}

Graph::~Graph() {
    // Delete dynamically allocated variables
    positions.clear();
    adjacency.clear();
    queue.clear();
    visited.clear();
    
}

std::vector<double> Graph::GetPos(string node){
    auto it = positions.find(node);
    if (it == positions.end()) {
        cout << node << " not found: " << endl;
        throw runtime_error("Node not found");
    }
    // If key found then iterator to that key is returned
    return it->second;
    
}

double Graph::GetDist(string start, string end){
    std::vector<double> startpos;
    std::vector<double> endpos;
    auto it = positions.find(start);
    if (it == positions.end()) {
        cout << start << " not found" << endl;
        throw std::runtime_error("NODE NOT FOUND");
    }
    // If key found then iterator to that key is returned 
    else{
        startpos = it->second;
    }
    auto it2 = positions.find(end);
    if (it2 == positions.end()) {
        cout << end << " not found" << endl; 
        throw std::runtime_error("NODE NOT FOUND");
    }
    // If key found then iterator to that key is returned 
    else{
        endpos = it2->second;
    }
    double xdist = endpos[0] - startpos[0];
    double zdist = endpos[2] - startpos[2];
    return sqrt(pow(xdist, 2) + pow(zdist, 2));
}

bool Graph::CheckNode(string node){
    bool retVal = true;
    for(int i=0; i<visitedList.size(); i++){
        if(GetDist(node, visitedList[i])<2.5){
            retVal=false;
            break;
        }
    }
    return retVal;

}

string Graph::VisitNode(string node){
    if(node == queue.front()){
            visitedNodes++;
            visitedList.push_front(node);
            queue.pop_front();
            
            // Get all adjacent vertices of the dequeued
            // vertex node. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            auto it = adjacency.find(node);
            if (it == adjacency.end()) {
                cout << node << "adjacency not found" << endl; 
            }
            // If key found then iterator to that key is returned 
            else{
                for(int i=0; i<it->second.size(); i++){
                    string curNode = it->second[i];
                    auto vistedCheck = visited.find(curNode);
                    if (vistedCheck == visited.end()){
                        visited[curNode] = true;
                        queue.push_front(curNode);
                    }
                }
            } 
    }
    else{
        cout << "VISITED THE WRONG NODE, EXITING" << endl;
        throw std::runtime_error("VISTED THE WRONG NODE< EXITING");
    }
    
    if(CheckNode(queue.front())){
        returnedNodes++;
        return queue.front();
    }
    else{
        return VisitNode(queue.front());
    }
}