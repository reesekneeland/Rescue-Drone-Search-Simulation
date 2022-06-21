#include "gtest/gtest.h"
#include "filters/image.h"
#include <iomanip>
#include <vector>
#include "filters/blob_detect.h" 
#include "filters/color_threshold.h"
#include "filters/canny_on_blob.h"
class BlobDetectTests : public ::testing::Test {
public:
  void SetUp( ) { 
    
    
  }
protected:
};
//Unit Testing
TEST_F(BlobDetectTests, PixelCount){
    Image* colored = new Image("tests/1_color.png");
    BlobDetect* blob = new BlobDetect();

    int colorPxls=blob->PixelCount(colored);

    EXPECT_EQ(colorPxls,9131)<<"Correct pixel count";

    delete colored;
    delete blob;
}
//Integration testing
TEST_F(BlobDetectTests,ObjectPresent){
    Image* orig = new Image("tests/1.png");

    ColorThreshold* clr = new ColorThreshold();
    CannyOnBlob* cny = new CannyOnBlob();
    BlobDetect* blb = new BlobDetect();
    //blank image
    Image filtered;
    std::vector<Image*>filter;
    filter.push_back(&filtered);
    //original image
    std::vector<Image*> original;
    original.push_back(orig);


    clr->Apply(original,filter);
    cny->Apply(filter,original);

    EXPECT_EQ(blb->objPresent(cny->edgePxlCount,clr->blobPxlCount),true)<<"Wrong ratio comparison";

    delete orig;
    delete clr;
    delete cny;
    delete blb;
    
}
