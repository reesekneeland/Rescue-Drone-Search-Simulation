#include "filter.h"
#ifndef CANNY_H_
#define CANNY_H_
class Canny : public Filter{
    public:
     /**
         * @brief apply a canny filter on the image passed in.
         * 
         * @param original vector containing the original images
         * @param filtered vector that will contain the new canny edge detected version of the old image
         */
    void Apply(std::vector<Image*> original, std::vector<Image*> filtered);
};
#endif