#define _USE_MATH_DEFINES
#include "filter.h"
#ifndef NON_MAX_H_
#define NON_MAX_H_

/** @class NonMaxFilter
 * @brief Applies NonMaxFilter to Intensity Image produced by Sobel
 * 
 * This Filter takes in 2 Matrices: The intensity matrix and the direction matrix.
 * Both Matrices are produced from the Sobel filter and are organized as floating
 * point matrices that represent the unsigned character arrays. This filter 
 * accesses the direction matrix, converts the radian value to an angle/degree value,
 * and finds which direction of neighboring pixels that will be used. The neighboring pixels'
 * intensity values are compared with that of the current pixel we are investigating and if
 * one of the neighboring pixel's values are greater then the current pixel is set to 0 (or black).
 * This is repeated for all pixels, and the resulting image is a smoother and thinner
 * representation of the original intensity image.
 * The algorithm I used to calculate the output suppression image is found at 
 * https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
 */
class NonMaxFilter: public Filter{

    public:
        /** @brief Method inherited from filter.h
         * This method simply calls Suppress down below but first loops through the vector 
         * "original" to extract the images from sobel and calls suppress with these images. 
         * From here it sets the "filtered" vector to the ouput image from supppress.
         */
        void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

    private:
        /** @brief This method does all of the gut work. It loops through the length and width
         * of the intensity image and gets the pixel at each index. It also gets the direction
         * calculated from sobel and compares the appropriate neighbors with the current pixel.
         * Sets the current pixel accordingly and the final image is sent back to Apply.
         */
        Image Suppress(Image intensity, Image direction);

        /** @brief This method is a helper for converting the radians found in the direction matrix
         * to degrees for simplicity sake when calculating the appropriate neighboring pixels.
         */
        float RadtoDeg(float rad);
};
#endif