/**
 * @file hysteresis_filter.h
 *
 */

#ifndef HYSTERESIS_H_
#define HYSTERESIS_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "filter.h"
/**
 * @brief The class for Hysteresis filter inheriting apply function from Filter class
 *
 */
class HysteresisFilter : public Filter { 
public: 
/**
  * @brief Application of hysteresis filter given original image vector with an empty filtered vector
  *
  * @return does not return anything but assigns filtered image to the filtered vector
  */
    void Apply(std::vector<Image*> original,std::vector<Image*> filtered);
/**
  * @brief Checks of the pixel given is a strong pixel or not
  *
  * @return returns a boolean value that is true if pixel is strong
  */
    bool isStrong(unsigned char* pixel);
};
#endif//HYSTERESIS_H_
