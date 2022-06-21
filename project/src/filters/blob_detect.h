#ifndef BLOB_DETECT_H_
#define BLOB_DETECT_H_
#include "image.h"
class BlobDetect{
public: 
    /**
     * @brief default constructor of blob detection
     * 
     * 
     */
    BlobDetect();
     /**
     * @brief default destructor of blob detection
     * 
     * 
     */
    ~BlobDetect();
    /**
     * @brief counts the number of white pixels in an image
     * 
     * @param image black and white image 
     * 
     * @return returns the number of white pixels in an image
     */
    int PixelCount(Image* image);
    /**
     * @brief counts the number of white pixels in an image
     * 
     * @param edgeCount number of white pixels in canny edge image
     * @param blobCount number of white pixels in color threshold image
     * 
     * @return true or false depending on if picture is present
     */
    bool objPresent(int edgeCount,int blobCount);
};

#endif//BLOB_DETECT_H_