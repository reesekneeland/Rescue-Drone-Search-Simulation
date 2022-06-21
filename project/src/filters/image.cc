
// Needed for reading images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "image.h"
// Needed for writing images
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//constructors
Image::Image(){

}

Image::Image(const std::string& filename){
  unsigned char* oldImage = stbi_load(filename.c_str(), &width, &height, &components, STBI_rgb_alpha);
  components = 4;
  image = new unsigned char[width*height*components];
  std::copy(oldImage, oldImage + width*height*components, image);
  stbi_image_free(oldImage);
}

Image::Image(int width,int height):width(width),height(height){
  image = new unsigned char[width*height*components];
}

Image::Image(const Image &img){
  *this = img;
}

void Image::operator=(const Image& img){
  if(image!=NULL){
    delete[] image;
  }
  width = img.width;
  height = img.height;
  components = img.components;
  image = new unsigned char[width*height*components];
  std::copy(img.image, img.image + width*height*components, image);
}

//destructor
Image::~Image(){
  delete[] image;
}


//getters
int Image::GetHeight() const{
  return height;
}

int Image::GetWidth() const{
  return width;
}

int Image::GetComponentNum() const{
  return components;
}

double Image::GetLuminance(int x, int y) const{
  unsigned char* pixel = GetPixel(x,y);
  return 0.2126*pixel[0] + 0.7152*pixel[1] + 0.0722*pixel[2];
}

unsigned char* Image::GetPixel(int x, int y) const{
  return &image[(y*width + x)*4];
}
unsigned char* Image::GetOverflowPixel(int x, int y) const{
    int X = x;
    int Y = y;
    if (x < 0) {
        X = 0;
    }
    if (y < 0) {
        Y = 0;
    }
    if (x > width - 1) {
        X = width - 1;
    }
    if (y > height - 1) {
        Y = height - 1;
    }
    return this->GetPixel(X, Y);
}

//setters
void Image::SetPixel(int x, int y, unsigned char* pixel){
  unsigned char* currentPixel = GetPixel(x,y);
  currentPixel[0]=pixel[0];
  currentPixel[1]=pixel[1];
  currentPixel[2]=pixel[2];
  currentPixel[3]=pixel[3];
}

//other
void Image::SaveAs(const std::string& filename){
  stbi_write_png(filename.c_str(), width, height, components, image, width*4);
}


float Image::getPixelFloat(int x, int y) const {
  unsigned char* pixel = &image[(x + width*y)*4];
  return *reinterpret_cast<float*>(pixel);
}

void Image::setPixelFloat(int x, int y, float value){
  unsigned char* pixel = &image[(x + width*y)*4];
  *reinterpret_cast<float*>(pixel) = value;
}

unsigned char* Image::GetImage(){
  return image;
}
