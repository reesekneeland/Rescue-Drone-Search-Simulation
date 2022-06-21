#ifndef DETECT_LOCATION_H_
#define DETECT_LOCATION_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "filters/image.h"
#include "filters/blob_detect.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief the main class for calculating Pixel location of the robot
 * 
 */
class DetectLocation{
public:
     /**
    * @brief Default constructor
    *
    */
    DetectLocation();
     /**
    * @brief Default destructor
    *
    */
    ~DetectLocation();
     /**
    * @brief Gets the X,Y coordinated of first white pixel in an image
    *
    * @param Image object 
    */
    void FindxyPxl(Image* image);
     /**
    * @brief Calculated DirectionVector,Direction and Distance given a pixel
    *
    * @param unsigned char pixel 
    */
    void DirCalc(unsigned char* pixel);

    double* DirVec;
    double* Direction;
    double Distance;
    int* xyPxl;

};

#endif//DETECT_LOCATION_H_