#include "../mtmtest.h"
#include <assert.h>
#include "../Exceptions.h"
#include "../Enigma.h"
#include <string>


using namespace mtm::escaperoom;
using mtm::MtmException;
using std::cout;
using std::set;

void testEnigmaCreate() {

    string str1("mystery1");
    string str2("mystery2");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }
    set<string> strings2 = set<string>();
    string tmp2[20] = {"1","2","3","4","5","6","7","8","9","10", "11","12","13",
        "14","15","16","17","18","19","20"};
    for (int i=0; i<20; i++){
        strings2.insert(tmp2[i]);
    }
    
    Enigma enigma1(str1,HARD_ENIGMA, 10, strings1);
    Enigma enigma2 = Enigma(str2, MEDIUM_ENIGMA, 20, strings2);
    ASSERT_THROWS(EnigmaIllegalSizeParamException, Enigma(str2, MEDIUM_ENIGMA,
                                                          20, strings1));
}

void testEnigmaCopy(){
    string str1("mystery1");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }
    
    Enigma enigma1(str1, EASY_ENIGMA, 10, strings1);
    Enigma copied_enigma = Enigma(enigma1);
    
    Enigma enigma1_1 = copied_enigma;
}

void testEnigmaBool(){
    string str1("mystery1");
    string str2("mystery2");
    string str3("mystery3");
    string str4("mystery4");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }

    
    Enigma enigma1(str1,HARD_ENIGMA, 10, strings1);
    Enigma enigma2(str2,HARD_ENIGMA, 10, strings1);
    strings1.insert(string("11"));
    strings1.insert(string("12"));
    Enigma enigma3(str3,MEDIUM_ENIGMA, 12, strings1);
    strings1.insert(string("13"));
    strings1.insert(string("14"));
    strings1.insert(string("15"));
    Enigma enigma4(str4,EASY_ENIGMA, 15,strings1);
    ASSERT_TRUE(enigma1 != enigma2);
    ASSERT_TRUE(enigma1 == Enigma(str1, HARD_ENIGMA, 15, strings1));
    ASSERT_TRUE(enigma2 != Enigma(str2, MEDIUM_ENIGMA,15,strings1));
    
    ASSERT_TRUE(enigma3 < enigma1);
    ASSERT_TRUE(enigma2 > enigma3);
    ASSERT_TRUE(enigma4 != enigma3);
    ASSERT_TRUE(enigma3 == enigma3);
}

void testAreEqualyComplex(){
    string str1("mystery1");
    string str2("mystery2");
    string str3("mystery3");
    string str4("mystery4");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }
    
    Enigma enigma1(str1,HARD_ENIGMA, 10, strings1);
    Enigma enigma2(str2,HARD_ENIGMA, 10, strings1);
    strings1.insert(string("11"));
    strings1.insert(string("12"));
    Enigma enigma3(str3,MEDIUM_ENIGMA, 12, strings1);
    strings1.insert(string("13"));
    strings1.insert(string("14"));
    strings1.insert(string("15"));
    Enigma enigma4(str4,EASY_ENIGMA, 15, strings1);
    
    ASSERT_TRUE(enigma1.areEqualyComplex(enigma2));
    ASSERT_FALSE(enigma1.areEqualyComplex(enigma3));
    ASSERT_TRUE(enigma1.areEqualyComplex(enigma1));
}

void testEnigmaGetFunctions(){
    string str1("mystery1");
    string str2("mystery2");
    string str3("mystery3");
    string str4("mystery4");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }
    
    Enigma enigma1(str1,HARD_ENIGMA, 10, strings1);
    Enigma enigma2(str2,HARD_ENIGMA, 10, strings1);
    strings1.insert(string("11"));
    strings1.insert(string("12"));
    Enigma enigma3(str3,MEDIUM_ENIGMA, 12, strings1);
    strings1.insert(string("13"));
    strings1.insert(string("14"));
    strings1.insert(string("15"));
    Enigma enigma4(str4,EASY_ENIGMA, 15, strings1);
    
    ASSERT_EQUALS(enigma1.getName(), str1);
    ASSERT_NOT_EQUAL(enigma1.getName(), enigma2.getName());

    ASSERT_EQUALS(enigma1.getDifficulty(), enigma2.getDifficulty());
    ASSERT_NOT_EQUAL(enigma3.getDifficulty(), enigma4.getDifficulty());
}

void testEnigmaPrint(){
    string str1("mystery1");
    string str2("mystery2");
    string str3("mystery3");
    string str4("mystery4");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }
    
    Enigma enigma1(str1,HARD_ENIGMA, 10, strings1);
    Enigma enigma2(str2,HARD_ENIGMA, 10, strings1);
    strings1.insert(string("11"));
    strings1.insert(string("12"));
    Enigma enigma3(str3,MEDIUM_ENIGMA, 12, strings1);
    strings1.insert(string("13"));
    strings1.insert(string("14"));
    strings1.insert(string("15"));
    Enigma enigma4(str4,EASY_ENIGMA, 15, strings1);
    
    ASSERT_PRINT("mystery1 (2) 10", enigma1);
    ASSERT_PRINT("mystery2 (2) 10", enigma2);
    ASSERT_PRINT("mystery3 (1) 12", enigma3);
    ASSERT_PRINT("mystery4 (0) 15", enigma4);
}


void testEnigmaAddElement(){
    string str1("mystery1");
    string str2("mystery2");
    string str3("mystery3");
    string str4("mystery4");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }
    
    Enigma enigma1(str1,HARD_ENIGMA, 10, strings1);
    Enigma enigma2(str2,HARD_ENIGMA, 10, strings1);
    strings1.insert(string("11"));
    strings1.insert(string("12"));
    Enigma enigma3(str3,MEDIUM_ENIGMA, 12, strings1);
    strings1.insert(string("13"));
    strings1.insert(string("14"));
    strings1.insert(string("15"));
    Enigma enigma4(str4,EASY_ENIGMA, 15, strings1);
    
    enigma1.addElement("11");
    ASSERT_PRINT("mystery1 (2) 11", enigma1);
    enigma4.addElement("16");
    ASSERT_PRINT("mystery4 (0) 16", enigma4);
}

void testEnigmaRemoveElement(){
    string str1("mystery1");
    string str2("mystery2");
    string str3("mystery3");
    string str4("mystery4");
    set<string> strings1 = set<string>();
    string tmp1[10] = {"1","2","3","4","5","6","7","8","9","10"};
    for (int i=0; i<10; i++){
        strings1.insert(tmp1[i]);
    }
    
    Enigma enigma1(str1,HARD_ENIGMA, 10, strings1);
    Enigma enigma2(str2,HARD_ENIGMA, 10, strings1);
    strings1.insert(string("11"));
    strings1.insert(string("12"));
    Enigma enigma3(str3,MEDIUM_ENIGMA, 12, strings1);
    strings1.insert(string("13"));
    strings1.insert(string("14"));
    strings1.insert(string("15"));
    Enigma enigma4(str4,EASY_ENIGMA, 15, strings1);
    
    for (int i=0; i<10; i++){
        enigma1.removeElement(tmp1[i]);
    }

    ASSERT_PRINT("mystery1 (2) 0", enigma1);
    
    ASSERT_THROWS(EnigmaNoElementsException, enigma1.removeElement("1"));
    
    ASSERT_THROWS(EnigmaElementNotFoundException, enigma2.removeElement("20"));
}


int main/*Enigma_test*/() {
    RUN_TEST(testEnigmaCreate);
    RUN_TEST(testEnigmaCopy);
    RUN_TEST(testEnigmaBool);
    RUN_TEST(testAreEqualyComplex);
    RUN_TEST(testEnigmaGetFunctions);
    RUN_TEST(testEnigmaPrint);
    RUN_TEST(testEnigmaAddElement);
    RUN_TEST(testEnigmaRemoveElement);
}
