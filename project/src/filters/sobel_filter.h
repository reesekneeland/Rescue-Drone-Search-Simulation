#include "filter.h"
#ifndef SOBEL_H_
#define SOBEL_H_

/** @class SobelFilter
 * @brief Applies SobelFilter to output of gaussian-blur
 * 
 * This filter takes in the output image of gaussian-blur and applies 2 kernels to it one-by-one
 * to find the intensity of the image in the x and y directions. From here it calculates the total
 * intensity from x and y by calculating the hypotenuse and storing the float value (since many
 * of these values are greater than 255 or less than 0) in a new Matrix and returns it. This filter
 * also calculates a direction matrix by finding the arctangent of the y pixel values divided by 
 * the x pixel values. In summary, this filter takes in a single image and outputs 2 matrices made 
 * up by floating point values that are later converted back into a single image by non-max-suppression
 * 
 * The algorithm I used to calculate the output matrices is found at 
 * https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
 * 
 * I also used supporting material from the links below
 * https://justin-liang.com/tutorials/canny/
 * https://setosa.io/ev/image-kernels/
 */
class SobelFilter: public Filter{

    public:
        /** @brief Method inherited from filter.h
         * This method extracts the image that was calculated by the gaussian-blur stored within
         * the "original" vector and passes it into Kernalize with the x and y kernels. Kernelize
         * returns 2 matrices of floating point values. These 2 matrices are passed into Intensity
         * and Direction and the resulting 2 matrices (direction and intensity) are stored in filtered.
         */
        void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

    private:
        /** @brief This method takes in the original image and a kernel. It is called twice in Apply
         * in order to generate a matrix for the x intensity and a matrix for the y intensity.
         * It loops through the image pixels and takes the sum of the product of the kernel and all
         * of the surrounding pixels and assigns this sum to a floating value that is stored in the
         * resulting matrix.
         */
        Image Kernelize(Image *original, int *kernel);

        /** @brief This method takes in the x and y intensity matrices calculated in kernelize and
         * finds the hypotenuse value between them by taking the square root of the sum of the 
         * squares of x and y. The resulting square root value is assigned to another floating point value
         * and is set in the new matrix that will be used in non-max-suppression later.
         */
        Image Intensity(Image ximage, Image yimage);

        /** @brief This method takes in the x and y intensity matrices calculated in kernelize and
         * finds the arctangent of the y intensity value divided by the x intensity value. This output
         * is set to a floating point value and is returned as the direction matrix which is also
         * later used in the non-max-suppression filter.
         */
        Image Direction(Image ximage, Image yimage);

};
#endif
