#ifndef COLOR_THRESHOLD_H_
#define COLOR_THRESHOLD_H_
#include "filter.h"
#include "blob_detect.h"
class ColorThreshold : public Filter{
public: 
    /**
     * @brief default constuctor for color threshold
     * 
     * 
     */
    ColorThreshold();
    /**
     * @brief Function that checks given pixel is the pixel of the robot
     * 
     * @param pixel is the pixel picked from the hsv image
     * 
     */
    bool isStrong(unsigned char* pixel);
    /**
     * @brief turns a hsv image to a image that replaces the robot with white strong pixels
     * 
     * @param original vector containing the hsv image
     * @param filtered vector that will contain color thresholded image
     * 
     */
    void Apply(std::vector<Image*> original,std::vector<Image*>filtered);

    int blobPxlCount;
};
#endif//COLOR_THRESHOLD_H_