#include "invert_filter.h"
#include <cmath>

InvertFilter::InvertFilter(){}

void InvertFilter::Apply(vector<Image *> original, vector<Image *> filtered)
{
    int width = original[0]->GetWidth();
    int height = original[0]->GetHeight();
    filtered[0]->SetBuf(original[0]->GetBuf());
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            unsigned char* pixel =(original[0]->GetPixel(x, y));
            int r = std::abs (255- int(pixel[0]));
            int b = std::abs (255 - int(pixel[1]));
            int g = std::abs (255 - int(pixel[2]));
            filtered[0]->SetPixel(x, y, r, b, g, 255);
        }
    }
}
