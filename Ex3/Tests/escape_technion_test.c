#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../escape_technion.h"
#include "test_utilities.h"


static bool testEscapeTechnionCreate(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system1 = escapeTechnionCreate(&system_error);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS && system1 != NULL);
    EscapeTechnion system2 = escapeTechnionCreate(&system_error);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS && system2 != NULL);
    EscapeTechnion system3 = escapeTechnionCreate(&system_error);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS && system3 != NULL);
    escapeTechnionDestroy(system1);
    escapeTechnionDestroy(system2);
    escapeTechnionDestroy(system3);
    return true;
}

static bool testEscapeTechnionAddCompany(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    char* null_str = NULL;
    system_error = escapeTechnionAddCompany(system, null_str, 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_NULL_PARAMETER);
    system_error = escapeTechnionAddCompany(system, "Hey@jack@pipe", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddCompany(system, "NoAtSign", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddCompany(system, "Great@mail", -1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddCompany(system, "Great@mail", COMPUTER_SCIENCE);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddCompany(system, "Great@mail", CHEMISTRY);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);

    char* mails[6] = {"@","this@","@mails","are@","too@","annoying@me"};
    
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);
    }
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionRemoveCompany(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    char* mails[6] = {"@","this@","@mails","are@","too@","annoying@me"};
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        if (system_error != ESCAPE_TECHNION_SUCCESS){
            return false;
        }
    }
    char* null_str = NULL;
    system_error = escapeTechnionRemoveCompany(system, null_str);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_NULL_PARAMETER);
    system_error = escapeTechnionRemoveCompany(system, "noAtInEmail!!!");
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionRemoveCompany(system, "noEmailLikeThis@");
    ASSERT_TEST(system_error == ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST);
    
    for (int i=0; i<6; i++){
        system_error = escapeTechnionRemoveCompany(system, mails[i]);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionAddRoom(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    char* mails[6] = {"@","this@","@mails","are@","too@","annoying@me"};
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        if (system_error != ESCAPE_TECHNION_SUCCESS){
            return false;
        }
    }
    char* null_str = NULL;
    system_error = escapeTechnionAddRoom(system, null_str, 10, 4, 1, "00-01",
                                         1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_NULL_PARAMETER);
    system_error = escapeTechnionAddRoom(system, "@@", 10, 4, 1, "00-01", 1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddRoom(system, "aaa", 10, 4, 1, "00-01", 1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddRoom(system, "TIK@TAK", 0, 4, 1, "00-01",
                                         1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddRoom(system, "TIK@TAK", 10, 3, 1, "00-01",
                                         1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddRoom(system, "TIK@TAK", 10, 4, 0, "00-01",
                                         1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddRoom(system, "TIK@TAK", 10, 4, 1, "23-11",
                                         1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddRoom(system, "TIK@TAK", 10, 4, 1, "11-23",
                                         1000);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    
    system_error = escapeTechnionAddRoom(system, "TIK@TAK", 10, 4, 1, "00-01",
                                         1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST);
    system_error = escapeTechnionAddRoom(system, mails[0], 10, 4, 1, "00-01",
                                         1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    for (int i=0; i< 30; i++){
        system_error = escapeTechnionAddRoom(system, mails[i%5], 20+i, 4+4*i, 3,
                                             "07-18", 4);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i< 30; i++){
        system_error = escapeTechnionAddRoom(system, mails[i%5], 20+i, 4+4*i, 3,
                                             "07-18", 4);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_ID_ALREADY_EXIST);
    }
    
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionRemoveRoom(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    char* mails[6] = {"@","this@","@mails","are@","too@","annoying@me"};
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        if (system_error != ESCAPE_TECHNION_SUCCESS){
            return false;
        }
    }
    for (int i=0; i< 6; i++){
        system_error = escapeTechnionAddRoom(system, mails[i], 20+i, 4+4*i, 3,
                                             "07-18", i+1);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    system_error = escapeTechnionRemoveRoom(system, -1, 10);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionRemoveRoom(system, 1, -20);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionRemoveRoom(system, 7, 10);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_ID_DOES_NOT_EXIST);
    
    for (int i=0; i< 6; i++){
        system_error = escapeTechnionRemoveRoom(system, i, 20+i);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i< 6; i++){
        system_error = escapeTechnionRemoveRoom(system, i, 20+i);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_ID_DOES_NOT_EXIST);
    }
    
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionAddEscaper(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    char* mails[6] = {"@","this@","@mails","are@","too@","annoying@me"};
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        if (system_error != ESCAPE_TECHNION_SUCCESS){
            return false;
        }
    }
    
    char* null_str = NULL;
    system_error = escapeTechnionAddEscaper(system, null_str, 2, 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_NULL_PARAMETER);
    system_error = escapeTechnionAddEscaper(system, "@@@", 2, 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddEscaper(system, "alex@email", 200, 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddEscaper(system, "Todu@bom", 2, 0);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddEscaper(system, "Todu@bom", 2, 11);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddEscaper(system, "Todu@bom", 2, 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddEscaper(system, "Todu@bom", 2, 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);
    system_error = escapeTechnionAddEscaper(system, "Todu@bom", 2, 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);
    system_error = escapeTechnionAddEscaper(system, "Static@boy", 2, 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddEscaper(system, mails[i], 2, 7);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);
    }
    
    escapeTechnionDestroy(system);
    return true;
}


static bool testEscapeTechnionRemoveEscaper(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    char* mails[6] = {"@","this@","@mails","are@","too@","annoying@me"};
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        if (system_error != ESCAPE_TECHNION_SUCCESS){
            return false;
        }
    }
    char* emails_escapers[4] = {"sapir@","@leaha","Yair@","WantToEnd@MTMex3"};
    for (int i=0; i<4; i++){
        system_error = escapeTechnionAddEscaper(system, emails_escapers[i], 2,
                                                7);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* null_str = NULL;
    system_error = escapeTechnionRemoveEscaper(system, null_str);;
    ASSERT_TEST(system_error == ESCAPE_TECHNION_NULL_PARAMETER);
    system_error = escapeTechnionRemoveEscaper(system, "@@#@#@#");;
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionRemoveEscaper(system, "No@Email");
    ASSERT_TEST(system_error == ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);
    
    for (int i=0; i<4; i++){
        system_error = escapeTechnionRemoveEscaper(system, emails_escapers[i]);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionAddOrder(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    char* mails[6] = {"@","this@","@mails","are@","too@","annoying@me"};
    for (int i=0; i<6; i++){
        system_error = escapeTechnionAddCompany(system, mails[i], i);
        if (system_error != ESCAPE_TECHNION_SUCCESS){
            return false;
        }
    }
    for (int i=0; i< 6; i++){
        system_error = escapeTechnionAddRoom(system, mails[i], 20+i, 4+4*i, 3,
                                             "07-18", i+1);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* emails_escapers[4] = {"sapir@","@leaha","Yair@","WantToEnd@MTMex3"};
    for (int i=0; i<4; i++){
        system_error = escapeTechnionAddEscaper(system, emails_escapers[i], 2,
                                                7);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* null_str = NULL;
    system_error = escapeTechnionAddOrder(system, null_str, 1, 12, "2-01", 2);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_NULL_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "AA", 2, 2, "2-11", 1000);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "A@A", 20, 2, "2-11", 1000);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "A@A", 2, 0, "2-11", 1000);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "A@A", 2, 12, "2.2-11", 1000);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "A@A", 2, 12, "1002020 11",
                                          1000);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "A@A", 2, 12, "2-34", 1000);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "A@A", 2, 12, "2-20", 0);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionAddOrder(system, "A@A", 2, 12, "2-20", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);
    system_error = escapeTechnionAddOrder(system, emails_escapers[0], 2, 14,
                                          "12-18", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_ID_DOES_NOT_EXIST);
    system_error = escapeTechnionAddOrder(system, emails_escapers[0], 2, 22,
                                          "12-18", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    system_error = escapeTechnionAddOrder(system, emails_escapers[0], 3, 23,
                                          "12-18", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_CLIENT_IN_ROOM);
    
    system_error = escapeTechnionAddOrder(system, emails_escapers[1], 2, 22,
                                          "12-18", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_ROOM_NOT_AVAILABLE);
    
    system_error = escapeTechnionAddOrder(system, emails_escapers[1], 2, 22,
                                          "12-19", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails_escapers[2], 2, 22,
                                          "12-20", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails_escapers[3], 2, 22,
                                          "12-21", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    system_error = escapeTechnionRemoveRoom(system, 2, 22);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_RESERVATION_EXISTS);
    system_error = escapeTechnionRemoveCompany(system, mails[3]);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionRemoveCompany(system, mails[2]);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_RESERVATION_EXISTS);
    
    
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionRecommendedOrder(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    
    char* emails1[3] = {"C1@","C2@","C3@"};
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddCompany(system, emails1[i],
                                                COMPUTER_SCIENCE);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i<2; i++){
        system_error = escapeTechnionAddRoom(system, emails1[2], 10+i, 20, 10,
                                             "12-18", 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* emails2[3] = {"bestC1@","bestC2@","bestC3@"};
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddCompany(system, emails2[i],
                                                CIVIL_ENGINEERING);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddRoom(system, emails2[1], 20+i, 20, 10,
                                             "08-16", 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* emails3[5] = {"Dani@","@Yoni","Keren@","Tim@","@Alex"};
    for (int i=0; i<5; i++){
        system_error = escapeTechnionAddEscaper(system, emails3[i], i, 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    char* null_str = NULL;
    system_error = escapeTechnionRecommendedOrder(system, null_str, 10);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_NULL_PARAMETER);
    system_error = escapeTechnionRecommendedOrder(system, "Take@mail@TIKI", 20);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionRecommendedOrder(system, "Take@mail", 0);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_INVALID_PARAMETER);
    system_error = escapeTechnionRecommendedOrder(system, "Take@mail", 1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);
    system_error = escapeTechnionRecommendedOrder(system, "Tim@", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    system_error =escapeTechnionRecommendedOrder(system, "Dani@", 7);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionReportDay(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    
    char* emails1[3] = {"C1@","C2@","C3@"};
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddCompany(system, emails1[i],
                                                COMPUTER_SCIENCE);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i<2; i++){
        system_error = escapeTechnionAddRoom(system, emails1[2], 10+i, 20, 10,
                                             "12-18", 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* emails2[3] = {"bestC1@","bestC2@","bestC3@"};
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddCompany(system, emails2[i],
                                                CIVIL_ENGINEERING);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddRoom(system, emails2[1], 20+i, 20, 10,
                                             "08-16", 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* emails3[5] = {"Dani@","@Yoni","Keren@","Tim@","@Alex"};
    for (int i=0; i<5; i++){
        system_error = escapeTechnionAddEscaper(system, emails3[i], i, 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    system_error = escapeTechnionAddOrder(system, emails3[0], COMPUTER_SCIENCE,
                                          11, "2-11", 2);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[1], COMPUTER_SCIENCE,
                                          10, "1-12", 10);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[2], CIVIL_ENGINEERING,
                                          20, "1-12", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[0], CIVIL_ENGINEERING,
                                          20, "2-13", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[3], CIVIL_ENGINEERING,
                                          21, "1-12", 1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[4], CIVIL_ENGINEERING,
                                          22, "1-14", 5);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    
    printf("\n\n");
    printf("#TEST: ReportDay test#1:\n");
    system_error = escapeTechnionReportDay(system, stdout);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    printf("#TEST: ReportDay test#2:\n");
    system_error = escapeTechnionReportDay(system, stdout);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    

    printf("#TEST: ReportDay test#3:\n");
    system_error = escapeTechnionReportDay(system, stdout);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    printf("#TEST: ReportDay test#3:\n");
    system_error = escapeTechnionReportDay(system, stdout);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);

    system_error = escapeTechnionAddOrder(system, emails3[0], COMPUTER_SCIENCE,
                                          11, "2-11", 2);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[1], COMPUTER_SCIENCE,
                                          10, "2-11", 10);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[2], CIVIL_ENGINEERING,
                                          20, "1-13", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[0], CIVIL_ENGINEERING,
                                          20, "2-13", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[3], CIVIL_ENGINEERING,
                                          21, "1-12", 1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[4], CIVIL_ENGINEERING,
                                          22, "1-14", 5);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    
    escapeTechnionDestroy(system);
    return true;
}

static bool testEscapeTechnionReportBest(){
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS && system == NULL){
        return false;
    }
    
    char* emails1[3] = {"C1@","C2@","C3@"};
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddCompany(system, emails1[i],
                                                COMPUTER_SCIENCE);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i<2; i++){
        system_error = escapeTechnionAddRoom(system, emails1[2], 10+i, 20, 10,
                                             "12-18", 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* emails2[3] = {"bestC1@","bestC2@","bestC3@"};
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddCompany(system, emails2[i],
                                                HUMANITIES_AND_ARTS);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    for (int i=0; i<3; i++){
        system_error = escapeTechnionAddRoom(system, emails2[1], 20+i, 20, 10,
                                             "08-16", 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }
    
    char* emails3[5] = {"Dani@","@Yoni","Keren@","Tim@","@Alex"};
    for (int i=0; i<5; i++){
        system_error = escapeTechnionAddEscaper(system, emails3[i], i, 3);
        ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    }

    system_error = escapeTechnionAddOrder(system, emails3[0], COMPUTER_SCIENCE,
                                          11, "2-11", 2);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[1], COMPUTER_SCIENCE,
                                          10, "1-12", 10);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[2],
                                          HUMANITIES_AND_ARTS, 20, "1-12", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[0],
                                          HUMANITIES_AND_ARTS, 20, "2-13", 3);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[3],
                                          HUMANITIES_AND_ARTS, 21, "1-12", 1);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);
    system_error = escapeTechnionAddOrder(system, emails3[4],
                                          HUMANITIES_AND_ARTS, 22, "1-14", 5);
    ASSERT_TEST(system_error == ESCAPE_TECHNION_SUCCESS);

    printf("\n\n");
    printf("#TEST: ReportBest test#1:\n");
    system_error = escapeTechnionReportBest(system, stdout);
    ASSERT_TEST(system_error);

    escapeTechnionReportDay(system, stdout);
    
    printf("\n\n");
    printf("#TEST: ReportBest test#2:\n");
    system_error = escapeTechnionReportBest(system, stdout);
    ASSERT_TEST(system_error);
    
    escapeTechnionReportDay(system, stdout);
    
    printf("\n\n");
    printf("#TEST: ReportBest test#3:\n");
    system_error = escapeTechnionReportBest(system, stdout);
    ASSERT_TEST(system_error);
    
    escapeTechnionReportDay(system, stdout);
    
    printf("\n\n");
    printf("#TEST: ReportBest test#4:\n");
    system_error = escapeTechnionReportBest(system, stdout);
    ASSERT_TEST(system_error);
  
    escapeTechnionDestroy(system);
    return true;
}

int main/*EscapeTechnionTest*/(){
    RUN_TEST(testEscapeTechnionCreate);
    RUN_TEST(testEscapeTechnionAddCompany);
    RUN_TEST(testEscapeTechnionRemoveCompany);
    RUN_TEST(testEscapeTechnionAddRoom);
    RUN_TEST(testEscapeTechnionRemoveRoom);
    RUN_TEST(testEscapeTechnionAddEscaper);
    RUN_TEST(testEscapeTechnionRemoveEscaper);
    RUN_TEST(testEscapeTechnionAddOrder);
    RUN_TEST(testEscapeTechnionRecommendedOrder);
    RUN_TEST(testEscapeTechnionReportDay);
    RUN_TEST(testEscapeTechnionReportBest);
    return 0;
}
