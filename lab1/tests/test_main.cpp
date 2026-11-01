#include <gtest/gtest.h>
#include "Room.h"
#include "Services.h"
#include "Repositories.h"
#include <cstdio>
#include <fstream>

TEST(ThermostatTest, ControlLogic) {
    Thermostat t(Temperature(20.0), 0.5);
    
    auto [heat1, cool1] = t.calculateControl(Temperature(18.0));
    EXPECT_DOUBLE_EQ(heat1.value, 1.0);
    EXPECT_DOUBLE_EQ(cool1.value, 0.0);

    auto [heat2, cool2] = t.calculateControl(Temperature(25.0));
    EXPECT_DOUBLE_EQ(heat2.value, 0.0);
    EXPECT_DOUBLE_EQ(cool2.value, 1.0);

    auto [heat3, cool3] = t.calculateControl(Temperature(20.2));
    EXPECT_DOUBLE_EQ(heat3.value, 0.0);
    EXPECT_DOUBLE_EQ(cool3.value, 0.0);
}

TEST(RoomTest, PhysicsHeating) {
    Room room(10.0, 100.0, 0.0, 100.0, 0.0, 42);
    room.getHeater().setPower(Power(1.0));
    room.updatePhysics(1.0, Temperature(10.0)); 
    EXPECT_NEAR(room.getTrueTemperature(), 11.0, 0.001);
}

TEST(RepositoryTest, FileWrite) {
    std::string testFile = "test_log.csv";
    {
        FileJournalRepository repo(testFile);
        repo.save({1.0, 22.5, 0.0, 1.0});
    } 

    std::ifstream f(testFile);
    ASSERT_TRUE(f.is_open());
    
    std::string header, data;
    std::getline(f, header);
    std::getline(f, data);
    
    EXPECT_EQ(data, "1,22.5,0,1");
    
    f.close();
    std::remove(testFile.c_str());
}