/**
 * @file double_threshold_filter.h
 *
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include<memory>
#include<vector>
#include "filter.h"
#include "image.h"
#ifndef DOUBLE_THRESHOLD_FILTER_H_
#define DOUBLE_THRESHOLD_FILTER_H_

using namespace std;

class DoubleThresholdFilter : public Filter {
    public:
        /**
        * @brief Default constructor for Double Threshold Filter.
        * @param lowRatio The low threshold ratio.
        * @param highRatio The high threshold ratio.
        * @param weak What is considered a weak pixel
        * @param strong What is considered a strong pixel
        * @return Nothing.
        */
        DoubleThresholdFilter(float lowRatio, float highRatio, float weak, float strong);

        /**
        * @brief Apply the Double Threshold filter.
        * @param original The original image.
        * @param filtered The filtered image.
        * @return Nothing.
        */
        void Apply(vector<Image *> original, vector<Image *> filtered);

    private:
        float lowRatio;
        float highRatio;
        float strong;
        float weak;
    
};

#endif
