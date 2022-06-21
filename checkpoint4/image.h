#include<iostream>  
#include<vector>
#include<memory>
using namespace std;
#ifndef IMAGE_H_
#define IMAGE_H_

class Image {
    public:
        Image(int w, int h);
        
        Image(string filename);
        
        Image(unsigned char* file);
        
        ~Image();
  
        void operator=(const Image& image);

        void SetBuf(unsigned char* buf);

        unsigned char* GetBuf();

        void SaveAs(string filename);

        int GetHeight();

        int GetWidth();

        int GetComponentNum();

        float GetLuminance(int x, int y);

        unsigned char * GetPixel(int x, int y);

        void SetPixel(int x, int y, int r, int g, int b, int a);

        float getPixelFloat(int x, int y) const;

        void setPixelFloat(int x, int y, float value);

    private:
        int components = 4;
        int height, width;
        unique_ptr<unsigned char[]> imageBuf;
    
};
#endif
