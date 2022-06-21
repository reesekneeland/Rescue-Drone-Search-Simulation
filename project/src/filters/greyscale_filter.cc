#include "greyscale_filter.h"

void GreyScaleFilter::Apply(std::vector<Image*> original,std::vector<Image*> filtered){
    *filtered[0] = *original[0];
    int width = original[0]->GetWidth();
    int height = original[0]->GetHeight();

    for(int x = 0; x < width; x++){
        for(int y = 0;y < height; y++){
            unsigned char luminance = original[0]->GetLuminance(x,y);
            unsigned char pixel[4] = {luminance,luminance,luminance,255};
            filtered[0]->SetPixel(x,y,pixel);
        }
    }
}