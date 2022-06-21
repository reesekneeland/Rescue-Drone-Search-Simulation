#include "filter.h"
#ifndef GREY_H_
#define GREY_H_
class GreyScaleFilter: public Filter{
    public:

        /**
         * @brief applies a greyscale filter on the image passed in.
         * 
         * @param original vector containing the original images
         * @param filtered vector that will contain the new greyscaled verson of the old image
         */

        void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

};
#endif