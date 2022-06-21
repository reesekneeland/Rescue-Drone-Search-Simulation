/**
 * @file canny.cc
 *
 */

#include "canny.h"

Canny::Canny(){}
        
void Canny::Apply(vector<Image *> original, vector<Image *> filtered){
    
    GreyScaleFilter* greyscale = new GreyScaleFilter();
    greyscale->Apply(original, filtered);
    *original[0]=*filtered[0];

    GaussianBlurFilter* gaussian = new GaussianBlurFilter();
    gaussian->Apply(original,filtered);
    *original[0]=*filtered[0];

    NonMaxFilter* nonmax = new NonMaxFilter();
    nonmax->Apply(original,filtered);
    *original[0]=*filtered[0];

    DoubleThresholdFilter* doubleThresh = new DoubleThresholdFilter(0.2, 0.4, 25, 255);
    doubleThresh->Apply(original, filtered);
    *original[0]=*filtered[0];

    HysteresisFilter* hyst = new HysteresisFilter();
    hyst->Apply(original, filtered);
    *original[0]=*filtered[0];

    delete greyscale;
    delete gaussian;
    delete nonmax;
    delete doubleThresh;
    delete hyst;



}
