#include "gtest/gtest.h"
#include "entityFactory.h"
#include "simulation.h"
#include <vector>
#include "robot.h"
 
class RobotTests : public ::testing::Test {
public:
  void SetUp( ) { 
      robot = new Robot(10);
      robot->SetPos(1,2,3);
        }
protected:
Robot* robot;
};

TEST_F(RobotTests, robotFunctions) {
   EXPECT_EQ(robot->GetPosX(), 1) << "robot position was set incorrectly";
   EXPECT_EQ(robot->GetPosY(), 2) << "robot position was set incorrectly";
   EXPECT_EQ(robot->GetPosZ(), 3) << "robot position was set incorrectly";
}

TEST_F(RobotTests, robotInit) {
   EXPECT_EQ(robot->GetID(), 10) << "robot id was initialized incorrectly";
}