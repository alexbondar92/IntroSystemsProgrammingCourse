
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "escape_utilitis.h"


/**
 * Checking if the mail sting is ligal.
 *
 * check that the email adrress is ligal by checking that there is only one
 * and only '@' sign in the string.
 *
 * @param email_address string to check
 * @return
 * 	True if the address is ligal, else return False
 */
static bool checkEmailLigal(char* email_address);


/* email struct */
struct Email_t{
    char* email_address;
};


Email emailCreate(char* email_address, EmailErrorCode *error){
    if (email_address == NULL){
        *error = EMAIL_NULL_PARAMETER;
        return NULL;
    }
    if (!checkEmailLigal(email_address)){
        *error = EMAIL_INVALID_PARAMETER;
        return NULL;
    }
    Email email = malloc(sizeof(Email));
    if (email == NULL){
        *error = EMAIL_OUT_OF_MEMORY;
        return NULL;
    }
    email->email_address = malloc(strlen(email_address)+1);
    if (email->email_address == NULL){
        emailDestroy(email);
        *error = EMAIL_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(email->email_address, email_address);
    *error = EMAIL_SUCCESS;
    return email;
}

void emailDestroy(Email email){
    if (email != NULL){
        free(email->email_address);
        free(email);
    }

}

int emailCompare(Email email1, Email email2){
    assert(email1 != NULL && email2 != NULL);
    return strcmp(email1->email_address, email2->email_address);
}

Email emailCopy(Email email){
    assert(email != NULL);
    EmailErrorCode error;
    return emailCreate(email->email_address,&error);
}

char* emailToStr(Email email){
    assert(email != NULL);
    int len_of_email =(int)strlen(email->email_address)+1;
    char* str = malloc(len_of_email* sizeof(char));
    if (str != NULL){
        memcpy(str, email->email_address, (size_t)len_of_email);
    }
    return str;
}




static bool checkEmailLigal(char* email_address){
    assert(email_address != NULL);
    bool flag = false;
    while(*email_address != '\0'){
        if(*email_address == '@'){
            if(flag == true){
                return false;
            } else{
                flag = true;
            }
        }
        email_address++;
    }
    return flag;
}
