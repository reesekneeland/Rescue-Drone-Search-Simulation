#include<iostream> 
#include<memory>
using namespace std;
#include"image.h"

// Needed for reading images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Needed for writing images
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(int w, int h){
    height = h;
    width = w;
    components = 4;
    imageBuf = make_unique<unsigned char[]>(width*height*components);

    // Loop through the image pixels and modify values
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
        // Get the pixel as a byte array
        unsigned char* pixel = &imageBuf.get()[(y*width + x)*4];
        pixel[0] = 0;
        pixel[1] = 0;      
        pixel[2] = 0;
        pixel[3] = 0;
      }
    }
}
Image::~Image(){}

Image::Image(unsigned char*file){
  components =4;
  imageBuf = make_unique<unsigned char[]>(width*height*components);
  std::copy(file,file + width*height*components, imageBuf.get());
  stbi_image_free(file);
  
}

Image::Image(std::string filename){
      // Load in an image
    unsigned char *loadedImage = stbi_load(filename.c_str(), &width, &height, &components, STBI_rgb_alpha);
    components = 4; // Images may have less components, but we are forcing alpha with STBI_rgb_alpha
    // Copy the image data into a buffer contained in a unique pointerand free the image
    imageBuf = make_unique<unsigned char[]>(width*height*components);
	  std::copy(loadedImage, loadedImage + width*height*components, imageBuf.get()); // copy allows us to copy one byte array to another
    stbi_image_free(loadedImage);
}

void Image::operator=(const Image& image){
          
          this->components = 4;
          this->width = image.width;
          this->height = image.height;
          std::copy(image.imageBuf.get(), image.imageBuf.get() + width*height*components, this->imageBuf.get());
}

void Image::SetBuf(unsigned char* buf){
  imageBuf = make_unique<unsigned char[]>(width*height*components);
  std::copy(buf, buf + width*height*components, imageBuf.get());
}

unsigned char* Image::GetBuf(){
  return imageBuf.get();
}

void Image::SaveAs(string filename){
    // Save the output image
    stbi_write_png(filename.c_str(), width, height, components, imageBuf.get(), width*4);
}

int Image::GetHeight(){
  return height;
}

int Image::GetWidth(){
  return width;
}

int Image::GetComponentNum(){
  return components;
}

float Image::GetLuminance(int x, int y) {
     unsigned char* pixel = GetPixel(x, y);
     return 0.2126*pixel[0] + 0.7152*pixel[1] + 0.0722*pixel[2];
}

unsigned char * Image::GetPixel(int x, int y){
  return &imageBuf.get()[(y*width + x)*4];
}

void Image::SetPixel(int x, int y, int r, int g, int b, int a){
  unsigned char* pixel = &imageBuf.get()[(y*width + x)*4];
  pixel[0] = r;
  pixel[1] = g;      
  pixel[2] = b;
  pixel[3] = a;
}

float Image::getPixelFloat(int x, int y) const {
unsigned char* pixel = &imageBuf.get()[(x + width*y)*4];
return *reinterpret_cast<float*>(pixel);
}

void Image::setPixelFloat(int x, int y, float value){
unsigned char* pixel = &imageBuf.get()[(x + width*y)*4];
*reinterpret_cast<float*>(pixel) = value;
}
