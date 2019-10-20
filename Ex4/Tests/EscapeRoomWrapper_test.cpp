#include "../mtmtest.h"
#include <assert.h>
#include "../Exceptions.h"
#include "../EscapeRoomWrapper.h"
#include <string>
#include <list>

using namespace mtm::escaperoom;


void testEscapeRoomWrapperCreate() {
    
    int num1 = 41;
    int num2 = 1;
    
    EscapeRoomWrapper room1((char*)"room1", num1, num2, num2);
    EscapeRoomWrapper room2((char*)"room2", 42, 2, 2);
    
    EscapeRoomWrapper room3((char*)"enigma3", 3);
    EscapeRoomWrapper room4((char*)"enigma4", 4);
    
    EscapeRoomWrapper room5 = EscapeRoomWrapper((char*)"room5", 45, 5, 5);
    EscapeRoomWrapper room6 = EscapeRoomWrapper((char*)"enigma6", 6);
    
}

void testEscapeRoomWrapperCopy(){
    EscapeRoomWrapper room1((char*)"room1", 41, 1, 1);
    EscapeRoomWrapper room2((char*)"room2", 42, 2, 2);
    EscapeRoomWrapper room3((char*)"enigma3", 3);
    
    EscapeRoomWrapper room1_copy(room1);
    EscapeRoomWrapper room2_copy = EscapeRoomWrapper(room2);
    EscapeRoomWrapper room3_copy(room3);
    
}

void testEscapeRoomWrapperBool(){
    EscapeRoomWrapper room1((char*)"room1", 31, 1, 1);
    EscapeRoomWrapper room2((char*)"room2", 32, 2, 2);
    EscapeRoomWrapper room3((char*)"room3", 33, 3, 3);
    EscapeRoomWrapper room4((char*)"room4", 34, 4, 4);
    
    ASSERT_TRUE(room1 == room1);
    ASSERT_FALSE(room1 == room2);
    ASSERT_TRUE(room1 != room3);
    
    ASSERT_TRUE(room1 < room2);
    ASSERT_TRUE(room3 < room4);
    ASSERT_TRUE(room4 > room2);
}

void testEscapeRoomWrapperGetFunctions(){
    EscapeRoomWrapper room1((char*)"room1", 41, 1, 1);
    EscapeRoomWrapper room2((char*)"room2", 42, 2, 2);
    EscapeRoomWrapper room3((char*)"enigma3", 3);
    
    ASSERT_EQUALS(room1.level(), 1);
    ASSERT_EQUALS(room3.level(), 3);
    ASSERT_NOT_EQUAL(room3.level(), 999);
    
    ASSERT_EQUALS(room1.getName(), "room1");
    ASSERT_NOT_EQUAL(room1.getName(), "trulolo");
    
    ASSERT_EQUALS(room3.getMaxTime(), 60);
    ASSERT_EQUALS(room2.getMaxTime(), 42);
    ASSERT_NOT_EQUAL(room1.getMaxTime(), 999);
    
    ASSERT_EQUALS(room1.getMaxParticipants(), 1);
    ASSERT_EQUALS(room3.getMaxParticipants(), 6);
    ASSERT_NOT_EQUAL(room2.getMaxParticipants(), room1.getMaxParticipants());
    
    ASSERT_EQUALS(room1.getRate(), 0);
    ASSERT_NOT_EQUAL(room1.getRate(), 5);

}

void testEscapeRoomWrapperRate(){
    EscapeRoomWrapper room1((char*)"room1", 41, 1, 1);
    EscapeRoomWrapper room2((char*)"room2", 42, 2, 2);
    EscapeRoomWrapper room3((char*)"enigma3", 3);
    
    //   ============= rate can be between 0 to 5 ==============
    ASSERT_EQUALS(room1.getRate(), 0);
    ASSERT_THROWS(EscapeRoomIllegalRateException, room3.rate(-1));
    ASSERT_THROWS(EscapeRoomIllegalRateException, room1.rate(6));
    ASSERT_EQUALS(room1.getRate(), 0);
    
    ASSERT_NO_THROW(room2.rate(2));
    ASSERT_NO_THROW(room2.rate(5));
    ASSERT_EQUALS(room2.getRate(), 3.5);
    ASSERT_NO_THROW(room2.rate(1));
    ASSERT_EQUALS(room2.getRate(), (double)8/3);
    
    room3.rate(3);
    room3.rate(3);
    room3.rate(2);
    ASSERT_EQUALS(room2.getRate(), room3.getRate());
}


void testEscapeRoomWrapperPrint(){
    EscapeRoomWrapper room1((char*)"room1", 41, 1, 1);
    EscapeRoomWrapper room2((char*)"room2", 42, 2, 2);
    EscapeRoomWrapper room3((char*)"enigma3", 3);
    
    ASSERT_PRINT("room1 (41/1/1)", room1);
    ASSERT_PRINT("room2 (42/2/2)", room2);
    ASSERT_PRINT("enigma3 (60/3/6)", room3);
}

void testEscapeRoomWrapperEnigmas(){
    EscapeRoomWrapper room1((char*)"room1", 41, 1, 1);
    EscapeRoomWrapper room2((char*)"room2", 42, 2, 2);
    EscapeRoomWrapper room3((char*)"enigma3", 3);
    
    Enigma enigma1("enigma1", HARD_ENIGMA);
    Enigma enigma2("enigma2", HARD_ENIGMA);
    
    room1.addEnigma(enigma1);
    room1.addEnigma(enigma2);
    
    vector<Enigma> enigmas = room1.getAllEnigmas();
    
}


int main/*EscapeRoomWrapper_test*/() {
    RUN_TEST(testEscapeRoomWrapperCreate);
    RUN_TEST(testEscapeRoomWrapperCopy);
    RUN_TEST(testEscapeRoomWrapperBool);
    RUN_TEST(testEscapeRoomWrapperGetFunctions);
    RUN_TEST(testEscapeRoomWrapperRate);
    RUN_TEST(testEscapeRoomWrapperPrint);
    RUN_TEST(testEscapeRoomWrapperEnigmas);
}
