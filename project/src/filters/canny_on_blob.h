#ifndef CANNY_ON_BLOB_H_
#define CANNY_ON_BLOB_H_
#include "filter.h"
#include "canny.h"
#include "blob_detect.h"

class CannyOnBlob: public Filter{
public:
    /**
     * @brief fefault constuctor of CannyOnBlob
     * 
     * 
     */
    CannyOnBlob();
     /**
     * @brief turns a color thresholded image to a canny edge image
     * 
     * @param original vector containing the blob image
     * @param filtered vector that will contain canny edge of blob
     * 
     */
    void Apply(std::vector<Image*> original,std::vector<Image*>filtered);

    int edgePxlCount;

};


#endif//CANNY_ON_BLOB_H_