#include "EscapeRoomWrapper.h"
#include "ScaryRoom.h"
#include "KidsRoom.h"
#include "Company.h"
#include "mtmtest.h"
#include <assert.h>
#include "Exceptions.h"

using namespace mtm::escaperoom;


void testConstructors()
{
    ASSERT_NO_THROW(Company("c1","1"));

    //make full company to copy
    Company* company = new Company("Test", "0");
    company->createRoom((char*)"base1", 20, 1, 2);
    company->createRoom((char*)"base2", 21, 2, 3);
    company->createKidsRoom((char*)"kids1", 10, 2, 3, 9);
    company->createKidsRoom((char*)"kids2", 11, 3, 2, 9);
    company->createScaryRoom((char*)"scary1",30,4,5,10,11);
    company->createScaryRoom((char*)"scary2",31,5,6,11,12);
    EscapeRoomWrapper base[2]={EscapeRoomWrapper((char*)"base1", 20, 1, 2),
                               EscapeRoomWrapper((char*)"base2", 21, 2, 3)};
    KidsRoom kid[2] ={KidsRoom((char*)"kids1", 10, 2, 3, 9),
                               KidsRoom((char*)"kids2", 11, 3, 2, 9)};
    ScaryRoom scary[2] ={ScaryRoom((char*)"scary1",30,4,5,10,11),
                               ScaryRoom((char*)"scary2",31,5,6,11,12)};
    Enigma enigma[3] = { {"1",EASY_ENIGMA},{"2",MEDIUM_ENIGMA},
                         {"3",HARD_ENIGMA} };
    enigma[0].addElement("1");
    enigma[0].addElement("2");
    company->addEnigma(base[1], enigma[0]);
    company->addEnigma(kid[1], enigma[1]);
    company->addEnigma(scary[1], enigma[2]);

    //copy and delete orignal
    Company copy = Company(*company);
    delete(company);

    //check copy
    set<EscapeRoomWrapper*> copy_room = copy.getAllRooms();
    ASSERT_EQUALS(copy_room.size(), 6);
    set<EscapeRoomWrapper*>::iterator it;
    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==base[0]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, base[0]);

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==base[1]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, base[1]);
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[0]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[0]));

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==kid[0]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, kid[0]);

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==kid[1]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, kid[1]);
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[1]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[1]));

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==scary[0]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, scary[0]);

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==scary[1]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, scary[1]);
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));
}

void testAssignment()
{
    //make full company to copy
    Company* company = new Company("Test", "0");
    company->createRoom((char*)"base1", 20, 1, 2);
    company->createRoom((char*)"base2", 21, 2, 3);
    company->createKidsRoom((char*)"kids1", 10, 2, 3, 9);
    company->createKidsRoom((char*)"kids2", 11, 3, 2, 9);
    company->createScaryRoom((char*)"scary1",30,4,5,10,11);
    company->createScaryRoom((char*)"scary2",31,5,6,11,12);
    EscapeRoomWrapper base[2]={EscapeRoomWrapper((char*)"base1", 20, 1, 2),
                               EscapeRoomWrapper((char*)"base2", 21, 2, 3)};
    KidsRoom kid[2] ={KidsRoom((char*)"kids1", 10, 2, 3, 9),
                      KidsRoom((char*)"kids2", 11, 3, 2, 9)};
    ScaryRoom scary[2] ={ScaryRoom((char*)"scary1",30,4,5,10,11),
                         ScaryRoom((char*)"scary2",31,5,6,11,12)};
    Enigma enigma[3] = { {"1",EASY_ENIGMA},{"2",MEDIUM_ENIGMA},
                         {"3",HARD_ENIGMA} };
    enigma[0].addElement("1");
    enigma[0].addElement("2");
    company->addEnigma(base[1], enigma[0]);
    company->addEnigma(kid[1], enigma[1]);
    company->addEnigma(scary[1], enigma[2]);

    //copy and delete orignal
    Company copy = Company("Fail", "5");
    copy = *company;
    delete(company);

    //check copy
    set<EscapeRoomWrapper*> copy_room = copy.getAllRooms();
    ASSERT_EQUALS(copy_room.size(), 6);
    set<EscapeRoomWrapper*>::iterator it;
    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==base[0]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, base[0]);

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==base[1]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, base[1]);
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[0]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[0]));

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==kid[0]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, kid[0]);

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==kid[1]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, kid[1]);
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[1]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[1]));

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==scary[0]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, scary[0]);

    for (it = copy_room.begin(); it != copy_room.end() ; ++it) {
        if(**it==scary[1]) {
            break;
        }
    }
    ASSERT_EQUALS(**it, scary[1]);
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));
}

void testCreateRemoveGetters()
{
    Company company1("c1","1");
    EscapeRoomWrapper room((char *) "1",30,1,10);
    ASSERT_THROWS(CompanyRoomNotFoundException,company1.removeRoom(room));

    //base:
    EscapeRoomWrapper room1((char *) "a",30,1,10);
    EscapeRoomWrapper room2((char *) "b",30,1,10);
    EscapeRoomWrapper room3((char *) "c",30,1,10);

    //scary:
    ScaryRoom room4((char *) "d",30,1,10,10,10);
    ScaryRoom room5((char *) "e",30,1,10,10,10);
    ScaryRoom room6((char *) "f",30,1,10,10,10);

    //kids:
    KidsRoom room7((char *) "g",30,1,10,10);
    KidsRoom room8((char *) "h",30,1,10,10);
    KidsRoom room9((char *) "i",30,1,10,10);

    ASSERT_THROWS(CompanyRoomNotFoundException,company1.getRoomByName("a"));
    //base:
    ASSERT_NO_THROW(company1.createRoom((char *) "a",30,1,10));
    ASSERT_NO_THROW(company1.getRoomByName("a"));
    ASSERT_EQUALS(1, company1.getAllRooms().size());
    ASSERT_EQUALS((*(company1.getAllRooms().begin()))->getName(), "a");
    ASSERT_NO_THROW(company1.createRoom((char *) "b",30,1,10));
    ASSERT_EQUALS(2, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.createRoom((char *) "c",30,1,10));
    ASSERT_EQUALS(3, company1.getAllRooms().size());
    ASSERT_EQUALS(3, company1.getAllRoomsByType(BASE_ROOM).size());
    ASSERT_EQUALS(0, company1.getAllRoomsByType(SCARY_ROOM).size());
    ASSERT_EQUALS(0, company1.getAllRoomsByType(KIDS_ROOM).size());

    ASSERT_EQUALS(*(company1.getRoomByName("a")),room1);
    ASSERT_EQUALS(*(company1.getRoomByName("b")),room2);
    ASSERT_EQUALS(*(company1.getRoomByName("c")),room3);

    ASSERT_THROWS(CompanyRoomNotFoundException,company1.getRoomByName("d"));
    //scary:
    ASSERT_NO_THROW(company1.createScaryRoom((char *) "d",30,1,10,10,10));
    ASSERT_NO_THROW(company1.getRoomByName("d"));
    ASSERT_EQUALS(4, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.createScaryRoom((char *) "e",30,1,10,10,10));
    ASSERT_EQUALS(5, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.createScaryRoom((char *) "f",30,1,10,10,10));
    ASSERT_EQUALS(6, company1.getAllRooms().size());
    ASSERT_EQUALS(3, company1.getAllRoomsByType(BASE_ROOM).size());
    ASSERT_EQUALS(3, company1.getAllRoomsByType(SCARY_ROOM).size());
    ASSERT_EQUALS(0, company1.getAllRoomsByType(KIDS_ROOM).size());

    ASSERT_EQUALS(*(company1.getRoomByName("d")),room4);
    ASSERT_EQUALS(*(company1.getRoomByName("e")),room5);
    ASSERT_EQUALS(*(company1.getRoomByName("f")),room6);

    ASSERT_THROWS(CompanyRoomNotFoundException,company1.getRoomByName("g"));
    //kids:
    ASSERT_NO_THROW(company1.createKidsRoom((char *) "g",30,1,10,10));
    ASSERT_NO_THROW(company1.getRoomByName("g"));
    ASSERT_EQUALS(7, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.createKidsRoom((char *) "h",30,1,10,10));
    ASSERT_EQUALS(8, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.createKidsRoom((char *) "i",30,1,10,10));
    ASSERT_EQUALS(9, company1.getAllRooms().size());
    ASSERT_EQUALS(3, company1.getAllRoomsByType(BASE_ROOM).size());
    ASSERT_EQUALS(3, company1.getAllRoomsByType(SCARY_ROOM).size());
    ASSERT_EQUALS(3, company1.getAllRoomsByType(KIDS_ROOM).size());

    ASSERT_EQUALS(*(company1.getRoomByName("g")),room7);
    ASSERT_EQUALS(*(company1.getRoomByName("h")),room8);
    ASSERT_EQUALS(*(company1.getRoomByName("i")),room9);

    ASSERT_NO_THROW(company1.removeRoom(room1));
    ASSERT_THROWS(CompanyRoomNotFoundException,company1.removeRoom(room1));
    ASSERT_EQUALS(8, company1.getAllRooms().size());
    ASSERT_EQUALS(2, company1.getAllRoomsByType(BASE_ROOM).size());

    ASSERT_NO_THROW(company1.removeRoom(room4));
    ASSERT_THROWS(CompanyRoomNotFoundException,company1.removeRoom(room4));
    ASSERT_EQUALS(7, company1.getAllRooms().size());
    ASSERT_EQUALS(2, company1.getAllRoomsByType(SCARY_ROOM).size());

    ASSERT_NO_THROW(company1.removeRoom(room7));
    ASSERT_THROWS(CompanyRoomNotFoundException,company1.removeRoom(room7));
    ASSERT_EQUALS(6, company1.getAllRooms().size());
    ASSERT_EQUALS(2, company1.getAllRoomsByType(KIDS_ROOM).size());

    ASSERT_NO_THROW(company1.removeRoom(room2));
    ASSERT_EQUALS(5, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.removeRoom(room3));
    ASSERT_EQUALS(4, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.removeRoom(room5));
    ASSERT_EQUALS(3, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.removeRoom(room6));
    ASSERT_EQUALS(2, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.removeRoom(room8));
    ASSERT_EQUALS(1, company1.getAllRooms().size());
    ASSERT_NO_THROW(company1.removeRoom(room9));
    ASSERT_EQUALS(0, company1.getAllRooms().size());
    ASSERT_EQUALS(0, company1.getAllRoomsByType(BASE_ROOM).size());
    ASSERT_EQUALS(0, company1.getAllRoomsByType(SCARY_ROOM).size());
    ASSERT_EQUALS(0, company1.getAllRoomsByType(KIDS_ROOM).size());

    //for valgrind
    ASSERT_NO_THROW(company1.createRoom((char *) "a",30,1,10));
    ASSERT_NO_THROW(company1.createScaryRoom((char *) "b",30,1,10,10,10));
    ASSERT_NO_THROW(company1.createKidsRoom((char *) "c",30,1,10,10));
    ASSERT_EQUALS(3, company1.getAllRooms().size());
}

void testAddEnigma()
{
    Company company("Test", "0");
    company.createRoom((char*)"base1", 20, 1, 2);
    company.createRoom((char*)"base2", 21, 2, 3);
    company.createKidsRoom((char*)"kids1", 10, 2, 3, 9);
    company.createKidsRoom((char*)"kids2", 11, 3, 2, 9);
    company.createScaryRoom((char*)"scary1",30,4,5,10,11);
    company.createScaryRoom((char*)"scary2",31,5,6,11,12);
    EscapeRoomWrapper base[2]={EscapeRoomWrapper((char*)"baseNo1", 20, 1, 2),
                               EscapeRoomWrapper((char*)"base2", 21, 2, 3)};
    KidsRoom kid[2] ={KidsRoom((char*)"kidsNo1", 10, 2, 3, 9),
                      KidsRoom((char*)"kids2", 11, 3, 2, 9)};
    ScaryRoom scary[2] ={ScaryRoom((char*)"scaryNo1",30,4,5,10,11),
                         ScaryRoom((char*)"scary2",31,5,6,11,12)};
    Enigma enigma[3] = { {"1",EASY_ENIGMA},{"2",MEDIUM_ENIGMA},
                         {"3",HARD_ENIGMA} };
    enigma[0].addElement("1");
    enigma[0].addElement("2");
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[0]));
    ASSERT_NO_THROW(company.addEnigma(kid[1], enigma[1]));
    ASSERT_NO_THROW(company.addEnigma(scary[1], enigma[2]));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.addEnigma(base[0], enigma[0]));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.addEnigma(kid[0], enigma[1]));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.addEnigma(scary[0], enigma[2]));

    //check added enigmas
    set<EscapeRoomWrapper*> company_rooms = company.getAllRooms();
    set<EscapeRoomWrapper*>::iterator it;
    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==base[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[0]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[0]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==kid[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[1]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[1]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==scary[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));
}

void testRemoveEnigma()
{
    Company company("Test", "0");
    company.createRoom((char*)"base1", 20, 1, 2);
    company.createRoom((char*)"base2", 21, 2, 3);
    company.createKidsRoom((char*)"kids1", 10, 2, 3, 9);
    company.createKidsRoom((char*)"kids2", 11, 3, 2, 9);
    company.createScaryRoom((char*)"scary1",30,4,5,10,11);
    company.createScaryRoom((char*)"scary2",31,5,6,11,12);
    EscapeRoomWrapper base[2]={EscapeRoomWrapper((char*)"baseNo1", 20, 1, 2),
                               EscapeRoomWrapper((char*)"base2", 21, 2, 3)};
    KidsRoom kid[2] ={KidsRoom((char*)"kids1", 10, 2, 3, 9),
                      KidsRoom((char*)"kids2", 11, 3, 2, 9)};
    ScaryRoom scary[2] ={ScaryRoom((char*)"scary1",30,4,5,10,11),
                         ScaryRoom((char*)"scary2",31,5,6,11,12)};
    Enigma enigma[3] = { {"1",EASY_ENIGMA},{"2",MEDIUM_ENIGMA},
                         {"3",HARD_ENIGMA} };
    enigma[0].addElement("1");
    enigma[0].addElement("2");
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[0]));
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[1]));
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[2]));

    ASSERT_NO_THROW(company.addEnigma(kid[1], enigma[1]));
    ASSERT_NO_THROW(company.addEnigma(kid[1], enigma[2]));

    ASSERT_NO_THROW(company.addEnigma(scary[1], enigma[2]));

    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeEnigma(base[0], enigma[0]));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,company.removeEnigma(kid[0], enigma[0]));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,company.removeEnigma(scary[0], enigma[0]));

    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeEnigma(kid[1], enigma[0]));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeEnigma(scary[1], enigma[0]));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeEnigma(scary[1], enigma[1]));

    ASSERT_NO_THROW(company.removeEnigma(base[1], enigma[1]));
    ASSERT_NO_THROW(company.removeEnigma(base[1], enigma[2]));
    ASSERT_NO_THROW(company.removeEnigma(kid[1], enigma[2]));

    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeEnigma(base[1], enigma[1]));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeEnigma(base[1], enigma[2]));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeEnigma(kid[1], enigma[2]));

    //check enigmas
    set<EscapeRoomWrapper*> company_rooms = company.getAllRooms();
    set<EscapeRoomWrapper*>::iterator it;
    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==base[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[0]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[0]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==kid[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[1]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[1]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==scary[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));

    ASSERT_NO_THROW(company.removeEnigma(base[1], enigma[0]));
    ASSERT_NO_THROW(company.removeEnigma(kid[1], enigma[1]));
    ASSERT_NO_THROW(company.removeEnigma(scary[1], enigma[2]));

    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,company.removeEnigma(base[1], enigma[0]));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,company.removeEnigma(kid[1], enigma[0]));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,company.removeEnigma(scary[1], enigma[0]));
}

void testAddElement()
{
    Company company("Test", "0");
    company.createRoom((char*)"base1", 20, 1, 2);
    company.createRoom((char*)"base2", 21, 2, 3);
    company.createKidsRoom((char*)"kids1", 10, 2, 3, 9);
    company.createKidsRoom((char*)"kids2", 11, 3, 2, 9);
    company.createScaryRoom((char*)"scary1",30,4,5,10,11);
    company.createScaryRoom((char*)"scary2",31,5,6,11,12);
    EscapeRoomWrapper base[2]={EscapeRoomWrapper((char*)"baseNo1", 20, 1, 2),
                               EscapeRoomWrapper((char*)"base2", 21, 2, 3)};
    KidsRoom kid[2] ={KidsRoom((char*)"kidsNo1", 10, 2, 3, 9),
                      KidsRoom((char*)"kids2", 11, 3, 2, 9)};
    ScaryRoom scary[2] ={ScaryRoom((char*)"scaryNo1",30,4,5,10,11),
                         ScaryRoom((char*)"scary2",31,5,6,11,12)};
    Enigma enigma[3] = { {"1",EASY_ENIGMA},{"2",MEDIUM_ENIGMA},
                         {"3",HARD_ENIGMA} };
    enigma[0].addElement("1");
    enigma[0].addElement("2");
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[0]));
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[1]));
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[2]));
    ASSERT_NO_THROW(company.addEnigma(kid[1], enigma[1]));
    ASSERT_NO_THROW(company.addEnigma(scary[1], enigma[2]));

    ASSERT_THROWS(CompanyRoomNotFoundException,company.addItem(kid[0], enigma[1], "1"));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.addItem(scary[0], enigma[2], "1"));

    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.addItem(kid[1], enigma[2], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.addItem(scary[1], enigma[0], "1"));

    ASSERT_NO_THROW(company.addItem(base[1], enigma[0], "3"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[0], "4"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[1], "1"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[1], "2"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[1], "3"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[2], "1"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[2], "2"));
    ASSERT_NO_THROW(company.addItem(kid[1], enigma[1], "1"));
    ASSERT_NO_THROW(company.addItem(kid[1], enigma[1], "2"));
    ASSERT_NO_THROW(company.addItem(kid[1], enigma[1], "3"));
    ASSERT_NO_THROW(company.addItem(scary[1], enigma[2], "1"));
    ASSERT_NO_THROW(company.addItem(scary[1], enigma[2], "2"));

    enigma[0].addElement("11");
    enigma[0].addElement("22");
    enigma[1].addElement("11");
    enigma[1].addElement("22");
    enigma[1].addElement("33");
    enigma[2].addElement("11");
    enigma[2].addElement("22");

    //check added elements
    set<EscapeRoomWrapper*> company_rooms = company.getAllRooms();
    set<EscapeRoomWrapper*>::iterator it;
    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==base[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 3);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));
    ASSERT_NO_THROW((*it)->removeEnigma(enigma[2]));
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 2);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[1]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[1]));
    ASSERT_NO_THROW((*it)->removeEnigma(enigma[1]));
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[0]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[0]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==kid[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[1]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[1]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==scary[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));
}

void testRemoveElement()
{
    Company company("Test", "0");
    company.createRoom((char*)"base1", 20, 1, 2);
    company.createRoom((char*)"base2", 21, 2, 3);
    company.createKidsRoom((char*)"kids1", 10, 2, 3, 9);
    company.createKidsRoom((char*)"kids2", 11, 3, 2, 9);
    company.createScaryRoom((char*)"scary1",30,4,5,10,11);
    company.createScaryRoom((char*)"scary2",31,5,6,11,12);
    EscapeRoomWrapper base[2]={EscapeRoomWrapper((char*)"baseNo1", 20, 1, 2),
                               EscapeRoomWrapper((char*)"base2", 21, 2, 3)};
    KidsRoom kid[2] ={KidsRoom((char*)"kidsNo1", 10, 2, 3, 9),
                      KidsRoom((char*)"kids2", 11, 3, 2, 9)};
    ScaryRoom scary[2] ={ScaryRoom((char*)"scaryNo1",30,4,5,10,11),
                         ScaryRoom((char*)"scary2",31,5,6,11,12)};
    Enigma enigma[3] = { {"1",EASY_ENIGMA},{"2",MEDIUM_ENIGMA},
                         {"3",HARD_ENIGMA} };
    enigma[0].addElement("1");
    enigma[0].addElement("2");
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[0]));
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[1]));
    ASSERT_NO_THROW(company.addEnigma(base[1], enigma[2]));
    ASSERT_NO_THROW(company.addEnigma(kid[1], enigma[1]));
    ASSERT_NO_THROW(company.addEnigma(scary[1], enigma[2]));

    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeItem(kid[0], enigma[1], "1"));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeItem(scary[0], enigma[2], "1"));

    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeItem(kid[1], enigma[2], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeItem(scary[1], enigma[0], "1"));

    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(kid[1], enigma[1], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(scary[1], enigma[2], "1"));

    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[0], "3"));

    ASSERT_NO_THROW(company.addItem(base[1], enigma[0], "3"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[0], "4"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[0], "5"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[1], "1"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[1], "2"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[1], "3"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[2], "1"));
    ASSERT_NO_THROW(company.addItem(base[1], enigma[2], "2"));
    ASSERT_NO_THROW(company.addItem(kid[1], enigma[1], "1"));
    ASSERT_NO_THROW(company.addItem(kid[1], enigma[1], "2"));
    ASSERT_NO_THROW(company.addItem(kid[1], enigma[1], "3"));
    ASSERT_NO_THROW(company.addItem(scary[1], enigma[2], "1"));
    ASSERT_NO_THROW(company.addItem(scary[1], enigma[2], "2"));

    enigma[0].addElement("11");
    enigma[1].addElement("11");
    enigma[1].addElement("22");
    enigma[2].addElement("11");

    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[0], "11"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[1], "11"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[2], "11"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(kid[1], enigma[1], "22"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(scary[1], enigma[2], "11"));

    ASSERT_NO_THROW(company.removeItem(base[1], enigma[0], "1"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[0], "2"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[1], "1"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[2], "1"));
    ASSERT_NO_THROW(company.removeItem(kid[1], enigma[1], "3"));
    ASSERT_NO_THROW(company.removeItem(scary[1], enigma[2], "2"));

    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[0], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[0], "2"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[1], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(base[1], enigma[2], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(kid[1], enigma[1], "3"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,company.removeItem(scary[1], enigma[2], "2"));

    //check elements
    set<EscapeRoomWrapper*> company_rooms = company.getAllRooms();
    set<EscapeRoomWrapper*>::iterator it;
    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==base[1]) {
            break;
        }
    }
    vector<Enigma>::iterator enigma_it;
    vector<Enigma>& room_enigmas = (*it)->getAllEnigmas();
    ASSERT_EQUALS(room_enigmas.size(), 3);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));
    for (enigma_it = room_enigmas.begin(); enigma_it != room_enigmas.end()
            ; ++enigma_it) {
        if (*enigma_it == enigma[1]) {
            break;
        }
    }
    ASSERT_TRUE((*enigma_it).areEqualyComplex(enigma[1]));
    for (enigma_it = room_enigmas.begin(); enigma_it != room_enigmas.end()
            ; ++enigma_it) {
        if (*enigma_it == enigma[0]) {
            break;
        }
    }
    ASSERT_TRUE((*enigma_it).areEqualyComplex(enigma[0]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==kid[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[1]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[1]));

    for (it = company_rooms.begin(); it != company_rooms.end() ; ++it) {
        if(**it==scary[1]) {
            break;
        }
    }
    ASSERT_EQUALS((*it)->getAllEnigmas().size(), 1);
    ASSERT_EQUALS((*it)->getHardestEnigma(), enigma[2]);
    ASSERT_TRUE((*it)->getHardestEnigma().areEqualyComplex(enigma[2]));

    ASSERT_NO_THROW(company.removeItem(base[1], enigma[0], "3"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[0], "4"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[0], "5"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[1], "2"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[1], "3"));
    ASSERT_NO_THROW(company.removeItem(base[1], enigma[2], "2"));
    ASSERT_NO_THROW(company.removeItem(kid[1], enigma[1], "1"));
    ASSERT_NO_THROW(company.removeItem(kid[1], enigma[1], "2"));
    ASSERT_NO_THROW(company.removeItem(scary[1], enigma[2], "1"));

    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(base[1], enigma[0], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(base[1], enigma[1], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(base[1], enigma[2], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(kid[1], enigma[1], "1"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(scary[1], enigma[2], "1"));
}

void testPrints()
{
    std::ostringstream output;
    EscapeRoomWrapper base((char*)"base1", 20, 1, 2);
    KidsRoom kid((char*)"kids1", 10, 2, 3, 9);
    ScaryRoom scary((char*)"scary1",30,4,5,10,11);

    Company company("Test", "0");
    company.createRoom((char*)"base1", 20, 1, 2);
    output << "Test : 0" << std::endl << base << std::endl;
    ASSERT_PRINT(output.str(), company);
    output.str("");
    company.removeRoom(base);

    company.createKidsRoom((char*)"kids1", 10, 2, 3, 9);
    output << "Test : 0" << std::endl << kid << std::endl;
    ASSERT_PRINT(output.str(), company);
    output.str("");
    company.removeRoom(kid);

    company.createScaryRoom((char*)"scary1",30,4,5,10,11);
    output << "Test : 0" << std::endl << scary << std::endl;
    ASSERT_PRINT(output.str(), company);
    output.str("");
    company.removeRoom(scary);

    output << "Test : 0" << std::endl;
    ASSERT_PRINT(output.str(),company);
}

int main() {
    RUN_TEST(testConstructors);
    RUN_TEST(testAssignment);
    RUN_TEST(testAddEnigma);
    RUN_TEST(testRemoveEnigma);
    RUN_TEST(testAddElement);
    RUN_TEST(testRemoveElement);
    RUN_TEST(testPrints);
    RUN_TEST(testCreateRemoveGetters);
}
