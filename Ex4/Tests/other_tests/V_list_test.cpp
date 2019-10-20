//
// Created by masha on 20-Jun-17.
//
#include <iostream>
#include <cmath>
#include "../mtmtest.h"
#include "../list.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;
using mtm::ListExceptions::ElementNotFound;


class EqualTo {
private:
    int target;
    string str;
public:
    EqualTo(int i) : target(i) {}
    EqualTo(string str) : str(str) {}

    bool operator()(const int &i) const {
        return i == target;
    }
    bool operator()(const string& i) const {
        return i == str;
    }
};


/**
 * Use to add @param num_of_elem to List<string>
 * @param func "sin" or "cos", use to make different lists
 */
void addToListString(List<string> &list, int num_of_elem, string func) {
    if (func == "sin") {
        for (int i = 1; i <= num_of_elem; ++i) {
            string s = string(std::to_string(sin(i)));
            list.insert(s);
        }
    } else{
        for (int i = 1; i <= num_of_elem; ++i) {
            string s = string(std::to_string(cos(i)));
            list.insert(s);
        }
    }
}

/**
 * Use to add @param num_of_elem to List<double>
 * @param func "sin" or "cos", use to make different lists
 */
void addToListDouble(List<double> &list, int num_of_elem, string func) {
    if (func == "sin"){
        for (int i = 1; i <= num_of_elem; ++i) {
            list.insert(sin(i));
        }
    } else{
        for (int i = 1; i <= num_of_elem; ++i) {
            list.insert(cos(i));
        }
    }
}

bool listCtorTest(){
    List<int> list_int;
    ASSERT_TRUE(list_int.getSize() == 0);
    ASSERT_TRUE(list_int.begin() == list_int.end());
    List<double> list_double;
    ASSERT_TRUE(list_double.getSize() == 0);
    List<char> list_char;
    ASSERT_TRUE(list_char.getSize() == 0);
    List<string> list_string;
    ASSERT_TRUE(list_string.getSize() == 0);
    ASSERT_TRUE(list_string.begin() == list_string.end());
    return true;
}

bool listCopyCtorTest(){
    List<int> list_int;
    for (int i = 0; i < 7; ++i) {
        list_int.insert(i);
    }
    List<int> list_int_cp(list_int);
    ASSERT_TRUE(list_int == list_int_cp);
    List<int>::Iterator it2 = list_int_cp.begin();
    for (List<int>::Iterator it1 = list_int.begin();
         it1 != list_int.end(); ++it1) {
        ASSERT_TRUE(*it1 == *it2);
        ++it2;
    }

    List<string> list_string;
    addToListString(list_string, 7, "sin");
    List<string> list_string_cp(list_string);
    ASSERT_TRUE(list_string == list_string_cp);
    List<string>::Iterator it3 = list_string_cp.begin();
    for (List<string>::Iterator it4 = list_string.begin();
         it4 != list_string.end(); ++it4) {
        ASSERT_TRUE(*it3 == *it4);
        ++it3;
    }
    ASSERT_TRUE(it3 == list_string_cp.end());
    return true;
}

bool ListAssignOpTest(){
    List<double> list_double1;
    list_double1 = list_double1;
    addToListDouble(list_double1, 10, "cos");
    List<double > list_double2;
    addToListDouble(list_double2, 10, "sin");
    list_double1 = list_double2;
    ASSERT_TRUE(list_double1 == list_double2);
    addToListDouble(list_double1, 4, "sin");
    list_double1 = list_double2;
    ASSERT_TRUE(list_double1 == list_double2);
    list_double1 = list_double1;
    ASSERT_TRUE(list_double1 == list_double1);

    return true;
}

bool ListBeginEndTest(){
    List<int> list_int;
    ASSERT_TRUE(list_int.begin() == list_int.end());
    ASSERT_NO_THROW(list_int.begin());
    list_int.insert(1);
    ASSERT_TRUE(*list_int.begin() == 1);
    ASSERT_THROWS(ElementNotFound, *list_int.end());

    List<string> list_string;
    addToListString(list_string, 200, "cos");
    ASSERT_TRUE(*(list_string.begin()) == to_string(cos(1)));
    ASSERT_THROWS(ElementNotFound, *list_string.end());

    return true;
}

bool listInsertTest(){
    //***int***
    List<int> list_int;
    ASSERT_TRUE(list_int.getSize() == 0);
    list_int.insert(1, list_int.end());
    ASSERT_TRUE(list_int.getSize() == 1);
    ASSERT_TRUE(*list_int.begin() == 1);

    list_int.insert(2);
    ASSERT_TRUE(list_int.getSize() == 2);
    List<int>::Iterator it = list_int.begin();
    ASSERT_TRUE(*it == 1);
    ASSERT_TRUE(*++it == 2);

    list_int.insert(3, list_int.begin());
    it = --list_int.begin();
    ASSERT_TRUE(list_int.getSize() == 3);
    it = list_int.begin();
    ASSERT_TRUE(*list_int.begin() == 3);
    ASSERT_TRUE(*++it == 1);
    ASSERT_TRUE(*++it == 2);
    ASSERT_THROWS(ElementNotFound, *++it);

    it = list_int.begin();
    for (int j = 0; j < 2; ++j) {
        ++it;
    }
    list_int.insert(4, it);
    ASSERT_TRUE(list_int.getSize() == 4);
    it = list_int.begin();
    for (int j = 0; j < 2; ++j) {
        ++it;
    }
    ASSERT_TRUE(*it == 4);
    ASSERT_TRUE(*++it == 2);
    ASSERT_TRUE(*--(--it) == 1);
    ASSERT_THROWS(ElementNotFound, *----it);
    ASSERT_NO_THROW(list_int.insert(3, it));

    //***string***
    List<string> list_string;
    ASSERT_TRUE(list_string.getSize() == 0);
    string s1 = "str1";
    list_string.insert("str1", list_string.end());

    ASSERT_TRUE(list_string.getSize() == 1);
    ASSERT_TRUE(*list_string.begin() == s1);

    string s2 = "str2";
    list_string.insert(s2);
    ASSERT_TRUE(list_string.getSize() == 2);

    string s3 = "str3";
    list_string.insert(s3, list_string.begin());
    ASSERT_TRUE(list_string.getSize() == 3);
    ASSERT_TRUE(*list_string.begin() == s3);

    List<string>::Iterator its = list_string.begin();
    for (int j = 0; j < 2; ++j) {
        ++its;
    }
    string s4 = "str4";
    list_string.insert(s4, its);
    ASSERT_TRUE(list_string.getSize() == 4);
    its = list_string.begin();
    for (int j = 0; j < 2; ++j) {
        ++its;
    }
    ASSERT_TRUE(*its == s4);
    ASSERT_TRUE(*(++its) == s2);
    ASSERT_TRUE(*--(--its) == s1);
    ASSERT_TRUE(*its++ == s1);
    ASSERT_TRUE(*its == s4);
    ASSERT_TRUE(++++its == list_string.end());
    ASSERT_TRUE(list_string.begin() != its);
    ASSERT_NO_THROW(list_string.insert("d2", --list_string.begin()));
    List<string> big_list;
    ASSERT_THROWS(ElementNotFound, big_list.insert("s", list_string.begin()));
    addToListString(big_list, 5000, "sin");
    ASSERT_TRUE(big_list.getSize() == 5000);
    return true;
}

bool removeListTest(){
    List<int> list_int;
    ASSERT_THROWS(ElementNotFound, list_int.remove(list_int.begin()));
    for (int i = 0; i < 10; ++i) {
        list_int.insert(i);
    }
    ASSERT_TRUE(list_int.getSize() == 10);
    list_int.remove(list_int.begin());
    ASSERT_TRUE(list_int.getSize() == 9);
    ASSERT_TRUE(*list_int.begin() == 1);
    List<int> list_int2;
    ASSERT_THROWS(ElementNotFound, list_int.remove(list_int2.begin()));
    list_int2.insert(2);
    ASSERT_THROWS(ElementNotFound, list_int.remove(list_int2.begin()));

    List<int> list;
    for (int l = 0; l < 200; ++l) {
        list.insert(l);
    }
    ASSERT_TRUE(list.getSize() == 200);
    for (int l = 0; l < 200; ++l) {
        list.remove(list.begin());
    }
    ASSERT_TRUE(list.getSize() == 0);

    List<double> list_double;
    for (double j = 0.5; j < 3.4; j+=0.5) {
        list_double.insert(j);
    }
    ASSERT_TRUE(list_double.getSize() == 6);
    List<double>::Iterator itd = list_double.begin();
    for (int k = 1; k <= 3; ++k) {
        itd++;
    }
    list_double.remove(itd);
    ASSERT_TRUE(list_double.getSize() == 5);
    itd = list_double.begin();
    for (int k = 2; k <= 3; ++k) {
        itd++;
    }
    ASSERT_TRUE(*itd == 1.5);
    ASSERT_TRUE(*++itd == 2.5);

    List<string> list_string;
    addToListString(list_string, 5000, "cos");
    ASSERT_TRUE(list_string.getSize() == 5000);
    list_string.sort(std::less<string>());
    for (int m = 0; m < 5000; ++m) {
        list_string.remove(list_string.begin());
    }
    ASSERT_TRUE(list_string.getSize() == 0);
    ASSERT_TRUE(list_string.begin() == list_string.end());

    return true;
}

bool ListEqualNotEqualOpTest(){
    List<double > list_d1;
    addToListDouble(list_d1, 1000, "cos");
    List<double > list_d2;
    addToListDouble(list_d2, 1000, "cos");
    ASSERT_TRUE(list_d1 == list_d2);
    ASSERT_FALSE(list_d1 != list_d2);
    list_d2.insert(2.12);
    ASSERT_TRUE(list_d1 != list_d2);
    ASSERT_FALSE(list_d1 == list_d2);

    ASSERT_TRUE(list_d1 == list_d1);

    list_d1 = list_d2;
    ASSERT_TRUE(list_d1 == list_d2);
    list_d1.remove(list_d1.begin());
    ASSERT_TRUE(list_d1 != list_d2);

    List<string> list_s1;
    ASSERT_TRUE(list_s1 == list_s1);
    addToListString(list_s1, 200, "sin");
    List<string> list_s2;
    addToListString(list_s2, 200, "sin");
    ASSERT_TRUE(list_s1 == list_s2);
    List<string>::Iterator it = list_s1.begin();
    for (int i = 0; i < 3; ++i) {
        ++it;
    }
    list_s1.remove(it);
    ASSERT_TRUE(list_s1 != list_s2);
    it = list_s1.begin();
    int i = 0;
    for (; i < 3; ++i) {
        ++it;
    }
    string s = to_string(sin(4));
    list_s1.insert(s, it);
    ASSERT_TRUE(list_s1 == list_s2);

    return true;
}

bool listFindTest(){
    List<int> list_int;
    for (int i = 0; i < 10; ++i) {
        list_int.insert(i);
    }
    List<int>::Iterator it = list_int.find(EqualTo(3));
    ASSERT_EQUALS(3, *it);
    it = list_int.find(EqualTo(20));
    ASSERT_TRUE(it == list_int.end());

    List<string> list_string;
    List<string>::Iterator its = list_string.find(EqualTo("str1"));
    ASSERT_TRUE(its == list_string.end());
    string s1 = "str1";
    string s2 = "str2";
    string s3 = "str3";
    list_string.insert(s1);
    list_string.insert(s2);
    list_string.insert(s1);
    list_string.insert(s3);
    list_string.insert(s2);
    list_string.insert(s1);
    its = list_string.find(EqualTo(s1));
    ASSERT_TRUE(its == list_string.begin());
    its = list_string.find(EqualTo(s2));
    ASSERT_TRUE(its == ++list_string.begin());
    its = list_string.find(EqualTo(s3));
    ASSERT_TRUE(its == ++++++list_string.begin());
    its = list_string.find(EqualTo("no"));
    ASSERT_TRUE(its == list_string.end());
    list_string.remove(++list_string.begin());
    its = list_string.find(EqualTo(s2));
    ASSERT_TRUE(its == ++++++list_string.begin());
    list_string.remove(++++++list_string.begin());
    ASSERT_TRUE(list_string.find(EqualTo(s2)) == list_string.end());

    return true;
}

bool listSortTest(){
    List<double> list_double;
    addToListDouble(list_double, 500, "cos");
    list_double.sort(std::less<double>());
    List<double >::Iterator it1 = list_double.begin();
    List<double>::Iterator it2 = it1;
    it2++;
    std::less<double> lessd;
    for (int j = 0; j < list_double.getSize()  - 1 ; ++j) {
        ASSERT_TRUE(lessd(*it1, *it2));
        ++it1;
        ++it2;
    }

    List<string> list_string;
    addToListString(list_string, 500, "sin");
    list_string.sort(std::less<string>());
    List<string >::Iterator its1 = list_string.begin();
    List<string>::Iterator its2 = its1;
    its2++;
    std::less_equal<string> lesss;
    for (int j = 0; j < list_string.getSize() - 1 ; ++j) {
        ASSERT_TRUE(lesss(*its1, *its2));
        ++its1;
        ++its2;
    }

    return true;
}

bool ListGetSizeTest(){
    List<string> list_str;
    addToListString(list_str, 70, "cos");
    ASSERT_TRUE(list_str.getSize() == 70);
    for (int i = 0; i < 30; ++i) {
        list_str.remove(list_str.begin());
    }
    ASSERT_TRUE(list_str.getSize() == 40);
    addToListString(list_str, 200, "sin");
    ASSERT_TRUE(list_str.getSize() == 240);
    return true;
}


bool iteratorDereferenceTest(){
    List<int> list_int;
    ASSERT_THROWS(ElementNotFound, *list_int.end());
    List<string> list_s;
    addToListString(list_s, 200, "sin");
    List<string>::Iterator it = list_s.begin();
    int i = 1;
    for (; it != list_s.end(); ++it) {
        ASSERT_TRUE(*it == to_string(sin(i)));
        i++;
    }
    ASSERT_THROWS(ElementNotFound, *it);
    return true;
}

bool IteratorEqualNotEqualOpTest(){
    List<string> list1;
    ASSERT_TRUE(list1.begin() == list1.end());
    List<string> list2;
    ASSERT_FALSE(list1.begin() == list2.end());
    ASSERT_TRUE(list1.begin() != list2.end());
    addToListString(list1, 20, "sin");
    addToListString(list2, 30, "sin");
    List<string>::Iterator it1 = list1.begin();
    List<string>::Iterator it2 = list2.begin();
    ASSERT_FALSE(it1 == it2);
    ASSERT_FALSE(list1.begin() == ++it1);
    ASSERT_FALSE(list1.end() == list2.end());
    it2 = it1;
    ASSERT_TRUE(it1 == it2);
    return true;
}

int main(){
    RUN_TEST(listCtorTest);
    RUN_TEST(listCopyCtorTest);
    RUN_TEST(ListAssignOpTest);
    RUN_TEST(ListBeginEndTest);
    RUN_TEST(listInsertTest);
    RUN_TEST(removeListTest);
    RUN_TEST(ListEqualNotEqualOpTest);
    RUN_TEST(listFindTest);
    RUN_TEST(listSortTest);
    RUN_TEST(ListGetSizeTest);
    RUN_TEST(iteratorDereferenceTest);
    RUN_TEST(IteratorEqualNotEqualOpTest);
    return 0;
}

