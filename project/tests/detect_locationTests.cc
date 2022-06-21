#include "gtest/gtest.h"
#include "filters/image.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include "detect_location.h"
//Unit Tests
class DetectLocationTests : public ::testing::Test {
public:
  void SetUp( ) { 

  }
protected:
};

TEST_F(DetectLocationTests, DirectionCalculation) {
    unsigned char pixel[4] = {255,255,255,255};
    DetectLocation* detect= new DetectLocation();
    detect->DirCalc(pixel);
    
    EXPECT_EQ((detect->DirVec)[0],1)<<"Direction vector is calculated incorrectly";
    EXPECT_EQ((detect->Direction)[0],(1.0/sqrt(3)))<<"Direction is calculated incorrectly";
    EXPECT_EQ((detect->Distance),((1-sqrt(3))*50.0))<<"Distance calculation is wrong";
    delete detect;
}

TEST_F(DetectLocationTests,FindXyPxl){
  Image* image=new Image("tests/1_color.png");
  DetectLocation* detect= new DetectLocation();
  detect->FindxyPxl(image);

  EXPECT_EQ(detect->xyPxl[1],560)<<"wrong coordinate";
  delete image;
  delete detect;
}


