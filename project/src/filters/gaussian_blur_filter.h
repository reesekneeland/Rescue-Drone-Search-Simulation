#define _USE_MATH_DEFINES
#include "image.h"
#include "filter.h"
#include <cmath>
#include <iomanip>
#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

class GaussianBlurFilter: public Filter{
    private:
        std::vector<std::vector<double>> kernel;//kernel that will contain weights that will alter pixel values represented as a matrix.
        int kernelSize = 5; //size of the dimensions of a kernel by default it is a 5x5 matrix.
    public:
        /**
         * @brief applies a gaussian blur on an image
         * 
         */
        void Apply(std::vector<Image*> original,std::vector<Image*> filtered);

        /**
         * @brief Construct a new Gaussian Blur Filter object with default kernel of size 5 and sigma value of 1.
         * 
         */
        GaussianBlurFilter();
        
        /**
         * @brief Construct a new Gaussian Blur Filter object 
         * 
         * @param size kernel's size
         * @param sigma sigma value to determine the strength of the blur
         */
        GaussianBlurFilter(int size, double sigma);
        
        /**
         * @brief Destroy the Gaussian Blur Filter object and clears out the kernel vector.
         * 
         */
        ~GaussianBlurFilter();
};
#endif