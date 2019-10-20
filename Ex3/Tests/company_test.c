#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../company.h"
#include "test_utilities.h"
#include "../escape_utilitis.h"


static bool testCompanyCreate(){
    char* email = "BenElTavori@campus.technion.ac.il";
    char* null_email = NULL;
    char* bad_email = "@k@k@k@k.technion.ac.il";

    TechnionFaculty zahav_faculty = CIVIL_ENGINEERING;
    TechnionFaculty tudo_bom_faculty = MECHANICAL_ENGINEERING;
    TechnionFaculty lo_stam_faculty = ELECTRICAL_ENGINEERING;

    CompanyErrorCode error = COMPANY_SUCCESS;
    Company company = companyCreate(email, (TechnionFaculty)20, &error);
    ASSERT_TEST(error == COMPANY_INVALID_PARAMETER && company == NULL);
    company = companyCreate(null_email, zahav_faculty, &error);
    ASSERT_TEST(error == COMPANY_NULL_PARAMETER && company == NULL);
    company = companyCreate(bad_email, tudo_bom_faculty, &error);
    ASSERT_TEST(error == COMPANY_INVALID_PARAMETER && company == NULL);
    company = companyCreate(email, lo_stam_faculty, &error);
    ASSERT_TEST(error == COMPANY_SUCCESS && company != NULL);

    EmailErrorCode error_email = EMAIL_SUCCESS;
    Email new_email = emailCreate(email, &error_email);
    ASSERT_TEST(emailCompare(companyGetEmail(company), new_email) == 0);
    ASSERT_TEST(companyGetFaculty(company) == lo_stam_faculty);

    emailDestroy(new_email);
    companyDestroy(company);
    return true;
}


static bool testCompanyCopy(){
    char* email = "EscapeFromInfi@mail.com";
    CompanyErrorCode error_company = COMPANY_SUCCESS;
    Company company = companyCreate(email, COMPUTER_SCIENCE, &error_company);
    if (company == NULL){
        return false;
    }
    
    Company new_company = companyCopy(company);
    ASSERT_TEST(new_company != NULL);

    ASSERT_TEST(companyGetFaculty(new_company) == companyGetFaculty(company));
    ASSERT_TEST(emailCompare(companyGetEmail(new_company),
                             companyGetEmail(company)) == 0);
    
    companyDestroy(new_company);
    companyDestroy(company);
    return true;
}


static bool testCompanyAddRoom(){
    char* mail = "TheBigFoot@EscapeRoom.com";
    CompanyErrorCode company_error = COMPANY_SUCCESS;
    Company big_foot_comp = companyCreate(mail, BIOLOGY, &company_error);
    if (big_foot_comp == NULL){
        return false;
    }
    RoomErrorCode room_error = ROOM_SUCCESS;
    Room room = roomCreate(43, 12, 2, "03-11", 3, &room_error);
    if (room_error != ROOM_SUCCESS){
        return false;
    }
    ASSERT_TEST(companyAddRoom(big_foot_comp, room) == COMPANY_SUCCESS);
    ASSERT_TEST(companyRoomIsIn(big_foot_comp, room) == true);
    Room room2 = roomCreate(23, 40, 1, "00-12", 7, &room_error);
    if (room_error != ROOM_SUCCESS){
        return false;
    }
    ASSERT_TEST(companyRoomIsIn(big_foot_comp, room2) == false);
    ASSERT_TEST(companyRemoveRoom(big_foot_comp, 43) == COMPANY_SUCCESS);
    ASSERT_TEST(companyRoomIsIn(big_foot_comp, room) == false);

    roomDestroy(room);
    roomDestroy(room2);
    
    companyDestroy(big_foot_comp);
    return true;
}


static bool testCompanyRemoveRoom(){
    char* mail = "TheBigFoot@EscapeRoom.com";
    CompanyErrorCode company_error = COMPANY_SUCCESS;
    Company big_foot_comp = companyCreate(mail, BIOLOGY, &company_error);
    if (big_foot_comp == NULL){
        return false;
    }
    for (int i=0; i<= 20; i++){
        RoomErrorCode room_error = ROOM_SUCCESS;
        Room room = roomCreate(100+i, 40+4*i, i+5, "07-20", 8, &room_error);
        if (room_error != ROOM_SUCCESS){
            return false;
        }
        ASSERT_TEST(companyAddRoom(big_foot_comp, room) == COMPANY_SUCCESS);
        roomDestroy(room);
    }
    
    ASSERT_TEST(companyRemoveRoom(big_foot_comp, -1) ==
                COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyRemoveRoom(big_foot_comp, 32) ==
                COMPANY_ID_DOES_NOT_EXIST);
    ASSERT_TEST(companyRemoveRoom(big_foot_comp, 101) ==
                COMPANY_SUCCESS);
    ASSERT_TEST(companyRemoveRoom(big_foot_comp, 101) ==
                COMPANY_ID_DOES_NOT_EXIST);
    ASSERT_TEST(companyRemoveRoom(big_foot_comp, 100) ==
                COMPANY_SUCCESS);
    ASSERT_TEST(companyRemoveRoom(big_foot_comp, 100) ==
                COMPANY_ID_DOES_NOT_EXIST);
    for (int i=2; i<= 20; i++){
        ASSERT_TEST(companyRemoveRoom(big_foot_comp, 100+i) == COMPANY_SUCCESS);
    }
    
    companyDestroy(big_foot_comp);
    return true;
}



static bool testCompanyDestroy(){
    /* ====================== already had been checked ====================== */
    return true;
}


int main/*CompanyTest*/(){
    RUN_TEST(testCompanyCreate);
    RUN_TEST(testCompanyCopy);
    RUN_TEST(testCompanyAddRoom);
    RUN_TEST(testCompanyRemoveRoom);
    RUN_TEST(testCompanyDestroy);

    return 0;
}
