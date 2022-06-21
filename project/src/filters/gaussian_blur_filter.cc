#include "gaussian_blur_filter.h"

GaussianBlurFilter::GaussianBlurFilter():kernelSize(5){
    kernel.push_back(std::vector<double>(5));
    kernel.push_back(std::vector<double>(5));
    kernel.push_back(std::vector<double>(5));
    kernel.push_back(std::vector<double>(5));
    kernel.push_back(std::vector<double>(5));
    double s = 2.0;
    int k = (kernelSize-1)/2;
    for (int i = 1; i <= 5; i++) {//initialize and create kernel
        for (int j = 1; j <= 5; j++) {
            double r = (i-(k+1))*(i-(k+1)) + (j-(k+1)) * (j-(k+1));
            kernel[i-1][j-1] = (exp(-(r * r) / s)) / (M_PI * s);
        }
    }
}
GaussianBlurFilter::GaussianBlurFilter(int size, double sigma) : kernelSize(size) {
    for (int i = 0; i < size; i++) {
        kernel.push_back(std::vector<double>(size));
    }
    double s = 2.0*(sigma*sigma);
    int k = (kernelSize-1)/2;

    for (int i = 1; i <= kernelSize; i++) {
        for (int j = 1; j <= kernelSize; j++) {
            double r = ((i-(k+1))*(i-(k+1))) + ((j-(k+1)) * (j-(k+1)));
            kernel[i-1][j-1] = 1.0 / (M_PI*s) * exp(-1.0 * r / s);
        }
    }
}
GaussianBlurFilter::~GaussianBlurFilter() {
    for (int i = 0; i < kernelSize;i++) {
        kernel[i].clear();
    }
    kernel.clear();
}

void GaussianBlurFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered) {
    *filtered[0] = *original[0];
    int width = original[0]->GetWidth();
    int height = original[0]->GetHeight();
    for (int x = 0; x < width; x++) { // outer 2 for loops loop through entire image
        for (int y = 0; y < height; y++) {
            double r = 0, g = 0, b = 0;//accumulators to be averaged.
            for (int i = 0; i < kernelSize;i++) {
                for (int j = 0; j < kernelSize;j++) {
                    int xx = x+i-kernelSize/2;
                    int yy = y+j-kernelSize/2;
                    unsigned char* pixel = original[0]->GetOverflowPixel(xx,yy);
                    r += pixel[0] * kernel[i][j];
                    g += pixel[1] * kernel[i][j];
                    b += pixel[2] * kernel[i][j];
                }
            }
            unsigned char average[4] = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
            filtered[0]->SetPixel(x, y, average);
        }
    }
}