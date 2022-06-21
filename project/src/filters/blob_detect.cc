#include "blob_detect.h"
using namespace std;

BlobDetect::BlobDetect(){
}

BlobDetect::~BlobDetect(){
}
int BlobDetect::PixelCount(Image* image){
    int numPixels=0;
    
     for(int x = 0; x<image->GetWidth();x++){
        for(int y =0; y<image->GetHeight();y++){
            unsigned char* pixel = image->GetPixel(x,y);
            if(pixel[0]==255&&pixel[1]==255&&pixel[2]==255){
                numPixels++;
            }
        }
    }
    return numPixels;
}

bool BlobDetect::objPresent(int edgeCount,int blobCount){
    bool found =false;
    if(edgeCount!=0){
        if(((1.0*blobCount)/(1.0*edgeCount))>=0.1){
            found =true;
        }
    }
    return found;
}