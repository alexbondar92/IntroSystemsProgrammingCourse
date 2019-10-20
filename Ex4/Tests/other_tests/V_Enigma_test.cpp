/** Created by Dennis on 18-Jun-17.
**/
#include "mtmtest.h"
#include "Enigma.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;
using std::string;
using std::set;

struct enigma_t {
  Enigma e1;
  Enigma e2;
  Enigma e3;
  Enigma e4;
  Enigma e5;
  Enigma e6;
  Enigma e7;
};

static enigma_t setUpEmptySet();

static enigma_t setUp();

static void
AssertParams(const string& s1, const Difficulty& difficulty,
             const int& numOfElements, const Enigma& enigma);

bool testCtorAndCpyCtr() {
  enigma_t enigmasEmpty = setUpEmptySet();

  AssertParams("enigma1", EASY_ENIGMA, 0, enigmasEmpty.e1);
  AssertParams("enigma5", HARD_ENIGMA, 0, enigmasEmpty.e5);
  AssertParams("enigma7", HARD_ENIGMA, 0, enigmasEmpty.e7);

  enigma_t enigmas = setUp();
  AssertParams("enigma4", MEDIUM_ENIGMA, 4, enigmas.e4);
  AssertParams("enigma1", EASY_ENIGMA, 1, enigmas.e1);
  AssertParams("enigma6", HARD_ENIGMA, 6, enigmas.e6);

    string t1[2] = {"hello", "world"};
    set<string> tSet;
    tSet.insert(t1[0]);
    tSet.insert(t1[1]);
  ASSERT_THROWS(EnigmaIllegalSizeParamException,
                Enigma("hi", EASY_ENIGMA, 5, tSet));
  ASSERT_THROWS(EnigmaIllegalSizeParamException,
                Enigma("hi", EASY_ENIGMA, 0, tSet));
  ASSERT_THROWS(EnigmaIllegalSizeParamException,
                Enigma("hi", EASY_ENIGMA, -2, tSet));
  ASSERT_NO_THROW(Enigma("hi", EASY_ENIGMA, 2, tSet));
  Enigma temp("hi", EASY_ENIGMA, 2, tSet);

  AssertParams("hi", EASY_ENIGMA, 2, temp);

  set<string> emptySet;
  Enigma empty("empty", MEDIUM_ENIGMA, 0, emptySet);

  AssertParams("empty", MEDIUM_ENIGMA, 0, empty);
  ASSERT_TRUE(empty.areEqualyComplex(enigmasEmpty.e3));

  return true;
}

bool testIsEqualAndNotEqualOp() {
  enigma_t enigmas = setUpEmptySet();

  ASSERT_TRUE(enigmas.e1 != enigmas.e2);
  ASSERT_TRUE(enigmas.e1 == enigmas.e1);

  Enigma temp("enigma4", EASY_ENIGMA);
  ASSERT_TRUE(enigmas.e4 != temp);

  Enigma temp2("enigma5", HARD_ENIGMA);
  ASSERT_TRUE(enigmas.e5 == temp2);
  ASSERT_TRUE(enigmas.e7 != temp2);

  enigma_t enigmasWithSet = setUp();
    string t2[2] = {"23", "hello"};
  set<string> twoStrSet;
    twoStrSet.insert(t2[0]);
    twoStrSet.insert(t2[1]);
  Enigma temp3("enigma2", EASY_ENIGMA, 2, twoStrSet);
  ASSERT_TRUE(temp3 == enigmasWithSet.e2);
  ASSERT_TRUE(temp3 != enigmasWithSet.e3);

  Enigma temp4("enigma6", HARD_ENIGMA, 2, twoStrSet);
  ASSERT_TRUE(temp4 == enigmasWithSet.e6);
  ASSERT_TRUE(temp4 != temp3);

  return true;
}

bool testGreaterLessThenOp() {
  enigma_t enigmas = setUpEmptySet();

  ASSERT_TRUE(enigmas.e7 > enigmas.e1);
  ASSERT_TRUE(enigmas.e5 > enigmas.e4);
  ASSERT_FALSE(enigmas.e7 > enigmas.e6);
  ASSERT_TRUE(enigmas.e2 < enigmas.e6);
  ASSERT_FALSE(enigmas.e6 < enigmas.e6);

  Enigma temp("enigma3", HARD_ENIGMA);
  ASSERT_TRUE(temp > enigmas.e3);

  enigma_t enigmasWithSet = setUp();

  ASSERT_TRUE(enigmasWithSet.e1 < enigmasWithSet.e7);
  ASSERT_TRUE(enigmasWithSet.e3 < enigmasWithSet.e7);
  ASSERT_TRUE(enigmasWithSet.e4 < enigmasWithSet.e6);
  ASSERT_TRUE(enigmas.e4 > enigmasWithSet.e2);
  ASSERT_FALSE(enigmasWithSet.e6 < enigmasWithSet.e6);

  return true;
}

bool testOsStreamOp() {
  enigma_t enigmas = setUpEmptySet();

  ASSERT_PRINT("enigma1 (0) 0", enigmas.e1);
  ASSERT_PRINT("enigma2 (0) 0", enigmas.e2);
  ASSERT_PRINT("enigma6 (2) 0", enigmas.e6);
  ASSERT_PRINT("enigma4 (1) 0", enigmas.e4);

  enigma_t enigmaWithSet = setUp();

  ASSERT_PRINT("enigma1 (0) 1", enigmaWithSet.e1);
  ASSERT_PRINT("enigma3 (1) 3", enigmaWithSet.e3);
  ASSERT_PRINT("enigma4 (1) 4", enigmaWithSet.e4);
  ASSERT_PRINT("enigma7 (2) 7", enigmaWithSet.e7);
  return true;
}

bool testAreEqualyComplex() {
  enigma_t enigmas = setUpEmptySet();

  Enigma t1("t1", EASY_ENIGMA);

  ASSERT_TRUE(enigmas.e1.areEqualyComplex(t1));
  ASSERT_TRUE(enigmas.e2.areEqualyComplex(t1));

  Enigma t2("enigma7", HARD_ENIGMA);

  ASSERT_TRUE(enigmas.e7.areEqualyComplex(t2));
  ASSERT_TRUE(enigmas.e7.areEqualyComplex(enigmas.e7));
  ASSERT_TRUE(enigmas.e7.areEqualyComplex(enigmas.e6));

  enigma_t enigmaWithSet = setUp();

    string t22[4] = {"1", "2", "3", "4"};
    set<string> fourStrings;
    fourStrings.insert(t22[0]);
    fourStrings.insert(t22[1]);
    fourStrings.insert(t22[2]);
    fourStrings.insert(t22[3]);
  Enigma t3("enigma4", MEDIUM_ENIGMA, 4, fourStrings);

  ASSERT_TRUE(t3.areEqualyComplex(enigmaWithSet.e4));
  ASSERT_FALSE(t3.areEqualyComplex(enigmaWithSet.e6));
  ASSERT_FALSE(t3.areEqualyComplex(enigmaWithSet.e3));

  return true;
}

bool testAddRemoveElements() {
  enigma_t emptyE = setUpEmptySet();

  ASSERT_THROWS(EnigmaNoElementsException, emptyE.e1.removeElement("t1"));

  ASSERT_NO_THROW(emptyE.e1.addElement("t1"));
  ASSERT_NO_THROW(emptyE.e1.removeElement("t1"));
  ASSERT_THROWS(EnigmaNoElementsException, emptyE.e1.removeElement("t1"));

  enigma_t enigmas = setUp();
  ASSERT_NO_THROW(emptyE.e1.addElement("t1"));
  ASSERT_NO_THROW(emptyE.e1.addElement("t1"));

//  ASSERT_TRUE(enigmas.e1.areEqualyComplex(emptyE.e1));
//  ASSERT_FALSE(enigmas.e2.areEqualyComplex(emptyE.e1));

  ASSERT_NO_THROW(emptyE.e1.addElement("t2"));
//  ASSERT_TRUE(enigmas.e2.areEqualyComplex(emptyE.e1));

  ASSERT_NO_THROW(emptyE.e1.addElement("t3"));
  ASSERT_NO_THROW(emptyE.e1.addElement("t4"));
  ASSERT_NO_THROW(emptyE.e1.addElement("t5"));

  ASSERT_TRUE(emptyE.e1 == enigmas.e1);
  ASSERT_TRUE(emptyE.e1 != enigmas.e5);

  ASSERT_NO_THROW(enigmas.e7.removeElement("s5"));
  ASSERT_TRUE(enigmas.e7.areEqualyComplex(enigmas.e6));

  ASSERT_THROWS(EnigmaElementNotFoundException, enigmas.e7.removeElement("s5"));

  ASSERT_PRINT("enigma7 (2) 6", enigmas.e7);
  ASSERT_PRINT("enigma1 (0) 5", emptyE.e1);

  return true;
}

static void
AssertParams(const string& s1, const Difficulty& difficulty,
             const int& numOfElements, const Enigma& enigma) {

  ASSERT_TRUE(s1 == enigma.getName());
  ASSERT_TRUE(difficulty == enigma.getDifficulty());
  set<string> tSet;
  string str("t");
  if (numOfElements > 0) {
    for (int i = 0; i < numOfElements; ++i) {
      str += i;
      tSet.insert(str);
    }
    Enigma temp(s1, difficulty, numOfElements, tSet);
    ASSERT_TRUE(enigma.areEqualyComplex(temp));
  } else {
    Enigma temp(s1, difficulty);
    ASSERT_TRUE(enigma.areEqualyComplex(temp));
  }
}

static enigma_t setUpEmptySet() {
  enigma_t enigmas = {
      Enigma("enigma1", EASY_ENIGMA),
      Enigma("enigma2", EASY_ENIGMA),
      Enigma("enigma3", MEDIUM_ENIGMA),
      Enigma("enigma4", MEDIUM_ENIGMA),
      Enigma("enigma5", HARD_ENIGMA),
      Enigma("enigma6", HARD_ENIGMA),
      Enigma("enigma7", HARD_ENIGMA)
  };
  return enigmas;
}

static enigma_t setUp() {

  set<string> set1;
    set1.insert("s1");
    set<string> set2;
    set2.insert("s1");
    set2.insert("s2");
    set<string> set3;
    set3.insert("s1");
    set3.insert("s2");
    set3.insert("s3");
  set<string> set4;
    set4.insert("s1");
    set4.insert("s2");
    set4.insert("s3");
    set4.insert("s4");
  set<string> set5;
    set5.insert("s1");
    set5.insert("s2");
    set5.insert("s3");
    set5.insert("s4");
    set5.insert("s5");
    set<string> set6;
    set6.insert("s1");
    set6.insert("s2");
    set6.insert("s3");
    set6.insert("s4");
    set6.insert("s5");
    set6.insert("s6");
  set<string> set7;
    set7.insert("s1");
    set7.insert("s2");
    set7.insert("s3");
    set7.insert("s4");
    set7.insert("s5");
    set7.insert("s6");
    set7.insert("s7");

  enigma_t enigmas = {
      Enigma("enigma1", EASY_ENIGMA, 1, set1),
      Enigma("enigma2", EASY_ENIGMA, 2, set2),
      Enigma("enigma3", MEDIUM_ENIGMA, 3, set3),
      Enigma("enigma4", MEDIUM_ENIGMA, 4, set4),
      Enigma("enigma5", HARD_ENIGMA, 5, set5),
      Enigma("enigma6", HARD_ENIGMA, 6, set6),
      Enigma("enigma7", HARD_ENIGMA, 7, set7)
  };
  return enigmas;
}

int main() {
  RUN_TEST(testCtorAndCpyCtr);
  RUN_TEST(testIsEqualAndNotEqualOp);
  RUN_TEST(testGreaterLessThenOp);
  RUN_TEST(testOsStreamOp);
  RUN_TEST(testAreEqualyComplex);
  RUN_TEST(testAddRemoveElements);
  return 0;
}
