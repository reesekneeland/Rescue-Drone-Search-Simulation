#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "image.h"

#include "sobel_filter.h"
#include "nonmax_filter.h"
#include "gaussian_blur_filter.h"
#include "greyscale_filter.h"
#include "double_threshold_filter.h"
#include "filter.h"
#include "invert_filter.h"
#include "hysteresis_filter.h"
#include "brightness_filter.h"
#include "canny.h"
#include "color_threshold.h"
#include "rgb_to_hsv.h"


using namespace std;

int main(int argc, const char* argv[]) {
    // Get input file, filter type, and output file from command line
    // argc = # of arguments
    // argv = an array of arguments
    std::string inputFile(argv[1]);
    std::string filterType(argv[2]);
    std::string outputFile(argv[3]);

    // Create available filters (unique_ptr handles dynamic memory)
    std::map<std::string, unique_ptr<Filter>> filters;
    filters["nonmax"] = unique_ptr<Filter>(new NonMaxFilter());
    filters["gaussian_blur"] = unique_ptr<Filter>(new GaussianBlurFilter());
    filters["sobel"] = unique_ptr<Filter>(new SobelFilter());
    filters["greyscale"] = unique_ptr<Filter>(new GreyScaleFilter());
    filters["invert"] = unique_ptr<Filter>(new InvertFilter());
    filters["double_threshold"] = unique_ptr<Filter>(new DoubleThresholdFilter(0.1, 0.2, 25, 255));
    filters["hysteresis"] = unique_ptr<Filter>(new HysteresisFilter());
    filters["brightness"] = unique_ptr<Filter>(new BrightnessFilter(255));
    filters["canny"] = unique_ptr<Filter>(new Canny());
    filters["color_threshold"]=unique_ptr<Filter>(new ColorThreshold());
    filters["hsv"]=unique_ptr<Filter>(new RgbToHsv());


    // Create input and output vectors
    Image input(inputFile);
    Image output(input.GetWidth(), input.GetHeight());
    std::vector<Image*> inputs;
    std::vector<Image*> outputs;
    inputs.push_back(&input);
    outputs.push_back(&output);

    // Apply filter based on filter type
    filters[filterType]->Apply(inputs, outputs);
    
    // Save output image
    output.SaveAs(outputFile);

}