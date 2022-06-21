#include "sobel_filter.h"
#include <iostream>
#include <cmath>

void SobelFilter::Apply(std::vector<Image*> original,std::vector<Image*> filtered){
    /*Some notes before starting:
    1. The values calculated from the kernels might be greater than 255 and should be
    accounted for when calculating the hypotenuse (intensity) image.
    2. The values calculated from the direction image can be negative and also
    should be accounted for
    3. Use 0 padding in the kernels (essentially replacing pixels outside of image with 0 as if they exist)
    4. Output should be 2 images (one representing hypotenuse image and one representing direction image)*/
    int xkernel[9] = {1,0,-1,2,0,-2,1,0,-1};
    int ykernel[9] = {1,2,1,0,0,0,-1,-2,-1};
    //We iterate every 2 because there are 2 output images for every input image
    for(int i = 0; i < original.size(); i++){
        Image ximage = Kernelize(original[i], xkernel);
        Image yimage = Kernelize(original[i], ykernel);
        Image intensity = Intensity(ximage, yimage);
        Image direction = Direction(ximage, yimage);
        *filtered[2*i] = intensity;
        *filtered[(2*i)+1] = direction;
    }
}

//Below are filter functions that do all of the work for the sobel filter process

Image SobelFilter::Kernelize(Image *original, int *kernel){
    //variables for creating x and y images
    int width = original->GetWidth();
    int height = original->GetHeight();
    Image kimage(width,height);
    //loops through each pixel in the image
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            int value = 0;
            int edge = 1;
            float intensity = 0;
            //loops through the bordering pixels 
            for(int k = j-1; k <= j+1; k++){
                for(int l = i-1; l <= i+1; l++){
                    //0 padding to ensure bounds are not crossed
                    if(k >= 0 && l >= 0 && k < height && l < width && edge){
                        unsigned char *cur_pix = original->GetPixel(l,k);
                        //computes values for kernelized image pixels using kernel values
                        intensity += (cur_pix[0]*kernel[value]);
                    }
                    else{
                        edge = 0;
                    }
                    value++;
                }
            }
            //sets pixel to 0 if pixel is on border
            if(!edge){
                intensity = 0;
            }
            kimage.setPixelFloat(i,j,intensity);
        }
    }
    return kimage;
}

Image SobelFilter::Intensity(Image ximage, Image yimage){
    int width = ximage.GetWidth();
    int height = ximage.GetHeight();
    Image intensity(width,height);
    //loops through both images' pixels
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            float x_pix = ximage.getPixelFloat(i,j);
            float y_pix = yimage.getPixelFloat(i,j);
            float intense_pix;
            //normalizes values for intensity calculations
            /*if(x_pix < 0){
                x_pix = 0;
            }
            if(y_pix < 0){
                y_pix = 0;
            }*/
            //gets hypotenuse (intensity gradient) of both the x image and y image values
            intense_pix = sqrt(pow(x_pix,2) + pow(y_pix,2));
            intensity.setPixelFloat(i,j,intense_pix);
        }
    }
    return intensity;
}

Image SobelFilter::Direction(Image ximage, Image yimage){
    int width = ximage.GetWidth();
    int height = ximage.GetHeight();
    Image direction(width,height);
    //loops through both images' pixels
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            float x_pix = ximage.getPixelFloat(i,j);
            float y_pix = yimage.getPixelFloat(i,j);
            float dir;
            //gets arctangent (edge direction) of both the x image and y image values
            dir = atan2(y_pix,x_pix);
            direction.setPixelFloat(i,j,dir);
        }
    }
    //note that this final image/matrix will not be used until non-max suppression
    return direction;
}
