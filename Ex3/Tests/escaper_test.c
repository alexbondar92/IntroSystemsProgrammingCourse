#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test_utilities.h"
#include "../escaper.h"
#include "../escape_utilitis.h"


static bool testEscaperCreate() {
    char* email = "myEmail@campus.com";
    char* bad_email = "bad@one@gmail@com";
    EscaperErrorCode error = ESCAPER_SUCCESS;
    Escaper escaper = escaperCreate(bad_email, (TechnionFaculty)1, 5, &error);
    ASSERT_TEST(error == ESCAPER_INVALID_PARAMETER && escaper == NULL);
    escaper = escaperCreate(email, (TechnionFaculty)-1, 5, &error);
    ASSERT_TEST(error == ESCAPER_INVALID_PARAMETER && escaper == NULL);
    escaper = escaperCreate(email, (TechnionFaculty)19, 5, &error);
    ASSERT_TEST(error == ESCAPER_INVALID_PARAMETER && escaper == NULL);
    escaper = escaperCreate(email, (TechnionFaculty)7, 0, &error);
    ASSERT_TEST(error == ESCAPER_INVALID_PARAMETER && escaper == NULL);
    escaper = escaperCreate(email, (TechnionFaculty)7, 11, &error);
    ASSERT_TEST(error == ESCAPER_INVALID_PARAMETER && escaper == NULL);
    escaper = escaperCreate(email, (TechnionFaculty)6, 5, &error);
    ASSERT_TEST(error == ESCAPER_SUCCESS && escaper != NULL);

    EmailErrorCode error2 = EMAIL_SUCCESS;
    Email email_new = emailCreate(email, &error2);
    ASSERT_TEST(escaperGetFaculty(escaper) == 6);
    ASSERT_TEST(escaperGetSkillLevel(escaper) == 5);
    ASSERT_TEST(emailCompare(email_new, escaperGetEmail(escaper)) == 0);
    
    emailDestroy(email_new);
    escaperDestroy(escaper);
    return true;
}

static bool testEscaperCopy(){
    char* email = "BigEscaper@email";
    EscaperErrorCode error = ESCAPER_SUCCESS;
    Escaper escaper = escaperCreate(email, (TechnionFaculty)6, 5, &error);
    if (escaper == NULL){
        return false;
    }
    
    Escaper copied_escaper = escaperCopy(escaper);
    if (copied_escaper == NULL){
        return false;
    }
    ASSERT_TEST(escaperGetSkillLevel(escaper) ==
                escaperGetSkillLevel(copied_escaper));
    ASSERT_TEST(escaperGetFaculty(escaper) ==escaperGetFaculty(copied_escaper));
    ASSERT_TEST(emailCompare(escaperGetEmail(escaper),
                             escaperGetEmail(copied_escaper)) == 0);
    
    escaperDestroy(escaper);
    escaperDestroy(copied_escaper);
    return true;
}

static bool testEscaperDestroy() {
    /* ====================== already had been checked ====================== */
    return true;
}

int main/*EscaperTest*/(){
    RUN_TEST(testEscaperCreate);
    RUN_TEST(testEscaperCopy);
    RUN_TEST(testEscaperDestroy);
    return 0;
}


