
/**
 * @file greyscale_filter.cc
 *
 */
 
#include "greyscale_filter.h"
using namespace std;

GreyScaleFilter::GreyScaleFilter(){

}
        
void GreyScaleFilter::Apply(vector<Image *> original, vector<Image *> filtered){
     
     filtered[0]->SetBuf(original[0]->GetBuf());
     for (int x = 0; x < filtered[0]->GetWidth(); x++) {
        for (int y = 0; y < filtered[0]->GetHeight(); y++) {
        float L = filtered[0]->GetLuminance(x, y);
        filtered[0]->SetPixel(x, y, L, L, L, 255);
      }
    }
}
