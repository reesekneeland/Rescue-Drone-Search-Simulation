
#include "canny.h"
#include "filter.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <stdio.h>
#include "image.h"
#include "greyscale_filter.h"
#include "gaussian_blur_filter.h"
#include "sobel_filter.h"
#include "non-max-suppression.h"
#include "double_threshold.h"
#include "hysteresis_filter.h"
void Canny::Apply(std::vector<Image *> original, std::vector<Image *> filtered)
{
    GreyScaleFilter gray_filter;
    GaussianBlurFilter gaus = GaussianBlurFilter(5,2);
    SobelFilter sf;
    NonMaxFilter nm;
    DoubleThresholdFilter dth = DoubleThresholdFilter();
    HysteresisFilter hf;
    
    std::vector<Image *> grey; // will contain greyscale image
    Image copy; // blank image
    grey.push_back(&copy);//adding blank image to grey
    gray_filter.Apply(original, grey);//greyscale the image
   //proccess repeats for each filter
    std::vector<Image *> blur;
    Image copy6;
    blur.push_back(&copy6);
    gaus.Apply(grey, blur);
    
    std::vector<Image *> sob;
    Image copy1;
    Image copy2;
    sob.push_back(&copy1);
    sob.push_back(&copy2);
    sf.Apply(blur, sob);
    sob[0]->SaveAs("sobel1.png");
    sob[1]->SaveAs("sobel2.png");
    std::vector<Image *> non_max;
    Image copy3;
    non_max.push_back(&copy3);
    nm.Apply(sob, non_max);
    
    std::vector<Image *> double_thres;
    Image copy4 = Image(non_max[0]->GetWidth(), non_max[0]->GetHeight());
    double_thres.push_back(&copy4);
    dth.Apply(non_max, double_thres);
   
    std::vector<Image *> hyster;
    Image copy5;
    hyster.push_back(&copy5);
    hf.Apply(double_thres, hyster);

    *filtered[0] = *hyster[0]; //setting the hysterisis filter to the filtered image
}
