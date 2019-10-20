#include <stdio.h>
#include "../list.h"
#include "../mtmtest.h"
#include <assert.h>
#include "../Exceptions.h"


using std::cout;
using std::string;

void testListCreate() {
    List<int> list1;
    List<string> list2;
    
    List<int> list3;
    list1 = list3;
}

void testListCopy(){
    List<int> list1;
    List<int> list2(list1);
    
    List<string> list3;
    List<string> list4(list3);
}

void testListInsert(){
    List<int> list1;
    int num = 1;
    list1.insert(num, list1.begin());
    List<int>::Iterator p = list1.end();
    for(int i =2; i<20; i++){
        list1.insert(i, p);
        p = list1.end();
    }
    int i=1;
    for (p = list1.begin(); p != list1.end();p++){
        ASSERT_TRUE(*p == i);
        i++;
    }
}

void testListRemove(){
    List<int> list1;
    List<int>::Iterator p = list1.begin();
    for(int i =5; i<20; i++){
        list1.insert(i, p);
    }
    p = list1.begin();
    list1.remove(p);
    
    p = list1.begin();
    while(p != list1.end()){
        list1.remove(p);
        p = list1.begin();
    }
    
    
    p = list1.begin();
    ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list1.remove(p));
    list1.insert(1000, list1.begin());
}

class findNumberTen{
public:
    bool operator()(int number) const{
        return number == 10;
    }
};

void testListFind(){
    List<int> list1;
   List<int>::Iterator p = list1.begin();
    for(int i =5; i<20; i++){
        list1.insert(i, p);
    }
    p = list1.find(findNumberTen());
    ASSERT_EQUALS(10, *p);
}

class sortBigtoSmall{
public:
    bool operator()(int num1, int num2) const{
        return (num1 >= num2)? true : false;
    }
};

void testListSort(){
    List<int> list1;
    List<int>::Iterator p = list1.begin();
    for(int i =5; i<20; i++){
        list1.insert(i, p);
    }
    
    list1.sort(sortBigtoSmall());
    p = list1.begin();
    for(int i =19; 5 <= i; i--){
        ASSERT_EQUALS(i, *p);
        p++;
    }
}

void testListEqual(){
    List<int> list1;
    List<int> list2;
    List<int> list3;
    ASSERT_TRUE(list1 == list2);
    
    list1.insert(10);
    list2.insert(10);
    ASSERT_TRUE(list1 == list2);
    ASSERT_TRUE(list1 != list3);
    
    list1.insert(20);
    ASSERT_TRUE(list1 != list2);
    list2.insert(20);
    ASSERT_TRUE(list1 == list2);
}

int main/*Enigma_test*/() {
    RUN_TEST(testListCreate);
    RUN_TEST(testListCopy);
    RUN_TEST(testListInsert);
    RUN_TEST(testListRemove);
    RUN_TEST(testListFind);
    RUN_TEST(testListSort);
    RUN_TEST(testListEqual);
}


