#include "rgb_to_hsv.h"
using namespace std;

RgbToHsv::RgbToHsv(){};

void RgbToHsv::Apply(std::vector<Image*> original,std::vector<Image*>filtered){
    *filtered[0]=*original[0];

    for(int x = 0; x<original[0]->GetWidth();x++){
        for(int y =0; y<original[0]->GetHeight();y++){
            unsigned char* pixel = original[0]->GetPixel(x,y);
            double r = pixel[0]/255.0;
            double g = pixel[1]/255.0;
            double b = pixel[2]/255.0;
            
            double cmax = max(r,max(g,b)); 
            double cmin = min(r,min(g,b));
            double diff = cmax - cmin;
            double h = -1, s=-1, v = cmax*100;

            //h value calculation 
            if (cmax==cmin){
                h=0;
            }else if(cmax == r){
                h = fmod((60.0*((g-b)/diff)+360.0),360.0);
            }else if(cmax ==g){
                h = fmod((60*((b-r)/diff)+360),360);
            }else if(cmax==b){
                h = fmod((60*((r-g)/diff)+360),360);
            }
            //s value calculation 
            if(cmax==0){
                s=0;
            }else{
                s = (diff/cmax)*100;
            }
            

            unsigned char pxl[4]={(unsigned char)h,(unsigned char)s,(unsigned char)v,255};

            filtered[0]->SetPixel(x,y,pxl);

        }
    }
}