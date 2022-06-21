#include "gtest/gtest.h"
#include "filters/image.h"
#include <iomanip>
#include <vector>
#include "filters/color_threshold.h"
#include "filters/blob_detect.h"
//Integration testing
class ColorThresholdTests : public ::testing::Test {
public:
  void SetUp( ) { 
    
    
  }
protected:
};

TEST_F(ColorThresholdTests, ApplyTest) {
    Image* original = new Image("tests/1.png");
    Image* colored = new Image("tests/1_color.png");

    //blank image
    Image filtered;
    std::vector<Image*>filterColor;
    filterColor.push_back(&filtered);

    ColorThreshold* color = new ColorThreshold();
    BlobDetect* blob = new BlobDetect();
    std::vector<Image*>original_image{original};

    color->Apply(original_image,filterColor);
    int colorPxls=blob->PixelCount(filterColor[0]);
    int testPxls=blob->PixelCount(colored);

    EXPECT_EQ(colorPxls,testPxls)<<"Color thresholding incorrectly";

    delete original;
    delete colored;
    delete blob;
    delete color;
}
