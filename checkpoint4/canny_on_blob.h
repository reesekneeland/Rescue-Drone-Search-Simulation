#ifndef CANNY_ON_BLOB_H_
#define CANNY_ON_BLOB_H_
#include "filter.h"
#include "canny.h"

class CannyOnBlob: public Filter{
public:
    CannyOnBlob();
    void Apply(std::vector<Image*> original,std::vector<Image*>filtered);

};


#endif//CANNY_ON_BLOB_H_