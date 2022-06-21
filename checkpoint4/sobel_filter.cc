
/**
 * @file sobel_filter.cc
 *
 */

/*******************************************************************************
  * Includes
******************************************************************************/

#include "sobel_filter.h"
#include <math.h>
#include <vector>

using namespace std;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief The Sobel Filter class for the application of this filter.
 *
 *  This filter class takes in one input image and applies an Xkernel and a Ykernel to the image to yield two seperate images.
 *  The hypotenuse of those images are then calculated to produce the intensity image. The direction image is produced by calculating
 *  the arctangent of the Xkernel and Ykernel images. These two images are members of the SobelFilter class and can be accessed as 
 *  this -> intensityim and this -> directionim.
 */

SobelFilter::SobelFilter(){}

void SobelFilter::convolve(vector<Image *> img, vector<vector<float>> mat, Image* im){
   
    Image newimg(img[0]->GetWidth(),img[0]->GetHeight());
    newimg.SetBuf(img[0]->GetBuf());
    float r= 0.0;

    // loops through each pixel value
    for (int x = 0; x < img[0]->GetWidth(); x++) {
        for (int y = 0; y < img[0]->GetHeight(); y++) {

        // sets each pixel to its float representation
        newimg.setPixelFloat(x,y, static_cast<float>(img[0]->GetPixel(x,y)[0]));
        }
    }

    // loops through each pixel
    for (int x = 0; x < img[0]->GetWidth(); x++) {
        for (int y = 0; y < img[0]->GetHeight(); y++) {

            // resets the pixel value
            r= 0.0;

                // checking for edge cases
                if (x>=1 && y>=1 && x*y<=img[0]->GetWidth()*img[0]->GetHeight()*4){
                
                // loops through surrounding pixels
                for (int i = x-1; i<=x+1;i++){
                    for (int j = y-1;j<=y+1;j++){
                        int k = i - (x-1);
                        int l = j - (y-1);
                
                        float newval= img[0]->GetPixel(i,j)[0];

                        // multiplying pixel value by kernel value                        
                        r += mat[k][l] * newval;
                
                    }
                }
                // sets the new pixel value to the calculated value after applying the kernel
                newimg.setPixelFloat(x,y,r);
            }
        }
    }   
        *im = newimg;
}

void SobelFilter::intensity(Image* original){

    // loops through each pixel
    for (int x = 0; x < original->GetWidth(); x++) {
        for (int y = 0; y < original->GetHeight(); y++) {
            float r= 0.0;

            // gets the float representation of the pixel from the x and y kernel images
            float pixelX= this->Ix->getPixelFloat(x,y);
            float pixelY= this->Iy->getPixelFloat(x,y);

            // calculates the hypotenuse between the two pixels
            r= sqrt(pow(pixelX,2.0)+pow(pixelY,2.0));

            // sets limits on the pixel values
            if (r>255){
                r = 255;
            }
            else if (r<0){
                r = 0;
            }
            // sets the intensity image pixels
            this->intensityim->SetPixel(x,y,r,r,r,255);
        }
    }
}

void SobelFilter::direction(Image* original){

    // loops through each pixel
    for (int x = 0; x < original->GetWidth(); x++) {
        for (int y = 0; y< original->GetHeight(); y++) {

            // gets the float representation of the pixel from the x and y kernel images
            float pixelX= this->Ix->getPixelFloat(x,y);
            float pixelY= this->Iy->getPixelFloat(x,y);

            // calculates the arctan between the two pixel values
            double r= atan2(pixelY,pixelX);

            // sets the direction image pixels
            this->directionim->setPixelFloat(x,y,r);
}
    }
}

// gets the intensity image
Image* SobelFilter::getIntensity(){
    return this->intensityim;
}

// gets the direction image
Image* SobelFilter::getDirection(){
    return this->directionim;
}

// produces the intensity and direction images
void SobelFilter::Apply(vector<Image *> original, vector<Image *> filtered){

    this->Ix = new Image(original[0]->GetWidth(),original[0]->GetHeight());
    this->Iy = new Image(original[0]->GetWidth(),original[0]->GetHeight());
    this->directionim = new Image(original[0]->GetWidth(),original[0]->GetHeight());
    this->intensityim = new Image(original[0]->GetWidth(),original[0]->GetHeight());

    SobelFilter::convolve(original, this->SobelX, this->Ix);
    SobelFilter::convolve(original, this->SobelY, this->Iy);
    SobelFilter::intensity(original[0]);
    SobelFilter::direction(original[0]);
    
}
