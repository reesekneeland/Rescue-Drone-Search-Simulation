#include "gtest/gtest.h"
#include "entityFactory.h"
#include "simulation.h"
#include <vector>
#include "drone.h"
 
class DroneTests : public ::testing::Test {
public:
  void SetUp( ) { 
      drone = new Drone(1);
      drone->SetSpeed(1);
      drone->SetPos(1,0,0);
      drone->SetDir(5,0,0);

  }
protected:
Drone* drone;

};

TEST_F(DroneTests, droneFunctions) {
   EXPECT_EQ(drone->GetSpeed(), 1) << "Drone speed was created incorrectly";

   EXPECT_EQ(drone->GetPosX(), 1) << "Drone position was created incorrectly";
   EXPECT_EQ(drone->GetPosY(), 0) << "Drone position was created incorrectly";
   EXPECT_EQ(drone->GetPosZ(), 0) << "Drone position was created incorrectly";

   EXPECT_EQ(drone->GetDirX(), 5) << "Drone direction was created incorrectly";
   EXPECT_EQ(drone->GetDirY(), 0) << "Drone direction was created incorrectly";
   EXPECT_EQ(drone->GetDirZ(), 0) << "Drone direction was created incorrectly";
}

TEST_F(DroneTests, droneInit) {
   EXPECT_EQ(drone->GetID(), 1) << "Drone was not initialized incorrectly";
}
TEST_F(DroneTests, getDist) {
   std::vector<double> pos1;
   std::vector<double> pos2;
   pos1.push_back(5.0);
   pos1.push_back(0.0);
   pos1.push_back(0.0);
   pos2.push_back(-5.0);
   pos2.push_back(0.0);
   pos2.push_back(0.0);

   EXPECT_EQ(drone->GetDist(pos1, pos2), 10) << "Point distance calculation failed";
}
TEST_F(DroneTests, GetTarget) {
   std::vector<double> dir1;
   dir1.push_back(0.5);
   dir1.push_back(0.3);
   dir1.push_back(0.2);
   drone->SetTarget(dir1);

   EXPECT_EQ(drone->GetTarget(), dir1) << "SetTarget failed";
}