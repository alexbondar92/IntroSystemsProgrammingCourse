#include "escaper.h"
#include <assert.h>
#include <stdlib.h>


/**
 * this function converts email errors to escaper error
 * @param error_email a error from email ADT
 * @return
 * escaper error code
 */
static EscaperErrorCode convertEmailToEscaperError(EmailErrorCode error_email);


/* Escaper Struct */
struct Escaper_t{
    Email email;
    TechnionFaculty faculty;
    int skill_level;
};


Escaper escaperCreate(char *email, TechnionFaculty faculty, int skill_level,
                      EscaperErrorCode *error){
    if (email == NULL){
        *error = ESCAPER_NULL_PARAMETER;
        return NULL;
    }
    if (1 > skill_level || skill_level > 10 || 0 > (int)faculty ||
            faculty > (NUM_OF_FACULTYS-1)){
        *error = ESCAPER_INVALID_PARAMETER;
        return NULL;
    }
  
    Escaper escaper = malloc(sizeof(*escaper));
    if (escaper == NULL){
        *error = ESCAPER_OUT_OF_MEMORY;
        return NULL;
    }
    EmailErrorCode error_email = EMAIL_SUCCESS;
    escaper->email = emailCreate(email, &error_email);
    if (error_email != EMAIL_SUCCESS ){
        *error = convertEmailToEscaperError(error_email);
        escaperDestroy(escaper);
        return NULL;
    }

    escaper->faculty = faculty;
    escaper->skill_level = skill_level;
    *error = ESCAPER_SUCCESS;
    return escaper;
}

void escaperDestroy(Escaper escaper){
    if (escaper == NULL){
        return;
    }
    emailDestroy(escaper->email);
    free(escaper);
}

Email escaperGetEmail(Escaper escaper){
    assert(escaper != NULL);
    return escaper->email;
}

TechnionFaculty escaperGetFaculty(Escaper escaper){
    assert(escaper != NULL);
    return escaper->faculty;
}

int escaperGetSkillLevel(Escaper escaper){
    assert(escaper != NULL);
    return escaper->skill_level;
}

Escaper escaperCopy(Escaper escaper){
    assert(escaper != NULL);
    char* mail = emailToStr(escaperGetEmail(escaper));
    EscaperErrorCode error = ESCAPER_SUCCESS;
    Escaper copied_escaper = escaperCreate(mail, escaperGetFaculty(escaper),
                                        escaperGetSkillLevel(escaper), &error);
    free(mail);
    return copied_escaper;
}

int escaperComapare(Escaper escaper1, Escaper escaper2){
    assert(escaper1 != NULL && escaper2 != NULL);
    return emailCompare(escaperGetEmail(escaper1), escaperGetEmail(escaper2));
}

static EscaperErrorCode convertEmailToEscaperError(EmailErrorCode error_email){
    switch (error_email){
        case EMAIL_OUT_OF_MEMORY:
            return ESCAPER_OUT_OF_MEMORY;
            break;
        case EMAIL_NULL_PARAMETER:
            return ESCAPER_NULL_PARAMETER;
            break;
        case EMAIL_INVALID_PARAMETER:
            return ESCAPER_INVALID_PARAMETER;
            break;
        case EMAIL_SUCCESS:
            return ESCAPER_SUCCESS;
            break;
    }
    return ESCAPER_INVALID_PARAMETER;
}
