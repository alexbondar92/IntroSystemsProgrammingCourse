#ifndef COMPANY_H_
#define COMPANY_H_

#include <stdbool.h>
#include "escape_utilitis.h"
#include "mtm_ex3.h"
#include "room.h"

/**
 * Company Container
 *
 * Implements a company container type.
 *
 * The following functions are available:
 *
 *   companyCreate                   - Creates a new company
 *   companyDestroy                  - Deletes an existing company and frees all resources
 *   companyGetEmail                 - Getting the Email of a company
 *   companyGetFaculty               - Getting the faculty of a company
 *   companyCopy                     - Make a copy of a company
 *   companyAddRoom                  - Add new room to company
 *   companyRemoveRoom               - Remove room from company
 *   companyCompare                  - Comparing to companies(by email)
 *   companyGetNumberOfTotalOrders   - get number of orders for company
 *   companyDecNumberOfOrderIsInRoom - decreases the number of rooms at the company
 *   companyRoomIsIn                 - check if there is a room with the same id
 *   companyGetRoom                  - returns the room at the company
 *   companyRecommendedRoom          - find the most recommended room at the company
 */

/**
 * This type defines all errors for the Company ADT.
 */
typedef enum {
    COMPANY_OUT_OF_MEMORY, // You should exit program after this error
    COMPANY_NULL_PARAMETER,
    COMPANY_INVALID_PARAMETER,
    COMPANY_ID_ALREADY_EXIST,
    COMPANY_RESERVATION_EXISTS,
    COMPANY_ID_DOES_NOT_EXIST,
    COMPANY_SUCCESS
} CompanyErrorCode;

/** Type for defining the company */
typedef struct Company_t *Company;


/**
 * Create a new Company.
 *
 * Creates a new company. This function resive all the data for first initial of
 * new company, and reset the rest.
 *
 * @param email of the current new Company assumption that null won't be sent.
 * @param faculty the fuculty that ownes this company.
 * @param error the error returning parameter code
 * @return
 * in case of invaild one or more of parameters,return COMPANY_INVALID_PARAMETER
 * in case of allocation fail, return CMAPNY_OUT_OF_MEMORY
 * in case of success, returns new escaper object and COMPANY_SUCCESS
 */
Company companyCreate(char* email, TechnionFaculty faculty,
                      CompanyErrorCode* error);

/**
 * Deallocates an existing company. Clears all elements by using the
 * stored free function.
 *
 * @param company Target to be deallocated. If company is NULL nothing will be
 * done
 */
void companyDestroy(Company company);

/**
 * Returns the email of the current company.
 *
 * @param company the current company object to get from(its assume that room 
 * not null)
 * @return
 * the email of the company.
 */
Email companyGetEmail(Company company);

/**
 * Returns the faculty of the current company.
 *
 * @param company The target company which faculty is requested.
 * @return
 * the faculty of the company.
 */
TechnionFaculty companyGetFaculty(Company company);

/**
 * create a copy of this company
 *
 * @param company The company copy with.
 * @return
 * returns a copy of the copmany element
 */
Company companyCopy(Company company);

/**
 * Adding new room to the current company.
 *
 * @param company The company that own the new room
 * @param room a room element with data that we copy to the new room
 * @return
 * COMPANY_ID_ALREADY_EXIST - in case there is already a room with the same id
 * COMAPNY_OUT_OF_MEMORY in case of allocation fail
 * COMPANY_SUCCESS - in case of success, the new room added
 */
CompanyErrorCode companyAddRoom(Company company, Room room);

/**
 * Removing room from the current company.
 *
 * @param company The company to remove room from
 * @param room_id The room id that needed to remove
 * @return
 * COMPANY_INVALID_PARAMETER - in case param room_id is invalid
 * COMPANY_ID_DOES_NOT_EXIST - in case there isn't relevant room in this company
 * with the same id
 * COMPANY_RESERVATION_EXISTS - in case there is an open orders for that room
 * COMPANY_SUCCESS - in case of success, the room had been removed
 */
CompanyErrorCode companyRemoveRoom(Company company,int room_id);

/**
 * comparing the companies by thier emails(uniq).
 *
 * @param company1 The first company to compare with
 * @param company2 The second company to compare to
 * @return
 * A positive integer if the first element is greater,
 * 0 if they're equal,
 * A negative integer if the second element is greater.
 */
int companyCompare(Company company1, Company company2);

/**
 * this function get the number of orders for rooms at current company
 * @param company the current company object to get from(its assume that company 
 * not null)
 * @return
 * the number of active orders for this company
 */
int companyGetNumberOfTotalOrders(Company company);

/**
 * this function decrease the number of orders for room at current company
 * @param company the current company witch own the room(its assume that company 
 * not null)
 * @param room_id the id of the room witch needed to decrease number of orders
 */
void companyDecNumberOfOrdersInRoom(Company company, int room_id);

/**
 * this function checks if there is already a room with the same id
 * @param company the current company object to check(its assume that company 
 * not null)
 * @return
 * true if there is a room with the same id, false if there is no room with the 
 * same id
 */
bool companyRoomIsIn(Company company, Room room);

/**
 * this function checks if there is a room with the same id
 * @param company the current company object to check(its assume that company 
 * not null)
 * @param room_id the id of the room
 * @param error error code
 * @return
 * the room if there is a room with the same id, NULL if there is no room with 
 * the same id
 */
Room companyGetRoom(Company company, int room_id, CompanyErrorCode* error);

/**
 * this function returns the calculation for the most recommended room
 * @param company the current company object to check(its assume that company 
 * not null)
 * @param p_e the number of people that are sent to the most recommended order
 * @param skill_level the skill level of the escaper that wants to make order
 * @param id a ptr
 * @return
 * the calculetion for the most recommended room at the company
 * id will get the room id of the most recommended room at the company
 */
int companyRecommendedRoom (Company company, int p_e, int skill_level, int* id);


#endif /*COMPANY_H_*/
