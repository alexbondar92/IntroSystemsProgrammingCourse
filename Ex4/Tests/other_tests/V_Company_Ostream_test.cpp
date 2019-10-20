/** Created by Dennis on 24-Jun-17.
**/

#include "../mtmtest.h"
#include "../KidsRoom.h"
#include "../ScaryRoom.h"
#include "../Company.h"

using namespace mtm::escaperoom;

struct kids_t {
  KidsRoom k1;
  KidsRoom k2;
  KidsRoom k3;
  KidsRoom k4;
  KidsRoom k5;
  KidsRoom k6;
  KidsRoom k7;
};

struct scary_t {
  ScaryRoom s1;
  ScaryRoom s2;
  ScaryRoom s3;
  ScaryRoom s4;
  ScaryRoom s5;
  ScaryRoom s6;
  ScaryRoom s7;
};

struct company_t {
  Company c1;
  Company c2;
  Company c3;
  Company c4;
  Company c5;
  Company c6;
  Company c7;
};

struct wrapper_t {
  EscapeRoomWrapper w1;
  EscapeRoomWrapper w2;
  EscapeRoomWrapper w3;
  EscapeRoomWrapper w4;
  EscapeRoomWrapper w5;
  EscapeRoomWrapper w6;
  EscapeRoomWrapper w7;
};

static wrapper_t setUpWrapper() {
  wrapper_t wrapper = {
      EscapeRoomWrapper((char*) "wrapper1", 30, 1, 10),
      EscapeRoomWrapper((char*) "wrapper2", 40, 2, 20),
      EscapeRoomWrapper((char*) "wrapper3", 50, 3, 30),
      EscapeRoomWrapper((char*) "wrapper4", 60, 4, 40),
      EscapeRoomWrapper((char*) "wrapper5", 70, 5, 50),
      EscapeRoomWrapper((char*) "wrapper6", 80, 6, 60),
      EscapeRoomWrapper((char*) "wrapper7", 90, 7, 70)
  };
  return wrapper;
}

static kids_t setUpKidsRooms() {
  kids_t kidsRooms = {
      KidsRoom((char*) "kids1", 30, 1, 10, 100),
      KidsRoom((char*) "kids2", 40, 2, 20, 200),
      KidsRoom((char*) "kids3", 50, 3, 30, 300),
      KidsRoom((char*) "kids4", 60, 4, 40, 400),
      KidsRoom((char*) "kids5", 70, 5, 50, 500),
      KidsRoom((char*) "kids6", 80, 6, 60, 600),
      KidsRoom((char*) "kids7", 90, 7, 70, 700)
  };
  return kidsRooms;
}

static scary_t setUpScaryRooms() {
  scary_t scaryRooms = {
      ScaryRoom((char*) "scary1", 30, 1, 10, 100, 1),
      ScaryRoom((char*) "scary2", 40, 2, 20, 200, 10),
      ScaryRoom((char*) "scary3", 50, 3, 30, 300, 100),
      ScaryRoom((char*) "scary4", 60, 4, 40, 400, 1000),
      ScaryRoom((char*) "scary5", 70, 5, 50, 500, 10000),
      ScaryRoom((char*) "scary6", 80, 6, 60, 600, 100000),
      ScaryRoom((char*) "scary7", 90, 7, 70, 700, 1000000),
  };
  return scaryRooms;
}

static company_t setUpCompanies() {
  company_t companies = {
      Company("company1", "phone1"),
      Company("company2", "phone2"),
      Company("company3", "phone3"),
      Company("company4", "phone4"),
      Company("company5", "phone5"),
      Company("company6", "phone6"),
      Company("company7", "phone7")
  };
  return companies;
}

bool testOsStreamOp() {
  company_t companies = setUpCompanies();
  kids_t kids = setUpKidsRooms();
  scary_t scary = setUpScaryRooms();
  wrapper_t wrapper = setUpWrapper();

  ASSERT_NO_THROW(companies.c7.createRoom((char*) "wrapper1", 30, 1, 10));
  ASSERT_NO_THROW(companies.c7.createRoom((char*) "wrapper2", 40, 2, 20));
  ASSERT_NO_THROW(companies.c7.createRoom((char*) "wrapper3", 50, 3, 30));

  ASSERT_NO_THROW(companies.c7.createKidsRoom((char*) "kids1", 30, 1, 10, 100));
  ASSERT_NO_THROW(companies.c7.createKidsRoom((char*) "kids2", 40, 2, 20, 200));
  ASSERT_NO_THROW(companies.c7.createKidsRoom((char*) "kids3", 50, 3, 30, 300));

  ASSERT_NO_THROW(companies.c7.createScaryRoom((char*) "scary1", 30, 1, 10,
                                               100, 1));
  ASSERT_NO_THROW(companies.c7.createScaryRoom((char*) "scary2", 40, 2, 20,
                                               200, 10));
  ASSERT_NO_THROW(companies.c7.createScaryRoom((char*) "scary3", 50, 3, 30,
                                               300, 100));

  std::cout << companies.c7;
 ASSERT_PRINT("company7 : phone7\n"
                  "wrapper1 (30/1/10)\n"
                  "wrapper2 (40/2/20)\n"
                  "wrapper3 (50/3/30)\n"
                  "Kids Room: kids1 (30/1/10/100)\n"
                  "Kids Room: kids2 (40/2/20/200)\n"
                  "Kids Room: kids3 (50/3/30/300)\n"
                  "Scary Room: scary1 (30/1/10/100)\n"
                  "Scary Room: scary2 (40/2/20/200)\n"
                  "Scary Room: scary3 (50/3/30/300)\n", companies.c7);

 ASSERT_PRINT("company1 : phone1\n", companies.c1);

  return true;
}

int main() {
  RUN_TEST(testOsStreamOp);
  return 0;
}
