/**
 * @file nonmax_filter.cc
 *
 */

/*******************************************************************************
  * Includes
******************************************************************************/

#include "nonmax_filter.h"
#include "sobel_filter.h"
#include <memory>
#include <math.h>
using namespace std;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief The NonMax Filter class for the application of this filter.
 *
 *  This filter class takes in one input image and applies the Sobel to get two seperate images 
 *  representing an intensity map and a direction map. NonMax then checks the direction of each
 *  pixel against surrounding pixels, and sets all pixels that aren't the maximum intensity pixel
 *  to zero to thin the edge.
 *  
 */

NonMaxFilter::NonMaxFilter(){}

void NonMaxFilter::Apply(vector<Image *> original, vector<Image *> filtered){
    unique_ptr<SobelFilter> Sobel = unique_ptr<SobelFilter>(new SobelFilter());
    Sobel->Apply(original, filtered);
    Image * intensityMap = Sobel->getIntensity();
    Image * directionMap = Sobel->getDirection();
    int width = intensityMap->GetWidth();
    int height = intensityMap->GetHeight();
    filtered[0]->SetBuf(intensityMap->GetBuf());
    Image * angles = directionMap;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float direction = directionMap->getPixelFloat(x, y);
            float angle = (direction * 180)/3.141592653589;
            if(angle < 0){
                angle += 180;
            }
            angles->setPixelFloat(x, y, angle);
        }
    }
    for (int x = 1; x < width-1; x++) {
        for (int y = 1; y < height-1; y++) {
            if(x!=0&&x!=filtered[0]->GetWidth()-1&&y!=0&&y!=intensityMap->GetHeight()-1){
                float angle = angles->getPixelFloat(x, y);
                int intensity = intensityMap->GetPixel(x, y)[0];
                int q = 255;
                int r = 255;
                //angle 0
                if((0 <= angle <= 22.5) ||(157.5 <= angle <= 180)){
                    q = intensityMap->GetPixel(x, y+1)[0];
                    r = intensityMap->GetPixel(x, y-1)[0];
                }
                //angle 45
                else if(22.5 <= angle <= 67.5){
                    q = intensityMap->GetPixel(x+1, y-1)[0];
                    r = intensityMap->GetPixel(x-1, y+1)[0];
                }
                //angle 90
                else if(67.5 <= angle <= 112.5){
                    q = intensityMap->GetPixel(x+1, y)[0];
                    r = intensityMap->GetPixel(x-1, y)[0];
                }
                //angle 135
                else if(112.5 <= angle <= 157.5){
                    q = intensityMap->GetPixel(x-1, y-1)[0];
                    r = intensityMap->GetPixel(x+1, y+1)[0];
                }
                if((intensity >= q) && (intensity >= r)){
                    filtered[0]->SetPixel(x, y, intensity, intensity, intensity, 255);
                }
                else{
                    filtered[0]->SetPixel(x, y, 0, 0, 0, 255);
                }
            }
        }
    }

                
    
}