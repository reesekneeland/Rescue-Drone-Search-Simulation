#include "detect_location.h"
#include <iostream>
using namespace std;

DetectLocation::DetectLocation(){
    DirVec = new double[3];
    Direction = new double[3];
    xyPxl = new int[2];
    Distance =0;


}
DetectLocation::~DetectLocation(){
    delete[] DirVec;
    delete[] Direction;
    delete[] xyPxl;
}

void DetectLocation::FindxyPxl(Image* image){
    for(int x = 0; x<image->GetWidth();x++){
        for(int y =0; y<image->GetHeight();y++){
            unsigned char* pixel = image->GetPixel(x,y);
            //if white pixel found
            if(pixel[0]==255&&pixel[1]==255&&pixel[2]==255){
                    xyPxl[0]=x;
                    xyPxl[1]=y;
                    break;
            } 
        }
    }
}

void DetectLocation::DirCalc(unsigned char* pixel){
    double r=0,g=0,b=0;

    r = ((pixel[0]/255.0)-0.5)*2.0;
    g = ((pixel[1]/255.0)-0.5)*2.0;
    b = ((pixel[2]/255.0)-0.5)*2.0;
    //DirVec
    double ColorVec[3]={r,g,b};
    //copy ColorVec into DirVec
    for(int i=0;i<3;i++){
        DirVec[i]=ColorVec[i];
    }

    double AbsDirVec = sqrt(pow(ColorVec[0],2)+pow(ColorVec[1],2)+pow(ColorVec[2],2));

    //Direction
    for (int i=0; i<3;i++){
        Direction[i]=DirVec[i]/AbsDirVec;
    }
    //Distance 
    Distance = ((1.0 - AbsDirVec)*50.0);

}
