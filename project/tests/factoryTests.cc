#include "gtest/gtest.h"
#include "entityFactory.h"
#include "simulation.h"
#include <vector>
#include <typeinfo>

Simulation* sim;  
class FactoryTest : public ::testing::Test {
public:
  void SetUp( ) { 
      sim = new Simulation();
      data1["name"] = picojson::value("drone");
      data1["entityId"] = picojson::value(0.0);
      data1["speed"]= picojson::value(10.0);

      data2["name"] = picojson::value("robot");
      data2["entityId"] = picojson::value(1.0);

      data3["name"] = picojson::value("recharge station");
      data3["entityId"] = picojson::value(2.0);

      data4["name"] = picojson::value("invalid entity");


  }
protected:
picojson::object data1;
picojson::object data2;
picojson::object data3;
picojson::object data4;

};

TEST_F(FactoryTest, CreateCorrectEntity) {
  sim->CreateEntity(data1, *sim);
  EXPECT_EQ(sim->entitylist[0]->GetName(), "drone") << "Drone Entity was created incorrectly";
  sim->CreateEntity(data2, *sim);
  EXPECT_EQ(sim->entitylist[1]->GetName(), "robot") << "Robot Entity was created incorrectly";
  sim->CreateEntity(data3, *sim);
  EXPECT_EQ(sim->entitylist[2]->GetName(), "charger") << "Charger Entity was created incorrectly";
}

TEST_F(FactoryTest, CreateDrone) {
   sim->CreateEntity(data1, *sim);
   EXPECT_EQ(sim->entitylist[0]->GetID(), 0.0) << "Entity ID was initialized incorrectly";
   EXPECT_EQ(sim->entitylist[0]->GetSpeed(), 10.0) << "Entity speed was initialized incorrectly";   
}

TEST_F(FactoryTest, CreateRobot) {
   sim->CreateEntity(data2, *sim);
   EXPECT_EQ(sim->entitylist[0]->GetID(), 1.0) << "Entity ID was initialized incorrectly";
}

TEST_F(FactoryTest, CreateCharger) {
   sim->CreateEntity(data3, *sim);
   EXPECT_EQ(sim->entitylist[0]->GetID(), 2.0) << "Entity ID was initialized incorrectly";
}

TEST_F(FactoryTest, invalidEntity) {
   sim->CreateEntity(data4, *sim);
   EXPECT_EQ(sim->entitylist.size(), 0) << "Entity creation was set up incorrectly";
}

TEST_F(FactoryTest, CheckDroneType) { // regression, Yna Roxas
  sim->CreateEntity(data1, *sim);
  EXPECT_EQ(std::string(typeid(*(sim->entitylist[0])).name()), "5Drone") << "Drone Entity was created incorrectly";
}

TEST_F(FactoryTest, CheckRobotType) { // regression, Yna Roxas
  sim->CreateEntity(data2, *sim);
  EXPECT_EQ(std::string(typeid(*(sim->entitylist[0])).name()), "5Robot") << "Robot Entity was created incorrectly";
}

TEST_F(FactoryTest, CheckChargerType) { // regression, Yna Roxas
  sim->CreateEntity(data3, *sim);
  EXPECT_EQ(std::string(typeid(*(sim->entitylist[0])).name()), "7Charger") << "Charger Entity was created incorrectly";
}

TEST_F(FactoryTest, CheckEntitylistSize) { // regression, Yna Roxas
  sim->CreateEntity(data1, *sim);
  sim->CreateEntity(data2, *sim);
  sim->CreateEntity(data3, *sim);
  EXPECT_EQ(sim->entitylist.size(), 3) << "Entity List size incorrect";
}

TEST_F(FactoryTest, CheckEntitylistSizeWithInvalidEntity) { // regression, Yna Roxas
  sim->CreateEntity(data1, *sim);
  sim->CreateEntity(data2, *sim);
  sim->CreateEntity(data3, *sim);
  sim->CreateEntity(data4, *sim);
  EXPECT_EQ(sim->entitylist.size(), 3) << "Entity List size incorrect";
}
