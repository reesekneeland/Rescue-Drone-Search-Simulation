/**
 * @file hysteresis_filter.cc
 *
 */
 
 /*******************************************************************************
* Includes
******************************************************************************/
#include "hysteresis_filter.h"
#define WEAK  25
#define STRONG 255

// Here i will create a filter for a picture that has been 
//applied the double threshold filter to get rid of noise 
//by strengthing weak pixels that are around strong pixels

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

bool HysteresisFilter::isStrong(unsigned char* pixel){
    if (pixel[0]==STRONG && pixel[1]==STRONG && pixel[2]==STRONG){
        // if pixel is strong 
        return true;
    }else{ 
        //if pixel is weak
        return false;
    }

}

void HysteresisFilter::Apply(std::vector<Image*> original,std::vector<Image*> filtered){
    //setting filtered to original image
    filtered[0]->SetBuf(original[0]->GetBuf());

    for(int i=1;i<original[0]->GetWidth()-1;i++){
        for(int j=1;j<original[0]->GetHeight()-1;j++){
            unsigned char* pixel = original[0]->GetPixel(i,j);

            if (pixel[0]==WEAK && pixel[1]==WEAK &&pixel[2]==WEAK){
                if (isStrong(original[0]->GetPixel(i+1,j-1)) || 
                    isStrong(original[0]->GetPixel(i+1,j)) || 
                    isStrong(original[0]->GetPixel(i+1,j+1)) || 
                    isStrong(original[0]->GetPixel(i,j-1)) ||  
                    isStrong(original[0]->GetPixel(i,j+1)) ||  
                    isStrong(original[0]->GetPixel(i-1,j-1)) ||  
                    isStrong(original[0]->GetPixel(i-1,j)) ||  
                    isStrong(original[0]->GetPixel(i-1,j+1))){

                    //if any of the surrounding is strong
                    filtered[0]->SetPixel(i,j,STRONG,STRONG,STRONG,255);

                }
                else{
                    //if the pixel is black or there are no strong pixels
                    //around the weak pixel
                   filtered[0]->SetPixel(i,j,0,0,0,255); 
                }
            }

        }
    }
}
