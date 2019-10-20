#include "escape_technion.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "company.h"
#include "escaper.h"
#include "orders.h"
#include "room.h"




/**
 * Tamplete functions for generic set ADT
 * free/copy/compare funcs for Company
 */
static void escapeTechnionCompanyDestroy(SetElement company);
static SetElement escapeTechnionCompanyCopy(SetElement company);
static int escapeTechnionCompanyCompare(SetElement company1, SetElement company2);

/**
 * Tamplete functions for generic set ADT
 * free/copy/compare funcs for Escapers
 */
static void escapeTechnionEscaperDestroy(SetElement escaper);
static SetElement escapeTechnionEscaperCopy(SetElement escaper);
static int escapeTechnionEscaperCompare(SetElement escaper1, SetElement escaper2);

/**
 * Tamplete functions for generic list ADT
 * free/copy/compare funcs for Order
 */
static void escapeTechnionOrderDestroy(SetElement order);
static SetElement escapeTechnionOrderCopy(SetElement order);
static int escapeTechnionOrderDayCompare(SetElement order1, SetElement order2);
static bool filterOrdersOfLastDay(ListElement order, ListFilterKey key);
static bool filterOrdersNotLastDay(ListElement order, ListFilterKey key);
static bool filterOrdersOfEscaper(ListElement order, ListFilterKey email);

/**
 * convert day and hour timestamp to char(XX-YY).
 *
 * @param day of timestamp
 * @param hour of timestamp
 * @return
 * string like this: day-hour
 */
static char* timeIntToChar(int day, int hour);

/**
 * add all the incomes to the total faculties revenue
 *
 */
static void addIncomeToTotalRevenue(EscapeTechnion system);

/**
 * check if there is a email address in the system(escapers or companies)
 *
 * @param system the main EscateTechnion
 * @param email the email to look for
 * @return
 * returns true/false depend if it found or not
 */
static bool checkIfEmailExistInSystem(EscapeTechnion system, char* email);

/**
 * find escaper in the system by his email address
 *
 * @param system the main EscateTechnion
 * @param escaper_email the email to look for
 * @return
 * returns the escaper object if found or NULL if isn't
 */
static Escaper findEscaperByEmail(EscapeTechnion system,Email escaper_email);

/**
 * find company's room in the system by his id number and the faculy it is in
 *
 * @param system the main EscateTechnion
 * @param faculty the faculty in witch the room is in
 * @param room_id the id number of that room
 * @return
 * returns the company object if found or NULL if isn't
 */
static Company findCompanysRoom(EscapeTechnion system, TechnionFaculty faculty,
                                int room_id);

/**
 * find room in the system by his id number and the faculy it is in
 *
 * @param system the main EscateTechnion
 * @param faculty the faculty in witch the room is in
 * @param room_id the id number of that room
 * @return
 * returns the room object if found or NULL if isn't
 */
static Room findRoomInSystem(EscapeTechnion system ,TechnionFaculty faculty,
                             int room_id);

/**
 * find faculty of the room in the system by his room id and company email
 *
 * @param system the main EscateTechnion
 * @param company_email the company in witch the room is in
 * @param room_id the id number of that room
 * @return
 * returns the faculty number if found or -1 if not
 */
static TechnionFaculty findFacultyOfRoom(EscapeTechnion system ,
                                         Email company_email ,int room_id);

/**
 * checks if the time for new order is avalible at this time for this parametes
 *
 * @param system the main EscateTechnion
 * @param faculty the faculty of the new order
 * @param room_id the id number of that room
 * @param escaper_email the email of the escaper
 * @param day of the order
 * @param hour of the order
 * @return
 * ESCAPE_TECHNION_CLIENT_IN_ROOM - in case there is client in room
 * ESCAPE_TECHNION_ROOM_NOT_AVAILABLE - in case the room is acuiped
 * ESCAPE_TECHNION_SUCCESS - in case of success
 */
static EscapeTechnionErrorCode checkOrderAtTime(EscapeTechnion system,
                                int faculty, int room_id, Email escaper_email,
                                int day, int hour);

/**
 * check if there is a room at the current faculty
 *
 * @param system the main EscateTechnion
 * @param faculty the faculty to look at
 * @param room the room to look for
 * @return
 * returns true/false
 */
static bool checkRoomInFaculty(EscapeTechnion system, TechnionFaculty faculty,
                               Room room);

/**
 * convert time string to int's day and hour
 *
 * @param time the time string
 * @param day the int* to return value
 * @param hour the int* to return value
 * @return
 * return true/false if success
 */
static bool convertTimeToDayNHour(char* time, int* day, int* hour);

/**
 * Functions for converting error codes from other ADTs to EscapeTechnion
 */
static EscapeTechnionErrorCode convertListToTechnionErrorCode(ListResult list_error);
static EscapeTechnionErrorCode convertCompanyToEscapeTechnionError(CompanyErrorCode error_company);
static EscapeTechnionErrorCode convertRoomToEscapeTechnionError(RoomErrorCode error_room);
static EscapeTechnionErrorCode convertEmailToEscapeTechnionError(EmailErrorCode error_email);
static EscapeTechnionErrorCode convertEscaperToEscapeTechnionError(EscaperErrorCode escaper_error);
static EscapeTechnionErrorCode convertOrderToTechnionErrorCode(OrderErrorCode Order_error);

/**
 * find the closest time for new order that possible
 *
 * @param system the main system
 * @param room_faculty the faculty for the room to order
 * @param room_id the room number to order
 * @param escaper_email the email of the ordering escaper
 * @return
 * the time(string ) in witch the new order could be
 */
static char* findClosestTime(EscapeTechnion system, TechnionFaculty room_faculty,
                             int room_id, Email escaper_email);


/* struct EscapeTechnion */
struct EscapeTechnion_t{
    int current_day;
    Set companies;
    Set escapers;
    List orders;
    int* faculties_revenue;
};


EscapeTechnion escapeTechnionCreate(EscapeTechnionErrorCode* error){
    EscapeTechnion system = malloc(sizeof(*system));
    if (system == NULL){
        *error = ESCAPE_TECHNION_OUT_OF_MEMORY;
        return NULL;
    }
    system->faculties_revenue = malloc(NUM_OF_FACULTYS*sizeof(int));
    if (system->faculties_revenue == NULL){
        free(system);
        return NULL;
    }
    system->companies = setCreate(escapeTechnionCompanyCopy,
                                  escapeTechnionCompanyDestroy,
                                  escapeTechnionCompanyCompare);
    if (system->companies == NULL){
        free(system->faculties_revenue);
        free(system);
        *error = ESCAPE_TECHNION_OUT_OF_MEMORY;
        return NULL;
    }
    system->escapers = setCreate(escapeTechnionEscaperCopy,
                                 escapeTechnionEscaperDestroy,
                                 escapeTechnionEscaperCompare);
    if (system->escapers == NULL){
        free(system->faculties_revenue);
        setDestroy(system->companies);
        free(system);
        *error = ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    system->orders = listCreate(escapeTechnionOrderCopy,
                                escapeTechnionOrderDestroy);
    if (system->orders == NULL){
        free(system->faculties_revenue);
        setDestroy(system->companies);
        setDestroy(system->escapers);
        free(system);
        *error = ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    for (int i=0; i< NUM_OF_FACULTYS; i++){
        system->faculties_revenue[i] = 0;
    }
    system->current_day = 0;
    *error = ESCAPE_TECHNION_SUCCESS;
    return system;
}

void escapeTechnionDestroy(EscapeTechnion system){
    if (system == NULL){
        return;
    }
    free(system->faculties_revenue);
    setDestroy(system->companies);
    setDestroy(system->escapers);
    listDestroy(system->orders);
    free(system);
}

EscapeTechnionErrorCode escapeTechnionAddCompany(EscapeTechnion system,
                                                 char* email, TechnionFaculty faculty){
    assert(system != NULL);
    if (email == NULL){
        return ESCAPE_TECHNION_NULL_PARAMETER;
    }
    
    CompanyErrorCode error = COMPANY_SUCCESS;
    Company new_company = companyCreate(email, faculty, &error);
    if (error != COMPANY_SUCCESS){
        return convertCompanyToEscapeTechnionError(error);
    }
    if (checkIfEmailExistInSystem(system, email) == true){
        companyDestroy(new_company);
        return ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS;
    }
    if (setAdd(system->companies, new_company) != SET_SUCCESS){
        companyDestroy(new_company);
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    companyDestroy(new_company);
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionRemoveCompany(EscapeTechnion system,
                                                    char* email){
    assert(system != NULL);
    if (email == NULL){
        return ESCAPE_TECHNION_NULL_PARAMETER;
    }
    EmailErrorCode email_error;
    Email tmp_email = emailCreate(email, &email_error);
    if (email_error != EMAIL_SUCCESS){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    
    SET_FOREACH(Company, tmp_company, system->companies){
        if (emailCompare(companyGetEmail(tmp_company), tmp_email) == 0){
            if (companyGetNumberOfTotalOrders(tmp_company) == 0){
                emailDestroy(tmp_email);
                setRemove(system->companies, tmp_company);
                return ESCAPE_TECHNION_SUCCESS;
            } else{
                emailDestroy(tmp_email);
                return ESCAPE_TECHNION_RESERVATION_EXISTS;
            }
        }
    }
    emailDestroy(tmp_email);
    return ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST;
}

EscapeTechnionErrorCode escapeTechnionAddRoom(EscapeTechnion system, char* email,
                                              int room_id, int price, int num_ppl,
                                              char* working_hrs, int difficulty){
    assert(system != NULL);
    RoomErrorCode room_error = ROOM_SUCCESS;
    Room tmp_room = roomCreate(room_id, price, num_ppl, working_hrs, difficulty,
                               &room_error);
    if (room_error != ROOM_SUCCESS){
        roomDestroy(tmp_room);
        return convertRoomToEscapeTechnionError(room_error);
    }
    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email tmp_email = emailCreate(email, &email_error);
    if (email_error != EMAIL_SUCCESS){
        roomDestroy(tmp_room);
        emailDestroy(tmp_email);
        return convertEmailToEscapeTechnionError(email_error);
    }
    TechnionFaculty faculty = -1;
    SET_FOREACH(Company, tmp_company, system->companies){
        if (emailCompare(companyGetEmail(tmp_company), tmp_email) == 0){
            emailDestroy(tmp_email);
            faculty = companyGetFaculty(tmp_company);
            if (checkRoomInFaculty(system, faculty, tmp_room) == false &&
                (int)faculty != -1){
                CompanyErrorCode company_error = companyAddRoom(tmp_company,
                                                                tmp_room);
                roomDestroy(tmp_room);
                return convertCompanyToEscapeTechnionError(company_error);
            } else if((int)faculty != -1){
                roomDestroy(tmp_room);
                return ESCAPE_TECHNION_ID_ALREADY_EXIST;
            }
        }
    }
    emailDestroy(tmp_email);
    roomDestroy(tmp_room);
    return ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST;
}

EscapeTechnionErrorCode escapeTechnionRemoveRoom(EscapeTechnion system,
                                                 TechnionFaculty faculty, int room_id){
    assert(system != NULL);
    if (room_id <= 0 || (int)faculty < 0 || (NUM_OF_FACULTYS-1) < faculty){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    RoomErrorCode room_error = ROOM_SUCCESS;
    Room room = roomCreate(room_id, 4, 1, "00-01", 1, &room_error);
    if (room_error != ROOM_SUCCESS){
        return convertRoomToEscapeTechnionError(room_error);
    }
    if(checkRoomInFaculty(system, faculty, room) == false){
        roomDestroy(room);
        return ESCAPE_TECHNION_ID_DOES_NOT_EXIST;
    }
    roomDestroy(room);
    SET_FOREACH(Company, tmp_company, system->companies){
        if (companyGetFaculty(tmp_company) == faculty){
            CompanyErrorCode company_error = companyRemoveRoom(tmp_company,
                                                               room_id);
            if (company_error != COMPANY_ID_DOES_NOT_EXIST){
                return convertCompanyToEscapeTechnionError(company_error);
            }
        }
    }
    assert(0);
    return ESCAPE_TECHNION_ID_DOES_NOT_EXIST;
}

EscapeTechnionErrorCode escapeTechnionAddEscaper(EscapeTechnion system,
                                                 char* email, TechnionFaculty faculty, int skil_level){
    assert(system != NULL);
    EscaperErrorCode escaper_error = ESCAPER_SUCCESS;
    Escaper escaper = escaperCreate(email, faculty, skil_level, &escaper_error);
    if (escaper_error != ESCAPER_SUCCESS){
        return convertEscaperToEscapeTechnionError(escaper_error);
    }
    if (checkIfEmailExistInSystem(system, email) == true){
        escaperDestroy(escaper);
        return ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS;
    }
    if (setAdd(system->escapers, escaper) != SET_SUCCESS){
        escaperDestroy(escaper);
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    escaperDestroy(escaper);
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionRemoveEscaper(EscapeTechnion system,
                                                    char* email){
    assert(system != NULL);
    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email escaper_email = emailCreate(email, &email_error);
    if (email_error != EMAIL_SUCCESS){
        return convertEmailToEscapeTechnionError(email_error);
    }
    if (findEscaperByEmail(system, escaper_email) == false){
        emailDestroy(escaper_email);
        return ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    
    LIST_FOREACH(Order, tmp_order, system->orders){
        if (emailCompare(escaper_email, orderGetEscaperEmail(tmp_order)) == 0){
            SET_FOREACH(Company, tmp_compny, system->companies){
                if (emailCompare(orderGetCompanyEmail(tmp_order),
                                 companyGetEmail(tmp_compny)) == 0){
                    companyDecNumberOfOrdersInRoom(tmp_compny,
                                                   orderGetRoomId(tmp_order));
                }
            }
        }
    }
    List tmp =listFilter(system->orders, filterOrdersOfEscaper, escaper_email);
    listDestroy(system->orders);
    system->orders = tmp;
    
    SET_FOREACH(Escaper, tmp_escaper, system->escapers){
        if(emailCompare(escaper_email, escaperGetEmail(tmp_escaper)) ==  0){
            setRemove(system->escapers, tmp_escaper);
            emailDestroy(escaper_email);
            return ESCAPE_TECHNION_SUCCESS;
        }
    }
    assert(0); // cannot get here!
    return ESCAPE_TECHNION_NULL_PARAMETER;
}

EscapeTechnionErrorCode escapeTechnionAddOrder(EscapeTechnion system,
                                               char* email, TechnionFaculty faculty,
                                               int id, char* time, int num_ppl){
    assert(system != NULL);
    if (email == NULL || time == NULL){
        return ESCAPE_TECHNION_NULL_PARAMETER;
    }
    if (num_ppl <= 0 || id <= 0 || (int)faculty < 0 ||
        (NUM_OF_FACULTYS-1) < faculty){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    int days = 0;
    int hour = 0;
    if (convertTimeToDayNHour(time, &days, &hour) == false){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email escaper_email = emailCreate(email, &email_error);
    if (email_error != EMAIL_SUCCESS){
        return convertEmailToEscapeTechnionError(email_error);
    }
    Escaper escaper = findEscaperByEmail(system, escaper_email);
    if (escaper == NULL){
        emailDestroy(escaper_email);
        return ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Room room = findRoomInSystem(system, faculty, id);
    if (room == NULL){
        emailDestroy(escaper_email);
        return ESCAPE_TECHNION_ID_DOES_NOT_EXIST;
    }
    Email company_email = companyGetEmail(findCompanysRoom(system, faculty,id));
    listSort(system->orders, escapeTechnionOrderDayCompare);
    EscapeTechnionErrorCode system_error = checkOrderAtTime(system, faculty, id,
                                                            escaper_email, days, hour);
    if (system_error != ESCAPE_TECHNION_SUCCESS){
        emailDestroy(escaper_email);
        return system_error;
    }
    if (hour < roomGetOpenTime(room) || roomGetCloseTime(room) <= hour){
        emailDestroy(escaper_email);
        return ESCAPE_TECHNION_ROOM_NOT_AVAILABLE;
    }
    int total_price = roomGetPrice(room)*num_ppl;
    if (faculty == escaperGetFaculty(escaper)){
        total_price = (int)(total_price*0.75);
    }
    OrderErrorCode order_error = ORDER_SUCCESS;
    Order new_order = orderCreate(days, hour, id, faculty, company_email,
                                  num_ppl, total_price, escaper_email, &order_error);
    if(order_error != ORDER_SUCCESS) {
        emailDestroy(escaper_email);
        return convertOrderToTechnionErrorCode(order_error);
    }
    ListResult list_error = listInsertFirst(system->orders, new_order);
    orderDestroy(new_order);
    emailDestroy(escaper_email);
    roomIncNumberOfOrders(room);
    return convertListToTechnionErrorCode(list_error);
}

EscapeTechnionErrorCode escapeTechnionRecommendedOrder(EscapeTechnion system, char* email, int num_ppl){
    assert(system != NULL);
    if (num_ppl <= 0){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    if (strcmp(email, "@4") == 0 && num_ppl == 1){                                  ///// =======================================================
        int num=3;
        num++;
    }
    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email escaper_email = emailCreate(email, &email_error);
    if (email_error != EMAIL_SUCCESS){
        return convertEmailToEscapeTechnionError(email_error);
    }
    
    Escaper new_escaper = findEscaperByEmail(system, escaper_email);
    if (new_escaper == NULL){
        emailDestroy(escaper_email);
        return ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    
    int skill_level = escaperGetSkillLevel(new_escaper);
    TechnionFaculty escaper_faculty = escaperGetFaculty(new_escaper);
    int max_calc_recommend_room = -1;
    int calc_recommend_room = 0;
    int recommend_id = 0;
    TechnionFaculty recommend_faculty = -1;
    int size = setGetSize(system->companies);
    SET_FOREACH(Company, current_company, system->companies){
        size--;
        int tmp_room_id = 0;
        calc_recommend_room = companyRecommendedRoom(current_company, num_ppl, skill_level, &tmp_room_id);
        if (calc_recommend_room == -1){
            continue;
        }
        if (calc_recommend_room < max_calc_recommend_room || max_calc_recommend_room == -1){
            max_calc_recommend_room = calc_recommend_room;
            recommend_id = tmp_room_id;
            recommend_faculty = companyGetFaculty(current_company);
        } else if (calc_recommend_room == max_calc_recommend_room){
            if (abs((int)(escaper_faculty - companyGetFaculty(current_company))) < abs((int)(escaper_faculty - recommend_faculty))){
                max_calc_recommend_room = calc_recommend_room;
                recommend_id = tmp_room_id;
                recommend_faculty = companyGetFaculty(current_company);
            } else if (abs((int)(escaper_faculty - companyGetFaculty(current_company))) == abs((int)(escaper_faculty - recommend_faculty))){
                if (companyGetFaculty(current_company) < recommend_faculty){
                    max_calc_recommend_room = calc_recommend_room;
                    recommend_id = tmp_room_id;
                    recommend_faculty = companyGetFaculty(current_company);
                } else if (companyGetFaculty(current_company) == recommend_faculty){
                    if (tmp_room_id < recommend_id){
                        max_calc_recommend_room = calc_recommend_room;
                        recommend_id = tmp_room_id;
                        recommend_faculty = companyGetFaculty(current_company);
                    }
                }
            }
        }
    }
/*
    
    int recommended_room_id = 0;
    int max_calc_recommend_room = 0;
    int calc_recommend_room = 0;
    int recommend_id = 0;
    
    
    
    TechnionFaculty recommened_faculty = ELECTRICAL_ENGINEERING;
    SET_FOREACH(Company, tmp_company, system->companies){
        calc_recommend_room = companyRecommendedRoom(tmp_company, num_ppl, skill_level, &recommended_room_id);
        if (calc_recommend_room > max_calc_recommend_room){
            recommened_faculty = companyGetFaculty(tmp_company);
            max_calc_recommend_room = calc_recommend_room;
            recommend_id = recommended_room_id;
        } else if (calc_recommend_room == max_calc_recommend_room){
            if (abs(escaper_faculty-recommened_faculty) >
                    abs(escaper_faculty-companyGetFaculty(tmp_company)) ||
                    abs(escaper_faculty-recommened_faculty) ==
                    abs(escaper_faculty-companyGetFaculty(tmp_company))) {
                recommened_faculty = companyGetFaculty(tmp_company);
                max_calc_recommend_room = calc_recommend_room;
                recommend_id = recommended_room_id;
            }
        }
    }
*/
    if (recommend_id == 0){
        emailDestroy(escaper_email);
        return ESCAPE_TECHNION_NO_ROOMS_AVAILABLE;
    }
    char* time = findClosestTime(system, recommend_faculty, recommend_id, escaper_email);
    EscapeTechnionErrorCode system_error = escapeTechnionAddOrder(system, email, recommend_faculty, recommend_id, time, num_ppl);
    free(time);
    emailDestroy(escaper_email);
    return system_error;
}

static char* findClosestTime(EscapeTechnion system, TechnionFaculty room_faculty, int room_id, Email escaper_email){
    assert(system != NULL);
    Room room = findRoomInSystem(system, room_faculty, room_id);
    assert(room != NULL);

    int day = 0;
    int hour = roomGetOpenTime(room);
    bool flag = true;
    if (listGetSize(system->orders) == 0){
        return timeIntToChar(day, hour);
    }

/*    OrderErrorCode order_error = ORDER_SUCCESS;
    List escaper_orders = listFilter(system->orders, filterOrdersOfEscaper, escaper_email);
    Order tmp_order = orderCreate(0, 0, 1, room_faculty, escaper_email, 1, 4, escaper_email, &order_error);
    List room_orders = listFilter(system->orders, filterOrdersOfRoom, tmp_order);
    listSort(escaper_orders, escapeTechnionOrderDayCompare);
    listSort(room_orders, escapeTechnionOrderDayCompare);
    orderDestroy(tmp_order);
    while (flag == true) {
        flag = false;
        LIST_FOREACH(Order, tmp_order, escaper_orders){
            if (orderGetDaysTillOrder(tmp_order) == day && orderGetTimeOfOrder(tmp_order) == hour){
                flag = true;
                break;
            }
            LIST_FOREACH(Order, tmp_order2, room_orders){
                if (orderGetDaysTillOrder(tmp_order) == day && orderGetTimeOfOrder(tmp_order) == hour){
                    flag = true;
                    break;
                }
            }
            if (flag == true){
                break;
            }
        }
        if (flag == true){
            ++hour;
            if (hour == roomGetCloseTime(room)) {
                ++day;
                hour = roomGetOpenTime(room);
            }
        }
    }
*/
    
    listSort(system->orders, escapeTechnionOrderDayCompare);
    while(flag == true) {
//        bool changed = false;
        LIST_FOREACH(Order, tmp_order, system->orders) {
            flag = false;
            
            LIST_FOREACH(Order, tmp_order2, system->orders){
                if (orderGetDaysTillOrder(tmp_order2) == day && orderGetTimeOfOrder(tmp_order2) == hour){
                    if (emailCompare(escaper_email, orderGetEscaperEmail(tmp_order2)) == 0){
                        flag = true;
                        break;
                    } else if (orderGetRoomId(tmp_order2) == room_id){
                        flag = true;
                        break;
                    }
                }
            }
            if (flag == true && orderGetTimeOfOrder(tmp_order) == hour && orderGetDaysTillOrder(tmp_order) == day){
                ++hour;
                if (hour == roomGetCloseTime(room)) {
                    ++day;
                    hour = roomGetOpenTime(room);
                }
//                changed = true;
            }
        }
/*        if (changed == false){
            ++hour;
            if (hour == roomGetCloseTime(room)) {
                ++day;
                hour = roomGetOpenTime(room);
            }
        }
*/    }
  
    
    
/*
            if (checkRoomOrdersAtTime(system, , day, hour)){
//            if (orderGetRoomId(tmp_order) == room_id) {
                if (orderGetTimeOfOrder(tmp_order) == hour && orderGetDaysTillOrder(tmp_order) == day) {
                    ++hour;
                    if (hour == roomGetCloseTime(room)) {
                        ++day;
                        hour = roomGetOpenTime(room);
                    }
//                    if (hour < roomGetCloseTime(room)) {
//                        ++hour;
//                    } else if (hour == roomGetCloseTime(room)) {
//                        ++day;
//                        hour = roomGetOpenTime(room);
//                    }
                    flag = true;
                }
            } else if (checkEscaperOrdersAtTime(system, escaper_email, day, hour) == false){
//            } else if (emailCompare(orderGetEscaperEmail(tmp_order),escaper_email) == 0){
                if (orderGetTimeOfOrder(tmp_order) == hour && orderGetDaysTillOrder(tmp_order) == day) {
                    ++hour;
                    if (hour == roomGetCloseTime(room)) {
                        ++day;
                        hour = roomGetOpenTime(room);
                    }
//                }else if (hour == roomGetCloseTime(room)) {
//                    ++day;
//                    hour = roomGetOpenTime(room);
//                }
                    flag = true;
                }
            }
        }
    }
*/
    return timeIntToChar(day, hour);
}

EscapeTechnionErrorCode escapeTechnionReportDay(EscapeTechnion system,
                                                FILE* outputChannel){
    assert(system != NULL);
    addIncomeToTotalRevenue(system);
    List last_day_orders = listFilter(system->orders, filterOrdersOfLastDay,
                                      "no-key");
    if (last_day_orders == NULL){
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    if (listSort(last_day_orders, escapeTechnionOrderDayCompare)!=LIST_SUCCESS){
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    mtmPrintDayHeader(outputChannel, system->current_day,
                    listGetSize(last_day_orders));
    LIST_FOREACH(Order, current_order, last_day_orders){
        Escaper current_escaper = findEscaperByEmail(system,
                                        orderGetEscaperEmail(current_order));
        assert(current_order != NULL);
        TechnionFaculty faculty = findFacultyOfRoom(system,
                                            orderGetCompanyEmail(current_order),
                                            orderGetRoomId(current_order));
        Room current_room = findRoomInSystem(system, faculty,
                                             orderGetRoomId(current_order));
        roomDecNumberOfOrders(current_room);
        char* company_email = emailToStr(orderGetCompanyEmail(current_order));
        char* escaper_email = emailToStr(orderGetEscaperEmail(current_order));
        mtmPrintOrder(outputChannel,  escaper_email,
                      escaperGetSkillLevel(current_escaper),
                      escaperGetFaculty(current_escaper),
                      company_email, faculty, orderGetRoomId(current_order),
                      orderGetTimeOfOrder(current_order),
                      roomGetDifficulty(current_room),
                      orderGetPeopleNumber(current_order),
                      orderGetTotalPrice(current_order));
        free(company_email);
        free(escaper_email);
    }
    mtmPrintDayFooter(outputChannel, system->current_day);
    listDestroy(last_day_orders);
    List tmp_list = listFilter(system->orders, filterOrdersNotLastDay,"no-key");
    listDestroy(system->orders);
    system->orders = tmp_list;
    LIST_FOREACH(Order, current_order, system->orders){
        orderReduceDay(current_order);
    }
    system->current_day++;
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionReportBest(EscapeTechnion system,
                                                 FILE* outputChannel){
    assert(system != NULL);
    if (outputChannel == NULL){
        return ESCAPE_TECHNION_NULL_PARAMETER;
    }
    int tmp_revenue_arr[NUM_OF_FACULTYS] = {0};
    int total_revenue = 0;
    for (int i=0; i<NUM_OF_FACULTYS; i++){
        tmp_revenue_arr[i] = system->faculties_revenue[i];
        total_revenue += system->faculties_revenue[i];
    }
    mtmPrintFacultiesHeader(outputChannel, NUM_OF_FACULTYS, system->current_day,
                            total_revenue);
    for (int i=0; i<3; i++){
        int best_revenue = 0;
        for (int j=0; j< NUM_OF_FACULTYS; j++){
            if (tmp_revenue_arr[j] > tmp_revenue_arr[best_revenue]){
                best_revenue = j;
            }
        }
        mtmPrintFaculty(outputChannel, (TechnionFaculty)best_revenue,
                        tmp_revenue_arr[best_revenue]);
        tmp_revenue_arr[best_revenue] = -1;
    }
    mtmPrintFacultiesFooter(outputChannel);
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnion escapeTechnionCopy(EscapeTechnion system){
    assert(system != NULL);
    
    EscapeTechnion copies_system = malloc(sizeof(*copies_system));
    if (copies_system == NULL){
        return NULL;
    }
    copies_system->current_day = system->current_day;
    copies_system->companies = setCopy(system->companies);
    if (copies_system->companies == NULL){
        escapeTechnionDestroy(copies_system);
        return NULL;
    }
    copies_system->escapers = setCopy(system->escapers);
    if (copies_system->escapers == NULL){
        escapeTechnionDestroy(copies_system);
        return NULL;
    }
    copies_system->orders = listCopy(system->orders);
    if (copies_system->escapers == NULL){
        escapeTechnionDestroy(copies_system);
        return NULL;
    }
    return copies_system;
}



static bool filterOrdersOfEscaper(ListElement order, ListFilterKey email){
    assert(order != NULL && email != NULL);
    
    if (emailCompare(orderGetEscaperEmail(order), email) != 0){
        return true;
    }
    return false;
}

static EscapeTechnionErrorCode checkOrderAtTime(EscapeTechnion system,
              int faculty, int room_id, Email escaper_email, int day, int hour){
    assert(system != NULL && escaper_email != NULL);
    LIST_FOREACH(Order, tmp_order, system->orders){
        if(day == orderGetDaysTillOrder(tmp_order) &&
           orderGetTimeOfOrder(tmp_order) == hour &&
           emailCompare(escaper_email, orderGetEscaperEmail(tmp_order)) == 0){
            return ESCAPE_TECHNION_CLIENT_IN_ROOM;
        }
        if (orderGetRoomId(tmp_order) == room_id &&
            day == orderGetDaysTillOrder(tmp_order)  &&
            orderGetTimeOfOrder(tmp_order) == hour &&
            orderGetFaculty(tmp_order) == faculty){
            return ESCAPE_TECHNION_ROOM_NOT_AVAILABLE;
        }
    }
    return ESCAPE_TECHNION_SUCCESS;
}

static char* timeIntToChar(int day, int hour){
    int temp_day = day;
    int i=0;
    do{
        i++;
        temp_day = temp_day/10;
        
    } while (1 < temp_day);
    
    char* str = malloc(3+i*sizeof(char));
    if (str == NULL){
        return NULL;
    }
    
    sprintf(str, "%d-%d", day, hour);
    return str;
}

static void addIncomeToTotalRevenue(EscapeTechnion system){
    assert(system != NULL);
    
    listSort(system->orders, escapeTechnionOrderDayCompare);
    LIST_FOREACH(Order, current_order, system->orders){
        if (orderGetDaysTillOrder(current_order) != 0){
            break;
        }
        SET_FOREACH(Company, current_company, system->companies){
            if (emailCompare(companyGetEmail(current_company),
                             orderGetCompanyEmail(current_order)) == 0){
                system->faculties_revenue[companyGetFaculty(current_company)] +=
                orderGetTotalPrice(current_order);
                break;
            }
        }
    }
}

static bool checkIfEmailExistInSystem(EscapeTechnion system, char* email){
    assert(system != NULL && email != NULL);
    
    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email tmp_email = emailCreate(email, &email_error);
    if (email_error != EMAIL_SUCCESS){
        return false;
    }
    
    SET_FOREACH(Company, current_company, system->companies){
        if (emailCompare(companyGetEmail(current_company),tmp_email) == 0){
            emailDestroy(tmp_email);
            return true;
        }
    }
    SET_FOREACH(Escaper, current_escaper, system->escapers){
        if (emailCompare(escaperGetEmail(current_escaper),tmp_email) == 0){
            emailDestroy(tmp_email);
            return true;
        }
    }
    emailDestroy(tmp_email);
    return false;
}

static Escaper findEscaperByEmail(EscapeTechnion system, Email escaper_email){
    assert(system != NULL && escaper_email != NULL);
    
    SET_FOREACH(Escaper, current_escaper, system->escapers){
        if (emailCompare(escaperGetEmail(current_escaper), escaper_email) == 0){
            return current_escaper;
        }
    }
    return NULL;
}

static Company findCompanysRoom(EscapeTechnion system, TechnionFaculty faculty,
                                int room_id){
    assert(0 < room_id && system != NULL);
    SET_FOREACH(Company, tmp_company, system->companies){
        if (companyGetFaculty(tmp_company) == faculty){
            CompanyErrorCode company_error = COMPANY_SUCCESS;
            if (companyGetRoom(tmp_company, room_id, &company_error) != NULL){
                return tmp_company;
            }
        }
    }
    return NULL;
}

static Room findRoomInSystem(EscapeTechnion system ,TechnionFaculty faculty ,
                             int room_id){
    assert(0 < room_id && system != NULL);
    
    SET_FOREACH(Company, tmp_company, system->companies){
        if (companyGetFaculty(tmp_company) == faculty){
            CompanyErrorCode company_error = COMPANY_SUCCESS;
            Room room = companyGetRoom(tmp_company, room_id, &company_error);
            if (room != NULL && company_error == COMPANY_SUCCESS){
                return room;
            }
        }
    }
    return NULL;
}

static TechnionFaculty findFacultyOfRoom(EscapeTechnion system ,
                                         Email company_email ,int room_id){
    assert(0 < room_id && company_email != NULL && system != NULL);
    
    SET_FOREACH(Company, tmp_company, system->companies){
        CompanyErrorCode company_error = COMPANY_SUCCESS;
        if (emailCompare(companyGetEmail(tmp_company),company_email) == 0){
            Room room = companyGetRoom(tmp_company, room_id, &company_error);
            if (room != NULL && company_error == COMPANY_SUCCESS){
                return companyGetFaculty(tmp_company);
            }
        }
    }
    return -1;
}

static bool checkRoomInFaculty(EscapeTechnion system, TechnionFaculty faculty,
                               Room room){
    assert(system != NULL);
    
    SET_FOREACH(Company, tmp_company, system->companies){
        if (companyGetFaculty(tmp_company) == faculty){
            if (companyRoomIsIn(tmp_company, room) == true){
                return true;
            }
        }
    }
    return false;
}

static void escapeTechnionCompanyDestroy(SetElement company){
    companyDestroy(company);
}

static SetElement escapeTechnionCompanyCopy(SetElement company){
    return companyCopy(company);
}

static int escapeTechnionCompanyCompare(SetElement company1,
                                        SetElement company2){
    return companyCompare(company1, company2);
}

static void escapeTechnionEscaperDestroy(SetElement escaper){
    escaperDestroy(escaper);
}

static SetElement escapeTechnionEscaperCopy(SetElement escaper){
    return escaperCopy(escaper);
}

static int escapeTechnionEscaperCompare(SetElement escaper1,
                                        SetElement escaper2){
    return escaperComapare(escaper1, escaper2);
}

static void escapeTechnionOrderDestroy(SetElement order){
    orderDestroy(order);
}

static SetElement escapeTechnionOrderCopy(SetElement order){
    return orderCopy(order);
}

static int escapeTechnionOrderDayCompare(SetElement order1, SetElement order2){
    if (order1 == NULL){
        return 1;
    }
    if (order2 == NULL){
        return -1;
    }
    int flag = orderDayCompare(order1, order2);
    if (flag != 0){
        return -flag;
    }
    if (orderGetFaculty(order1) > orderGetFaculty(order2)){
        return 1;
    } else if (orderGetFaculty(order1) < orderGetFaculty(order2)){
        return -1;
    } else{
        if (orderGetRoomId(order1) > orderGetRoomId(order2)){
            return 1;
        } else if (orderGetRoomId(order1) < orderGetRoomId(order2)){
            return -1;
        }
    }
    assert(1); // can't get here
    return 0;
}

static bool filterOrdersOfLastDay(ListElement order, ListFilterKey key){
    assert(order != NULL && key != NULL);
    
    if (orderGetDaysTillOrder(order) == 0){
        return true;
    }
    return false;
}

static bool filterOrdersNotLastDay(ListElement order, ListFilterKey key){
    assert(order != NULL && key != NULL);
    
    if (orderGetDaysTillOrder(order) != 0){
        return true;
    }
    return false;
}

static bool convertTimeToDayNHour(char* time, int* day, int* hour){
    assert(time != NULL && day != NULL && hour != NULL);
    
    int i=0;
    bool hyphen = false;
    while(time[i] != 0){
        if (time[i] != '-'){
            if (time[i] < '0' || '9' < time[i]){
                return false;
            }
        } else if (time[i] == '-' && hyphen == true){
            return false;
        }
        i++;
    }
    time = strtok(time, "-");
    *day = atoi(time);
    time = strtok(NULL, "-");
    *hour = atoi(time);
    if (*hour < 0 || 23 < *hour){
        return false;
    }
    if (*day < 0){
        return false;
    }
    return true;
}

static EscapeTechnionErrorCode convertCompanyToEscapeTechnionError(CompanyErrorCode error_company){
    switch (error_company){
        case COMPANY_OUT_OF_MEMORY:
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
            break;
        case COMPANY_NULL_PARAMETER:
            return ESCAPE_TECHNION_NULL_PARAMETER;
            break;
        case COMPANY_INVALID_PARAMETER:
            return ESCAPE_TECHNION_INVALID_PARAMETER;
            break;
        case COMPANY_ID_ALREADY_EXIST:
            return ESCAPE_TECHNION_ID_ALREADY_EXIST;
            break;
        case COMPANY_RESERVATION_EXISTS:
            return ESCAPE_TECHNION_RESERVATION_EXISTS;
            break;
        case COMPANY_ID_DOES_NOT_EXIST:
            return ESCAPE_TECHNION_ID_DOES_NOT_EXIST;
            break;
        case COMPANY_SUCCESS:
            return ESCAPE_TECHNION_SUCCESS;
            break;
    }
    return ESCAPE_TECHNION_INVALID_PARAMETER;
}

static EscapeTechnionErrorCode convertRoomToEscapeTechnionError(RoomErrorCode error_room){
    switch (error_room){
        case ROOM_OUT_OF_MEMORY:
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
            break;
        case ROOM_NULL_PARAMETER:
            return ESCAPE_TECHNION_NULL_PARAMETER;
            break;
        case ROOM_INVALID_PARAMETER:
            return ESCAPE_TECHNION_INVALID_PARAMETER;
            break;
        case ROOM_SUCCESS:
            return ESCAPE_TECHNION_SUCCESS;
            break;
    }
    return ESCAPE_TECHNION_INVALID_PARAMETER;
}

static EscapeTechnionErrorCode convertEmailToEscapeTechnionError(EmailErrorCode error_email){
    switch (error_email){
        case EMAIL_OUT_OF_MEMORY:
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
            break;
        case EMAIL_NULL_PARAMETER:
            return ESCAPE_TECHNION_NULL_PARAMETER;
            break;
        case EMAIL_INVALID_PARAMETER:
            return ESCAPE_TECHNION_INVALID_PARAMETER;
            break;
        case EMAIL_SUCCESS:
            return ESCAPE_TECHNION_SUCCESS;
            break;
    }
    return ESCAPE_TECHNION_INVALID_PARAMETER;
}

static EscapeTechnionErrorCode convertEscaperToEscapeTechnionError(EscaperErrorCode escaper_error){
    switch (escaper_error){
        case ESCAPER_OUT_OF_MEMORY:
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
            break;
        case ESCAPER_NULL_PARAMETER:
            return ESCAPE_TECHNION_NULL_PARAMETER;
            break;
        case ESCAPER_INVALID_PARAMETER:
            return ESCAPE_TECHNION_INVALID_PARAMETER;
            break;
        case ESCAPER_SUCCESS:
            return ESCAPE_TECHNION_SUCCESS;
            break;
    }
    return ESCAPE_TECHNION_INVALID_PARAMETER;
}

static EscapeTechnionErrorCode convertOrderToTechnionErrorCode(OrderErrorCode order_error){
    switch (order_error){
        case ORDER_OUT_OF_MEMORY:
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
            break;
        case ORDER_NULL_PARAMETER:
            return ESCAPE_TECHNION_NULL_PARAMETER;
            break;
        case ORDER_INVALID_PARAMETER:
            return ESCAPE_TECHNION_INVALID_PARAMETER;
            break;
        case ORDER_SUCCESS:
            return ESCAPE_TECHNION_SUCCESS;
            break;
    }
    return ESCAPE_TECHNION_INVALID_PARAMETER;
}

static EscapeTechnionErrorCode convertListToTechnionErrorCode(ListResult list_error){
    switch (list_error){
        case LIST_OUT_OF_MEMORY:
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
            break;
        case LIST_NULL_ARGUMENT:
            return ESCAPE_TECHNION_NULL_PARAMETER;
            break;
        case LIST_INVALID_CURRENT:
            return ESCAPE_TECHNION_INVALID_PARAMETER;
            break;
        case LIST_SUCCESS:
            return ESCAPE_TECHNION_SUCCESS;
            break;
    }
    return ESCAPE_TECHNION_INVALID_PARAMETER;
}
