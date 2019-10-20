#include "../mtmtest.h"
#include <assert.h>
#include "../Exceptions.h"
#include "../KidsRoom.h"
#include <string>
#include <list>

using namespace mtm::escaperoom;


void testKidsRoomCreate() {
    KidsRoom Kids1((char*)"buhh", 40, 3, 7, 12);
}

void testKidsRoomCopy(){
    KidsRoom Kids1((char*)"buhh", 40, 3, 7, 12);
    KidsRoom Kids2(Kids1);
    
    ASSERT_TRUE(Kids1 == Kids2);
}

void testKidsRoomBool(){
    KidsRoom Kids1((char*)"buhh", 40, 3, 7, 12);
    KidsRoom Kids2((char*)"Auhhhh", 42, 4, 7, 12);
    KidsRoom Kids3(Kids1);
    
    ASSERT_TRUE(Kids1 == Kids3);
    ASSERT_FALSE(Kids1 == Kids2);
}

void testKidsRoomGetFunctions(){
    KidsRoom Kids1((char*)"buhh", 40, 3, 7, 12);
    KidsRoom Kids2((char*)"Auhhhh", 42, 4, 7, 12);
    KidsRoom Kids3(Kids1);
    
    
    ASSERT_TRUE(Kids1.getAgeLimit() == 12);
    ASSERT_TRUE(Kids2.getAgeLimit() != 10);
    
    ASSERT_TRUE(Kids1.getName() == "buhh");
    
    ASSERT_THROWS(KidsRoomIllegalAgeLimit, Kids1.setNewAgeLimit(-1));
}

void testKidsRoomPrint(){
    KidsRoom Kids1((char*)"buhh", 40, 3, 7, 12);
    KidsRoom Kids2((char*)"Auhhhh", 42, 4, 7, 12);
    KidsRoom Kids3(Kids1);
    
    ASSERT_PRINT("Kids Room: buhh (40/3/7/12)", Kids1);
    ASSERT_PRINT("Kids Room: Auhhhh (42/4/7/12)", Kids2);
    
}


int main/*Kids_test*/() {
    RUN_TEST(testKidsRoomCreate);
    RUN_TEST(testKidsRoomCopy);
    RUN_TEST(testKidsRoomBool);
    RUN_TEST(testKidsRoomGetFunctions);
    RUN_TEST(testKidsRoomPrint);
}
