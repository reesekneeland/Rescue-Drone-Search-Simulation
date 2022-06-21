#include "color_threshold.h"
#include "rgb_to_hsv.h"
using namespace std; 
#define WEAK 0
#define STRONG 255

ColorThreshold::ColorThreshold(){
}

bool ColorThreshold::isStrong(unsigned char* pixel){
    //check if the pixel is within the range of the robot pixels
    if ((27 <=pixel[0] && pixel[0]<=37)&&
        (87 <=pixel[1] && pixel[1]<=93)&&
        (70 <=pixel[2] && pixel[2]<=100)){
        return true;
    }else{
        return false;
    }
}

void ColorThreshold::Apply(std::vector<Image*> original,std::vector<Image*>filtered){

   RgbToHsv* rgbtohsv=new RgbToHsv();
   rgbtohsv->Apply(original,filtered);
   *original[0] = *filtered[0];
   
   unsigned char strongpxl[4]={STRONG,STRONG,STRONG,255};
   unsigned char weakpxl[4]={WEAK,WEAK,WEAK,255};

    for(int x = 1; x<original[0]->GetWidth();x++){
        for(int y =1; y<original[0]->GetHeight();y++){
            unsigned char* pixel = original[0]->GetPixel(x,y);

            if(isStrong(pixel)){
                filtered[0]->SetPixel(x,y,strongpxl);
            }else{
                filtered[0]->SetPixel(x,y,weakpxl);

            }
        }

    }
    BlobDetect blob;
    //white pixels present in blob image
    blobPxlCount = blob.PixelCount(filtered[0]);
    delete rgbtohsv;
}