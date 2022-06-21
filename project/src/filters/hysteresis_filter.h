#include "filter.h"

#ifndef HYSTERESIS_H_
#define HYSTERESIS_H_
//https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123 
//source for psuedo code to apply.
class HysteresisFilter : public Filter{
    private:
        const int STRONG = 255;//strong pixel value
        const int WEAK = 25;//weak pixel value
    public:
        /**
         * @brief applies a hysteresis filter to the original image and saves the final result in filtered
         * @param original is a vector that holds a pointer to the original image, filtered is a vector that points to the result image 
         * of apply.
         */
        void Apply(std::vector<Image*> original,std::vector<Image*> filtered);
};

#endif