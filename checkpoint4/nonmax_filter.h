/**
 * @file nonmax_filter.h
 *
 */

/*******************************************************************************
  * Includes
******************************************************************************/

#include<memory>
#include<vector>
#include "filter.h"
#include "image.h"
#ifndef NONMAXFILTER_H_
#define NONMAXFILTER_H_

using namespace std;

/**
 * @brief The class for the NonMax filter inheriting from the Filter class
 *
 */

class NonMaxFilter : public Filter {
    public:
        NonMaxFilter();
/**
  * @brief Implements the sobel filter to produce two images representing a direction
  * map and an intensity map and calculates the pixel of highest intensity along every edge.
  * It then sets every nonmaximum pixel intensity to zero and returns the image inside the
  * filtered image vector passed into the method.
  \param original a vector of image objects containing the input image(s)

  \param filtered a vector of image objects containing the output image(s) with the nonmax filter applied.
*/
        void Apply(vector<Image *> original, vector<Image *> filtered);

    private:
        
    
};

#endif
