#include "company.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "room.h"

/**
 * this function converts email errors to company error
 * @param error_email a error from email ADT
 * @return
 * company error code
 */
static CompanyErrorCode convertEmailToCompanyError(EmailErrorCode error_email);


/**
 * Tamplete functions for generic set ADT
 * free/copy/compare funcs for Room
 */
static void companyRoomDestroy(SetElement room);
static SetElement companyRoomCopy(SetElement room);
static int companyRoomCompare(SetElement room1, SetElement room2);


/* Company Struct */
struct Company_t{
    Email email;
    TechnionFaculty faculty;
    Set rooms;
};


Company companyCreate(char* email, TechnionFaculty faculty,
                      CompanyErrorCode* error){
    if (email == NULL){
        *error = COMPANY_NULL_PARAMETER;
        return NULL;
    }
    if (0 > (int)faculty || faculty > (NUM_OF_FACULTYS-1)){
        *error = COMPANY_INVALID_PARAMETER;
        return NULL;
    }
    Company company = malloc(sizeof(*company));
    if (company == NULL){
        *error = COMPANY_OUT_OF_MEMORY;
        return NULL;
    }
    EmailErrorCode error_email = EMAIL_SUCCESS;
    company->email = emailCreate(email, &error_email);
    if (error_email != EMAIL_SUCCESS){
        free(company);
        *error = convertEmailToCompanyError(error_email);
        return NULL;
    }
    company->rooms = setCreate(companyRoomCopy, companyRoomDestroy,
                               companyRoomCompare);
    if (company->rooms == NULL){
        companyDestroy(company);
        *error = COMPANY_OUT_OF_MEMORY;
        return NULL;
    }
    company->faculty = faculty;
    *error = COMPANY_SUCCESS;
    return company;
}

void companyDestroy(Company company){
    if (company != NULL){
        emailDestroy(company->email);
        setDestroy(company->rooms);
        free(company);
    }
}

Email companyGetEmail(Company company){
    assert(company != NULL);
    return company->email;
}

TechnionFaculty companyGetFaculty(Company company){
    assert(company != NULL);
    return company->faculty;
}

Company companyCopy(Company company){
    assert (company != NULL);
    char* new_email = emailToStr(company->email);
    CompanyErrorCode error = COMPANY_SUCCESS;
    Company new_company = companyCreate(new_email, company->faculty, &error);
    setDestroy(new_company->rooms);
    new_company->rooms = setCopy(company->rooms);
    free(new_email);
    return new_company;
}

int companyCompare(Company company1, Company company2){
    assert (company1 != NULL);
    assert (company2 != NULL);
    return emailCompare(company1->email, company2->email);
}

CompanyErrorCode companyAddRoom(Company company, Room room){
    assert(company!=NULL);
    if (setIsIn(company->rooms, room) == true){
            return COMPANY_ID_ALREADY_EXIST;
    }
    if(setAdd(company->rooms, room) != SET_SUCCESS){
        return COMPANY_OUT_OF_MEMORY;
    }
    return COMPANY_SUCCESS;
}

CompanyErrorCode companyRemoveRoom(Company company,int room_id){
    assert(company != NULL);
    if (room_id < 0){
        return COMPANY_INVALID_PARAMETER;
    }
    SET_FOREACH(Room, tmp_room, company->rooms){
        if (roomGetId(tmp_room) == room_id){
            if (roomGetNumberOfOrders(tmp_room) == 0){
                setRemove(company->rooms, tmp_room);
                return COMPANY_SUCCESS;
            } else{
                return COMPANY_RESERVATION_EXISTS;
            }
        }
    }
    return COMPANY_ID_DOES_NOT_EXIST;
}

int companyGetNumberOfTotalOrders(Company company){
    assert(company != NULL);
    int numOfTotalOrders = 0;
    SET_FOREACH(Room, tmp_room, company->rooms){
        numOfTotalOrders += roomGetNumberOfOrders(tmp_room);
    }
    return numOfTotalOrders;
}

void companyDecNumberOfOrdersInRoom(Company company, int room_id){
    assert(company != NULL);
    SET_FOREACH(Room, tmp_room, company->rooms){
        if (roomGetId(tmp_room) == room_id){
            roomDecNumberOfOrders(tmp_room);
            return;
        }
    }
    return;
}

bool companyRoomIsIn(Company company, Room room){
    assert(company != NULL && room != NULL);
    return setIsIn(company->rooms, room);
}

Room companyGetRoom(Company company, int room_id, CompanyErrorCode* error){
    assert(company != NULL);
    
    SET_FOREACH(Room, current_room, company->rooms){
        if (roomGetId(current_room) == room_id){
            *error = COMPANY_SUCCESS;
            return current_room;
            
        }
    }
    *error = COMPANY_ID_DOES_NOT_EXIST;
    return NULL;
}

int companyRecommendedRoom (Company company, int p_e, int skill_level, int* id){
    assert(company != NULL);
    int recommened_room_id = 0;
    int calc_recommened_room = 0;
    int max_calc_recommened_room = -1;
    SET_FOREACH(Room, tmp_room, company->rooms){
        int p_r = roomGetNumOfPepole(tmp_room);
        int difficulty = roomGetDifficulty(tmp_room);
        calc_recommened_room = ((p_r-p_e)*(p_r-p_e)) +
                            ((difficulty-skill_level)*(difficulty-skill_level));
        if (calc_recommened_room < max_calc_recommened_room ||
                                            max_calc_recommened_room == -1){
            max_calc_recommened_room = calc_recommened_room;
            recommened_room_id = roomGetId(tmp_room);
        } else if (calc_recommened_room == max_calc_recommened_room){
            if (roomGetId(tmp_room) < recommened_room_id){
                recommened_room_id = roomGetId(tmp_room);
            }
        }
    }
    *id = recommened_room_id;
    return max_calc_recommened_room;
}


static void companyRoomDestroy(SetElement room){
    roomDestroy((Room)room);
}

static SetElement companyRoomCopy(SetElement room){
    return (SetElement)roomCopy((Room)room);
}

static int companyRoomCompare(SetElement room1, SetElement room2){
    return roomCompare((Room)room1, (Room)room2);
}

static CompanyErrorCode convertEmailToCompanyError(EmailErrorCode error_email){
    switch (error_email){
        case EMAIL_OUT_OF_MEMORY:
            return COMPANY_OUT_OF_MEMORY;
            break;
        case EMAIL_NULL_PARAMETER:
            return COMPANY_NULL_PARAMETER;
            break;
        case EMAIL_INVALID_PARAMETER:
            return COMPANY_INVALID_PARAMETER;
            break;
        case EMAIL_SUCCESS:
            return COMPANY_SUCCESS;
            break;
    }
    return COMPANY_INVALID_PARAMETER;
}
