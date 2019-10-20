#include "../mtmtest.h"
#include <assert.h>
#include "../Exceptions.h"
#include "../ScaryRoom.h"
#include <string>
#include <list>

using namespace mtm::escaperoom;


void testScaryRoomCreate() {
    ScaryRoom scary1((char*)"buhh", 40, 3, 7, 12, 3);
}

void testScaryRoomCopy(){
    ScaryRoom scary1((char*)"buhh", 40, 3, 7, 12, 3);
    ScaryRoom scary2(scary1);
    
    ASSERT_TRUE(scary1 == scary2);
}

void testScaryRoomBool(){
    ScaryRoom scary1((char*)"buhh", 40, 3, 7, 12, 3);
    ScaryRoom scary2((char*)"Auhhhh", 42, 4, 7, 12, 3);
    ScaryRoom scary3(scary1);
    
    ASSERT_TRUE(scary1 == scary3);
    ASSERT_FALSE(scary1 == scary2);
}

void testScaryRoomGetFunctions(){
    ScaryRoom scary1((char*)"buhh", 40, 3, 7, 12, 3);
    ScaryRoom scary2((char*)"Auhhhh", 42, 4, 7, 12, 3);
    ScaryRoom scary3(scary1);
    
    
    ASSERT_TRUE(scary1.getAgeLimit() == 12);
    ASSERT_TRUE(scary2.getAgeLimit() != 10);
    
    ASSERT_TRUE(scary1.getName() == "buhh");
    
    ASSERT_THROWS(ScaryRoomIllegalAgeLimit, scary1.setNewAgeLimit(-1));
}

void testScaryRoomPrint(){
    ScaryRoom scary1((char*)"buhh", 40, 3, 7, 12, 3);
    ScaryRoom scary2((char*)"Auhhhh", 42, 4, 7, 12, 3);
    ScaryRoom scary3(scary1);
    
    ASSERT_PRINT("Scary Room: buhh (40/3/7/12)", scary1);
    ASSERT_PRINT("Scary Room: Auhhhh (42/4/7/12)", scary2);

}


int main/*Scary_test*/() {
    RUN_TEST(testScaryRoomCreate);
    RUN_TEST(testScaryRoomCopy);
    RUN_TEST(testScaryRoomBool);
    RUN_TEST(testScaryRoomGetFunctions);
    RUN_TEST(testScaryRoomPrint);
}
