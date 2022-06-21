/**
 * @file greyscale_filter.h
 *
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include<memory>
#include<vector>
#include "filter.h"
#include "image.h"
#ifndef GREYSCALEFILTER_H_
#define GREYSCALEFILTER_H_

using namespace std;

/**
 * @brief The class for the Greyscale filter inheriting from the Filter class. 
 *
 */

class GreyScaleFilter : public Filter {
    public:
        GreyScaleFilter();
        
        void Apply(vector<Image *> original, vector<Image *> filtered);

    private:
        
    
};

#endif
