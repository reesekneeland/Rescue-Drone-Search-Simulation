/**
 * @file gaussian_blur_filter.h
 *
 */

/*******************************************************************************
  * Includes
******************************************************************************/

#include<memory>
#include<vector>
#include "filter.h"
#include "image.h"

#ifndef GAUSSIANBLURFILTER_H_
#define GAUSSIANBLURFILTER_H_

using namespace std;

/**
 * @brief The class for the Gaussian Blur filter inheriting from the Filter class
 *
 */

class GaussianBlurFilter : public Filter {
    public:
        GaussianBlurFilter();
/**
  * @brief Generates and implements a gaussian kernel to set every pixel equal to the average
  * values of the surrounding pixels in a 5x5 grid, weighted by the gaussian kernel. This applies
  * a gaussian blur effect.
  *
  * @return Assigns the filtered array to the output image.
*/
        void Apply(vector<Image *> original, vector<Image *> filtered);

    private:
        
    
};

#endif
