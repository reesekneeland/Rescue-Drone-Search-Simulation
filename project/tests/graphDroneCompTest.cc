#include "gtest/gtest.h"
#include "entityFactory.h"
#include "simulation.h"
#include <vector>
#include "drone.h"
#include "graph.h"
 
class GraphDroneCompTests : public ::testing::Test {
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

TEST_F(GraphDroneCompTests, VisitNode) {
    EXPECT_EQ(drone->GetTargetNode(), "1719996961") << "Initial graph node initialization failed";
    drone->UpdateTarget(drone->GetTargetNode());
    EXPECT_EQ(drone->GetTargetNode(), "1719996958") << "Graph VisitNode method failed.";
    drone->UpdateTarget(drone->GetTargetNode());
    EXPECT_EQ(drone->GetTargetNode(), "246710361") << "Graph VisitNode method failed.";
}