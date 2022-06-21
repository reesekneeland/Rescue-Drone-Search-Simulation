/*! \mainpage Drone Simulation Index Page
 *
 * \section intro_sec Introduction
 *
 * Welcome to Team 36's Drone Rescue Simulation! The goal of the program is to help a drone rescue a robot in distress and bring it to a hospital!
 * Our program uses an object oriented class inheritance structure to facilitate
 * an EntityFactory creation scheme to create an Entity on the map, this system creates a Drone object within a representation of the 
 * University of Minnesota campus. A Graph structure is generated from the map of streets and intersections on the campus, 
 * which the drone will patrol in a depth first search methodology to find the robot
 * located on the map, it detects the Robot with a BlobDetect algorithm applied to an image the drone takes of its surroundings
 * once every five seconds. Once the Robot is located, the drone will beeline directly towards the robot and bring it to a hospital 
 * to be serviced. Further details about the functionality of our simulation can be found in the following documentation pages:
 * 
 * <a href="https://docs.google.com/document/d/1lFi3PZ3u55LxlNjxh80YxQtaFFYda6ydTmYzTDGp9bg/edit?usp=sharing">Detailed Overview</a> 

 * <a href="https://docs.google.com/document/d/1fPoumZ7JcPbe8ovgh7w-G1xEea_-aNKeFjvmU1oWn0M/edit?usp=sharing">Getting Started</a>
 * 
 * <a href="https://docs.google.com/document/d/1oxC_KbgaFSl3jn4MMn7DL5g3o9HFydJgXHuiBxrYoME/edit?usp=sharing">How to Contribute</a>
 * 
 * <a href="https://docs.google.com/document/d/1wlaAKFXaprftbdKIy56xEib1An6BuCWhlE3n_XZcl7M/edit?usp=sharing">Simulation Specification</a> 
 * 
 * <a href="https://docs.google.com/document/d/1-Dwys-zjBca37Uw8eR266Y5FY0IfjslAj65-jTg5UUA/edit?usp=sharing">Image Processing Specification</a>
 * 
 *
 */