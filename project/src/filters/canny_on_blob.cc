#include "canny_on_blob.h"
using namespace std;

CannyOnBlob::CannyOnBlob(){}

void CannyOnBlob::Apply(std::vector<Image*> original,std::vector<Image*>filtered){
    Canny* canny = new Canny();
    canny -> Apply(original,filtered);
    //*original[0]=*filtered[0];

    BlobDetect blob;
    edgePxlCount = blob.PixelCount(filtered[0]);
    
    delete canny;
}