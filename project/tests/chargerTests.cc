#include "gtest/gtest.h"
#include "entityFactory.h"
#include "simulation.h"
#include <vector>
#include "Charger.h"
 
class ChargerTests : public ::testing::Test {
public:
  void SetUp( ) { 
      charger = new Charger(10);
      charger->SetPos(1,2,3);
  }
protected:
Charger* charger;

};

TEST_F(ChargerTests, chargerFunctions) {
   EXPECT_EQ(charger->GetSpeed(), 0) << "Charger speed was defaulted incorrectly";

   EXPECT_EQ(charger->GetPosX(), 1) << "charger position was set incorrectly";
   EXPECT_EQ(charger->GetPosY(), 2) << "charger position was set incorrectly";
   EXPECT_EQ(charger->GetPosZ(), 3) << "charger position was set incorrectly";
}

TEST_F(ChargerTests, chargerInit) {
   EXPECT_EQ(charger->GetID(), 10) << "charger id was initialized incorrectly";
}