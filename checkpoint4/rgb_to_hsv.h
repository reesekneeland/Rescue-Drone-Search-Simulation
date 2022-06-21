#ifndef RGB_TO_HSV_H_
#define RGB_TO_HSV_H_
#include "filter.h"
#include <algorithm>
#include <cmath>

class RgbToHsv: public Filter{
public: 
    RgbToHsv();
    void Apply(std::vector<Image*> original,std::vector<Image*>filtered);
};


#endif//RGB_TO_HSV_H_
