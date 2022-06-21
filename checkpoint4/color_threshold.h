#ifndef COLOR_THRESHOLD_H_
#define COLOR_THRESHOLD_H_
#include "filter.h"
class ColorThreshold : public Filter{
public: 
    ColorThreshold();
    bool isStrong(unsigned char* pixel);
    void Apply(std::vector<Image*> original,std::vector<Image*>filtered);
};
#endif//COLOR_THRESHOLD_H_