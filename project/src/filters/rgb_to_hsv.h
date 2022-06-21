#ifndef RGB_TO_HSV_H_
#define RGB_TO_HSV_H_
#include "filter.h"
#include <algorithm>
#include <cmath>

class RgbToHsv: public Filter{
public: 
    /**
     * @brief default constuctor of RgbToHsv
     * 
     * 
     */
    RgbToHsv();
    /**
     * @brief turns a rgb image to a hsv image
     * 
     * @param original vector containing the original image
     * @param filtered vector that will contain the hsv image
     * 
     */
    void Apply(std::vector<Image*> original,std::vector<Image*>filtered);
};


#endif//RGB_TO_HSV_H_
