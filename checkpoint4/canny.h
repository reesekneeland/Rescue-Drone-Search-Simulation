/**
 * @file canny.h
 *
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include<memory>
#include<vector>
#include "filter.h"
#include "double_threshold_filter.h"
#include "gaussian_blur_filter.h"
#include "greyscale_filter.h"
#include "sobel_filter.h"
#include "nonmax_filter.h"
#include "hysteresis_filter.h"
#include "image.h"
#ifndef CANNY_H
#define CANNY_H

using namespace std;

/**
 * @brief The class for the Canny filter inheriting from the Filter class. 
 *
 */

class Canny : public Filter {
    public:
        Canny();
        

/**
 * @brief The function for the Canny filter which applies all other filters to the input images 
 *
 */
        void Apply(vector<Image *> original, vector<Image *> filtered);

    private:
        
    
};

#endif