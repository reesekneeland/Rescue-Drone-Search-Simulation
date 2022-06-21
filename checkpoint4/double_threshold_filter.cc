/**
 * @file double_threshold_filter.cc
 *
 */

#include "double_threshold_filter.h"
using namespace std;

DoubleThresholdFilter::DoubleThresholdFilter(float lowRatio, float highRatio, float weak, float strong)
{
    this->lowRatio = lowRatio;
    this->highRatio = highRatio;
    this->strong = strong;
    this->weak = weak;
}

void DoubleThresholdFilter::Apply(vector<Image *> original, vector<Image *> filtered)
{
    int width = original[0]->GetWidth();
    int height = original[0]->GetHeight();
    //original[0]->SaveAs("DOUBLETHRES_og.png");
    filtered[0]->SetBuf(original[0]->GetBuf());
    filtered[0]->SaveAs("DOUBLETHRES_Filtered.png");
    // figure out maximum pixel to set threshold
    float max = 0;
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            unsigned char* current = original[0]->GetPixel(x, y);
            if (float(current[0]) > max){
                max = float(current[0]);
            }
        }
    }
    // set threshold levels from ratio
    float highThreshold = max * highRatio;
    float lowThreshold = highThreshold * lowRatio;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            unsigned char* current = original[0]->GetPixel(x, y);
            if(float(current[0]) >= highThreshold)
            {
                filtered[0]->SetPixel(x, y, strong, strong, strong, 255);
            }
            else if(float(current[0]) >= lowThreshold && float(current[0]) < highThreshold)
            {
                filtered[0]->SetPixel(x, y, weak, weak, weak, 255);
            }
            else
            {
                filtered[0]->SetPixel(x, y, 0, 0, 0, 255);
            }

        }   
    }


}
