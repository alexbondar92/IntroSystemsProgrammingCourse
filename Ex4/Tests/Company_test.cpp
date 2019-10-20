#include "../mtmtest.h"
#include <assert.h>
#include "../Exceptions.h"
#include "../Company.h"
#include "../ScaryRoom.h"
#include "../KidsRoom.h"
#include "../Enigma.h"
#include <string>
#include <list>

using namespace mtm::escaperoom;


void testCompanyCreate(){
    Company comp1("TechnionEscape", "177177");
}

void testCompanyCreateRoom(){
    Company comp1("TechnionEscape", "177177");
    comp1.createRoom((char*)"room1", 31, 5, 8);
    comp1.createKidsRoom((char*)"K_room2", 40, 5, 8, 10);
    comp1.createKidsRoom((char*)"K_room3", 41, 4, 83, 12);
    comp1.createScaryRoom((char*)"S_room4", 42, 7, 23, 12, 3);
    comp1.createScaryRoom((char*)"S_room5", 42, 9, 2, 12, 3);
}

void testCompanyRemoveRoom(){
    Company comp1("TechnionEscape", "177177");
    comp1.createRoom((char*)"room1", 31, 5, 8);
    comp1.createKidsRoom((char*)"K_room2", 40, 5, 8, 10);
    comp1.createKidsRoom((char*)"K_room3", 41, 4, 83, 12);
    comp1.createScaryRoom((char*)"S_room4", 42, 7, 23, 12, 3);
    comp1.createScaryRoom((char*)"S_room5", 42, 9, 2, 12, 3);
    
    set<EscapeRoomWrapper*> rooms = comp1.getAllRooms();
    set<EscapeRoomWrapper*>::iterator i = rooms.begin();
    while (i != rooms.end()){
        if ((**i).getName() == "room1"){
            comp1.removeRoom(**i);
            i = rooms.begin();
            rooms = comp1.getAllRooms();
        } else if ((**i).getName() == "K_room3"){
            KidsRoom* tmp_room = dynamic_cast<KidsRoom*>(*i);
            if (tmp_room->getAgeLimit() == 12){
                comp1.removeRoom(**i);
                rooms = comp1.getAllRooms();
            }
            i = rooms.begin();
        } else{
            i++;
        }
    }
    
    ScaryRoom scary1((char*)"buhh", 40, 3, 7, 12, 3);
    
    ASSERT_THROWS(CompanyRoomNotFoundException, comp1.removeRoom(scary1));
    
}

void testCompanyAddEnigma(){
    Company comp1("TechnionEscape", "177177");
    comp1.createRoom((char*)"room1", 31, 5, 8);
    comp1.createKidsRoom((char*)"K_room2", 40, 5, 8, 10);
    comp1.createKidsRoom((char*)"K_room3", 41, 4, 83, 12);
    comp1.createScaryRoom((char*)"S_room4", 42, 7, 23, 12, 3);
    comp1.createScaryRoom((char*)"S_room5", 42, 9, 2, 12, 3);
    
    string tmp("Enigma1");
    
    set<EscapeRoomWrapper*> rooms = comp1.getAllRooms();
    set<EscapeRoomWrapper*>::iterator i = rooms.begin();
    while (i != rooms.end()){
        if ((**i).getName() == "K_room2"){
            comp1.addEnigma(**i, Enigma(tmp, HARD_ENIGMA));
        }
        i++;
    }
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  comp1.addEnigma(ScaryRoom((char*)"buhh", 40, 3, 7, 12, 3),
                                  Enigma(tmp, HARD_ENIGMA)));
}

void testCompanyRemoveEnigma(){
    Company comp1("TechnionEscape", "177177");
    comp1.createRoom((char*)"room1", 31, 5, 8);
    comp1.createKidsRoom((char*)"K_room2", 40, 5, 8, 10);
    comp1.createKidsRoom((char*)"K_room3", 41, 4, 83, 12);
    comp1.createScaryRoom((char*)"S_room4", 42, 7, 23, 12, 3);
    comp1.createScaryRoom((char*)"S_room5", 42, 9, 2, 12, 3);
    
    string tmp("Enigma1");
    
    set<EscapeRoomWrapper*> rooms = comp1.getAllRooms();
    set<EscapeRoomWrapper*>::iterator i = rooms.begin();
    while (i != rooms.end()){
        if ((**i).getName() == "K_room2"){
            comp1.addEnigma(**i, Enigma(tmp, HARD_ENIGMA));
        }
        i++;
    }
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
                  comp1.removeEnigma(KidsRoom((char*)"K_room2", 40, 5, 8, 10),
                                     Enigma("no_correct", HARD_ENIGMA)));
    i = rooms.begin();
    while (i != rooms.end()){
        if ((**i).getName() == "K_room2"){
            comp1.removeEnigma(**i, Enigma(tmp, HARD_ENIGMA));
        }
        i++;
    }
    
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  comp1.removeEnigma(ScaryRoom((char*)"buhh", 40, 3, 7, 12, 3),
                                     Enigma(tmp, HARD_ENIGMA)));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,
                  comp1.removeEnigma(ScaryRoom((char*)"S_room4", 42, 7, 23,12,3),
                                     Enigma(tmp, HARD_ENIGMA)));
}


int main/*Company_test*/() {
    RUN_TEST(testCompanyCreate);
    RUN_TEST(testCompanyCreateRoom);
    RUN_TEST(testCompanyRemoveRoom);
    RUN_TEST(testCompanyAddEnigma);
    RUN_TEST(testCompanyRemoveEnigma);
}
