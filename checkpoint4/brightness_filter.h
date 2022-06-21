#ifndef BRIGHTNESS_H_
#define BRIGHTNESS_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "filter.h"
#include <algorithm>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief a brightness filter class that inherits apply function from Filter class
 *
 */
class BrightnessFilter : public Filter { 
public: 
/**
  * @brief Brightness filter constructor that initilizes brightness variable between -255 to 255
  *
  * @return construction of a brightness filter
  */ 
    BrightnessFilter(int bright);
/**
  * @brief Function that ensures the color value is between 0 to 255
  *
  * @return returns the color value converted to value between 0 to 255
  */
    int truncate(int color);
/**
  * @brief Application filter that applies a brightness filter given image vector
  *
  * @return has a return parameter that is filled with the filtered pixels
  */
    void Apply(std::vector<Image*> original,std::vector<Image*> filtered);
private: 
/**
  * @brief Brightness value between -255 to 255
  *
  */
    int bright;
};
#endif//BRIGHTNESS_H_
