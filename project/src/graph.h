/**
* @file graph.h
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <memory>
#include <vector>
#include <fstream>
#include "web_app.h"
#include <fstream>
#include "util/base64.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <unordered_map> 
#include <math.h>
#include <vector>

#ifndef GRAPH_H_
#define GRAPH_H_

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class to represent the graph model of the map, facilitates search algorithms
 * through an adjacency list and a priority queue.
 */

class Graph{
    public:
        Graph(string node);

        ~Graph();
        /**
        * @brief Gets the position of the provided node by checking for its coordinates
        * in the unorderded position map.
        * 
        * @param node A string representing the node ID to check.
        *
        * @return A vector of doubles representing nodes position in 3d space.
        */
        vector<double> GetPos(string node);
        /**
        * @brief Gets the Euclidean distance between two nodes.
        *
        * @param start A string representing the node ID of the starting node for the distance calculation.
        *
        * @param end A string representing the node ID of the ending node for the distance calculation.
        *
        * @return A double representing the Euclidean distance between the nodes.
        */
        double GetDist(string start, string end);
        /**
        * @brief marks the given node as visited, queues up all adjacent nodes, 
        * and returns the next node in the queue. This is the backbone of the graph class
        * that facilitates the breadth first search algorithm.
        *
        * @param node A string representing the node ID of the visted node, which is then
        * popped off the queue. All nodes adjacent to his node are then added to the priority queue.
        *
        * @return A string representing the next node in the priority queue to be visited next.
        */
        string VisitNode(string node);

        /**
        * @brief Checks to see if the given node is close to a previously visted coordinate, 
        * if it is, prune the node from the queue.
        *
        * @param node A string representing the node ID of the node being checked.
        *
        * @return A bool representing whether the node is safe to visit.
        */
        bool CheckNode(string node);

        int visitedNodes;
        int returnedNodes;

    private:
        /**
        * @brief An ordered map storing the positions of all nodes as a key value pair, 
        * with the key being the string containing a node ID and the value being a vector of doubles
        * representing the position of the node in 3d space.
        */
        unordered_map<string, std::vector<double>> positions;
        /**
        * @brief An ordered map storing the adjacency list of the graph as key value pairs,
        * with the key being the string containing a node ID and the value being a vector of strings
        * containing the IDs of all adjacent nodes.
        */
        unordered_map<string, std::vector<string>> adjacency; 
        /**
        * @brief A dynamic deque representing a priority queue storing the list of nodes to be visted next.
        */
        std::deque<string> queue;
        /**
        * @brief An ordered map storing all visited nodes as a key value pair, 
        * with the key being the string containing a node ID and the value being a boolean
        * value that is always set to true. A node has not been visited if it is not in the map.
        */
        unordered_map<string, bool> visited; 
        /**
        * @brief A deque of coordinates the drone has visited, used to check if a new node is very
        * close to a previously visited node, as to be able to ignore it.
        */
        std::deque<string> visitedList;
        /**
        * @brief An ordered map storing all deleted nodes as a key value pair, 
        * with the key being the string containing a node ID and the value being a boolean
        * value that is always set to true. A node has been deleted because it is outside the map.
        */
        unordered_map<string, bool> deleted; 

    
};

#endif
