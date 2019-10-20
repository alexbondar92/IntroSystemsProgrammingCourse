#include "EscapeRoomWrapper.h"
#include "ScaryRoom.h"
#include "KidsRoom.h"
#include "Company.h"
#include "mtmtest.h"
#include <assert.h>
#include "Exceptions.h"

using namespace mtm::escaperoom;


void test1() {

    ASSERT_NO_THROW(Company("c1","1234"));
    ASSERT_NO_THROW(Company("c2","0541234567"));
}

void test2() {
    Company company("c1","1234");
    ASSERT_NO_THROW(company.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(company.createRoom((char *) "r2", 60, 3, 4));
    ASSERT_NO_THROW(company.createRoom((char *) "r3", 60, 5, 6));
    ASSERT_NO_THROW(company.createKidsRoom((char *) "r4", 60, 2, 2,7));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "r5", 60, 2, 2,11,20));
    ASSERT_NO_THROW(company.removeRoom(EscapeRoomWrapper((char*)"r1",60,2,2)));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeRoom(EscapeRoomWrapper((char*)"r1",60,2,2)));
    ASSERT_NO_THROW(company.removeRoom(ScaryRoom((char*)"r5",60,2,2,11,20)));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeRoom(ScaryRoom((char*)"r5",60,2,2,11,20)));

}

void test3() {
    Company company("c1","1234");
    company.createRoom((char *) "r1", 60, 2, 2);
    company.createRoom((char *) "r2", 60, 3, 4);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room2((char *) "r2", 60, 2, 2);
    Enigma enigma1("e1",EASY_ENIGMA);
    Enigma enigma2("e2",HARD_ENIGMA);

    ASSERT_THROWS(CompanyRoomNotFoundException , company.addEnigma(room2, enigma2));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma1));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma2));
    ASSERT_NO_THROW(company.removeEnigma(room1,enigma1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException , company.removeEnigma(room1,enigma1));
    ASSERT_NO_THROW(company.removeEnigma(room1,enigma2));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException , company.removeEnigma(room1,enigma2));
}

void test4() {
    Company company("c1","1234");
    company.createRoom((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room2((char *) "r2", 60, 2, 2);
    Enigma enigma1("e1",EASY_ENIGMA);
    Enigma enigma2("e2",HARD_ENIGMA);

    company.addEnigma(room1,enigma1);
    ASSERT_NO_THROW(company.addItem(room1,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException ,company.addItem(room1,enigma2,"x"));
    ASSERT_THROWS(CompanyRoomNotFoundException ,company.addItem(room2,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomNotFoundException, company.removeItem(room2,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException , company.removeItem(room1,enigma2,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException , company.removeItem(room1,enigma1,"y"));
    ASSERT_NO_THROW(company.removeItem(room1,enigma1,"x"));

    company.addEnigma(room1,enigma2);
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException , company.removeItem(room1,enigma2,"x"));

}

int main() {
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);
}