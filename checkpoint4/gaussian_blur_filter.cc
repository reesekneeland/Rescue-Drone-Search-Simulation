/**
 * @file gaussian_blur_filter.cc
 *
 */

/*******************************************************************************
  * Includes
******************************************************************************/

#include "gaussian_blur_filter.h"
#include<math.h>
using namespace std;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief The Gaussian Blur Filter class for the application of this filter.
 *
 *  This filter class takes in one input image and applies an Gaussian kernel to the image to yield a blurred image.
 */

GaussianBlurFilter::GaussianBlurFilter(){}

void GaussianBlurFilter::Apply(vector<Image *> original, vector<Image *> filtered){
    int width = original[0]->GetWidth();
    int height = original[0]->GetHeight();
    int size = 5;
    vector<vector<double>> normalMap(size, vector<double>(size));
    int sigma = 1;
    int redSize = (size -1)/2;
    double normal = 1/(2.0 * 3.14159465 * pow(sigma,2));
    for(int x = 0; x < size; x++){
        for(int y = 0; y<size; y++){
            double xVal = (x-redSize);
            double yVal = (y-redSize);
            normalMap[x][y] = pow(2.71828182, -((pow(xVal, 2) + pow(yVal, 2))/(2.0 * pow(sigma, 2)))) * normal;

        }
    }
    filtered[0]->SetBuf(original[0]->GetBuf());
     for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double r=0.0;
            double b=0.0;
            double g=0.0;
            if(x!=0&&x!=1&&x!=filtered[0]->GetWidth()-2&&x!=filtered[0]->GetWidth()-1&&y!=0&&y!=1&&y!=original[0]->GetHeight()-2&&y!=original[0]->GetHeight()-1){
                for (int i = x-2; i <= x+2; i++){
                    for (int j = y-2; j <= y+2; j++){
                        int k = i - (x-2);
                        int l = j - (y-2);
                        unsigned char* pixel = original[0]->GetPixel(i, j);
                        r += normalMap[k][l] * double(pixel[0]);
                        b += normalMap[k][l] * double(pixel[1]);
                        g += normalMap[k][l] * double(pixel[2]);
                    }
                }
                filtered[0]->SetPixel(x, y, r, b, g, 255);
            }
      }
    }
}
