#include "non-max-suppression.h"
#include <iostream>
#include <cmath>

void NonMaxFilter::Apply(std::vector<Image*> original,std::vector<Image*> filtered){
    for(int i = 0; i < (original.size()/2); i++){
        Image intensity = *original[2*i];
        Image direction = *original[(2*i)+1];
        Image suppression = Suppress(intensity, direction);
        *filtered[i] = suppression;
    }
}

Image NonMaxFilter::Suppress(Image intensity, Image direction){
    int width = intensity.GetWidth();
    int height = intensity.GetHeight();
    Image suppression(width,height);
    //loops through intensity/direction matrix's "pixels" or values
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            float i_pix = intensity.getPixelFloat(i,j);
            float d_pix = RadtoDeg(direction.getPixelFloat(i,j));
            unsigned char* suppress_pix = new unsigned char[4];
            //checks the direction the intensity pixel should compare itself with
            if(abs(d_pix) <= 22.5 || abs(d_pix) >= 157.5){
                //makes sure pixel exists within dimensions of image
                if(i-1>=0 && (intensity.getPixelFloat(i-1,j) > i_pix)){
                    i_pix = 0;
                }
                if(i+1<width && (intensity.getPixelFloat(i+1,j) > i_pix)){
                    i_pix = 0;
                }
            }
            else if((d_pix > 22.5 && d_pix < 67.5) || (d_pix < -112.5 && d_pix > -157.5)){
                if(i-1>=0 && j-1>=0 && (intensity.getPixelFloat(i-1,j-1) > i_pix)){
                    i_pix = 0;
                }
                if(i+1<width && j+1<height && (intensity.getPixelFloat(i+1,j+1) > i_pix)){
                    i_pix = 0;
                }
            }
            else if(abs(d_pix) >= 67.5 && abs(d_pix) <= 112.5){
                if(j-1>=0 && (intensity.getPixelFloat(i,j-1) > i_pix)){
                    i_pix = 0;
                }
                if(j+1<height && (intensity.getPixelFloat(i,j+1) > i_pix)){
                    i_pix = 0;
                }
            }
            else{
                if(i-1>=0 && j+1<=height && (intensity.getPixelFloat(i-1,j+1) > i_pix)){
                    i_pix = 0;
                }
                if(i+1<width && j-1>=0 && (intensity.getPixelFloat(i+1,j-1) > i_pix)){
                    i_pix = 0;
                }
            }
            //keeps pixel value within bounds of an unsigned char
            if(i_pix > 255){
                i_pix = 255;
            }
            suppress_pix[0] = i_pix; suppress_pix[1] = i_pix; suppress_pix[2] = i_pix; suppress_pix[3] = 255;
            suppression.SetPixel(i,j,suppress_pix);
            delete[] suppress_pix;
        }
    }
    return suppression;
}

//radians to degrees
float NonMaxFilter::RadtoDeg(float rad){
    float deg = (180*rad)/M_PI;
    return deg;
}