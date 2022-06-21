/**
 * @file sobel_filter.h
 *
 */

/*******************************************************************************
  * Includes
******************************************************************************/

#include<memory>
#include<vector>
#include "filter.h"
#include "image.h"

#ifndef SOBEL_H
#define SOBEL_H
using namespace std;

/**
 * @brief The class for the Sobel filter inheriting from the Filter class
 *
 */

class SobelFilter : public Filter {
    public:
        SobelFilter();

/**
* @brief The x and y kernels to be applied to the original image input
*/

        vector<vector<float>> SobelX{{-1.0,0.0,1}, 
                                     {-2.0,0.0,2.0}, 
                                     {-1.0,0.0,1.0}};
                                     
        vector<vector<float>> SobelY{{1.0,2.0,1.0},
                                     {0.0,0.0,0.0}, 
                                     {-1.0,-2.0,-1.0}};

/**
  * @brief Calls helper functions to produce two images and calculate the intensity and direction images
  *
  * @return Assigns the two produced images to the member variables
*/
        void Apply(vector<Image *> original, vector<Image *> filtered);

/**
  * @brief Applies a kernel to an image
*/
        void convolve(vector<Image *> img, vector<vector<float>> mat, Image* im);
/**
  * @brief Produces the intensity image
  *
  * @return Assigns the produced image to the member variable  
*/
        void intensity(Image* original);
/**
* @brief Produces the direction image
*
* @return Assigns the produced image to the member variable  
*/
        void direction(Image* original);

/**
* @brief gets the intensity image
*
* @return returns the intensity image
*/
        Image* getIntensity();

/**
* @brief gets the direction image
*
* @return returns the direction image
*/
        Image* getDirection();

    private:
        Image* Ix;
        Image* Iy;
        Image* directionim;
        Image* intensityim;
    
};

#endif
