#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test_utilities.h"
#include "../escape_utilitis.h"


static bool testEmailCreate() {
    char* mail = "StaticBoy@mail.com";
    char* null_mail = NULL;
    char* bad_mail = "Jordi@Can@You@Do@This@PumPumPum@@";
    EmailErrorCode error = EMAIL_SUCCESS;
    Email email = emailCreate(null_mail, &error);
    ASSERT_TEST(error == EMAIL_NULL_PARAMETER && email == NULL);
    email = emailCreate(mail, &error);
    ASSERT_TEST(error == EMAIL_SUCCESS);
    Email bad_email = emailCreate(bad_mail, &error);
    ASSERT_TEST(error == EMAIL_INVALID_PARAMETER && bad_email == NULL);
    
    emailDestroy(email);
    emailDestroy(bad_email);
    return true;
}

static bool testEmailCompare() {
    char* mail1 = "MatamEmail@Ex3.com"; // big 'M'
    char* mail2 = "matamEmail@Ex3.com"; // small 'm'
    EmailErrorCode error = EMAIL_SUCCESS;
    Email email1 = emailCreate(mail1, &error);
    if (email1 == NULL){
        return false;
    }
    Email email2 = emailCreate(mail1, &error);
    if (email2 == NULL){
        return false;
    }
    Email email3 = emailCreate(mail2, &error);
    if (email3 == NULL){
        return false;
    }
    ASSERT_TEST(emailCompare(email1, email2) == 0);
    ASSERT_TEST(emailCompare(email1, email3) != 0);
    emailDestroy(email1);
    emailDestroy(email2);
    emailDestroy(email3);
    
    return true;
}

static bool testEmailCopy() {
    char* mail = "DrunkFromCola23@gmail.com";
    EmailErrorCode error = EMAIL_SUCCESS;
    Email email = emailCreate(mail, &error);
    Email copied_email = emailCopy(email);
    ASSERT_TEST(copied_email != NULL);
    ASSERT_TEST(emailCompare(email, copied_email) == 0);
    
    emailDestroy(email);
    emailDestroy(copied_email);
    return true;
}


static bool testEmailDestroy() {
    /* ====================== already had been checked ====================== */
	return true;
}

int main/*EmailTest*/(){
	RUN_TEST(testEmailCreate);
    RUN_TEST(testEmailCompare);
    RUN_TEST(testEmailCopy);
	RUN_TEST(testEmailDestroy);

	return 0;
}


