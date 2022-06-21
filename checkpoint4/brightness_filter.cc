/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "brightness_filter.h"
//here i will create a brightness filter that dims and brightens a given image

//Brightness constructor that initilizes bright variable that is between -255 to 255
BrightnessFilter::BrightnessFilter(int bright){
    this->bright = bright;
}
//Truncating function that ensures the color value is between 0 to 255
int BrightnessFilter::truncate(int color){
    return min(255,max(0,color));
}
//Application function that applies brightness or dim to a given image 
void BrightnessFilter::Apply(std::vector<Image*> original,std::vector<Image*> filtered){
    filtered[0]->SetBuf(original[0]->GetBuf());
    for(int i=0;i<original[0]->GetWidth();i++){
        for(int j=0;j<original[0]->GetHeight();j++){
           unsigned char* pixel = original[0]->GetPixel(i,j); 

            pixel[0] = truncate(pixel[0]+bright);
            pixel[1] = truncate(pixel[1]+bright);
            pixel[2] = truncate(pixel[2]+bright);

            filtered[0]->SetPixel(i,j,pixel[0],pixel[1],pixel[2],255);

        }
    }
}
