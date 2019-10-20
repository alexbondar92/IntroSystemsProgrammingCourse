#ifndef ESCAPE_TECHNION_H_
#define ESCAPE_TECHNION_H_

#include <stdbool.h>
#include "mtm_ex3.h"

/**
 * EscapeTechnion Container
 *
 * Implements a company container type.
 *
 * The following functions are available:
 *
 *   escapeTechnionCreate           - Creates a new company
 *   escapeTechnionDestroy          - Deletes an existing company and frees all resources
 *   escapeTechnionAddCompany       - Create a new company in the system
 *   escapeTechnionRemoveCompany    - Remove a company from the system
 *   escapeTechnionAddRoom          -
 *   escapeTechnionRemoveRoom       -
 *   escapeTechnionAddEscaper       -
 *   escapeTechnionRemoveEscaper    -
 *   escapeTechnionAddOrder         -
 *   escapeTechnionRecommendedOrder -
 *   escapeTechnionReportDay        -
 *   escapeTechnionReportBest       -
 *   escapeTechnionCopy             -
 */

/**
 * This type defines all errors for the EscapeTechnion ADT.
 */
typedef enum {
    ESCAPE_TECHNION_OUT_OF_MEMORY, // You should exit program after this error
//    ESCAPE_TECHNION_INVALID_COMMAND_LINE_PARAMETERS, // You should exit program after this error
//    ESCAPE_TECHNION_CANNOT_OPEN_FILE, // You should exit program after this error
    ESCAPE_TECHNION_NULL_PARAMETER,
    ESCAPE_TECHNION_INVALID_PARAMETER,
    ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS,
    ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST,
    ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST,
    ESCAPE_TECHNION_ID_ALREADY_EXIST,
    ESCAPE_TECHNION_ID_DOES_NOT_EXIST,
    ESCAPE_TECHNION_CLIENT_IN_ROOM,
    ESCAPE_TECHNION_ROOM_NOT_AVAILABLE,
    ESCAPE_TECHNION_RESERVATION_EXISTS,
    ESCAPE_TECHNION_NO_ROOMS_AVAILABLE,
    ESCAPE_TECHNION_SUCCESS
} EscapeTechnionErrorCode;

/** Type for defining the EscapeTechnion */
typedef struct EscapeTechnion_t *EscapeTechnion;


/**
 * Create a new EscapeTechnion.
 *
 * Creates a new escape system object. This function initiate the system for the
 * first time.
 *
 * @param error the error returning parameter code
 * @return
 * in case of allocation fail, return ESCAPE_TECHNION_OUT_OF_MEMORY
 * in case of success, returns new system object and ESCAPE_TECHNION_SUCCESS
 */
EscapeTechnion escapeTechnionCreate(EscapeTechnionErrorCode* error);

/**
 * Deallocates an existing escape technion system. Clears all elements by using the
 * stored free function.
 *
 * @param system Target to be deallocated. If company is NULL nothing will be
 * done
 */
void escapeTechnionDestroy(EscapeTechnion system);

/**
 * Create a new company in the system.
 *
 * add new company to the set to companies in the system. This function initiate
 * the company by the relevent parameters and reset the rest.
 *
 * @param system the EscapeTechnion object
 * @param email the string of email for the new company
 * @param faculty the faculty that the new company is assigned to
 * @return
 * in case of allocation fail, return ESCAPE_TECHNION_OUT_OF_MEMORY
 * in case of invaild parameters, return ESCAPE_TECHNION_INVALID_PARAMETER
 * in case that the email is already owned by another company 
 *         in the system ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS
 * in case of success, returns ESCAPE_TECHNION_SUCCESS
 */
EscapeTechnionErrorCode escapeTechnionAddCompany(EscapeTechnion system,
                                        char* email, TechnionFaculty faculty);

/**
 * Remove company from the system.
 *
 * remove company from the set to companies in the system. It can be removed 
 * only if the company without any future orders
 *
 * @param system the EscapeTechnion object
 * @param email the string of email of the company to delete
 * @return
 * in case of allocation fail, return ESCAPE_TECHNION_OUT_OF_MEMORY
 * in case of invaild parameters, return ESCAPE_TECHNION_INVALID_PARAMETER
 * in case there is future orders at this room, return ESCAPE_TECHNION_RESERVATION_EXISTS
 * in case of success, returns ESCAPE_TECHNION_SUCCESS
 */
EscapeTechnionErrorCode escapeTechnionRemoveCompany(EscapeTechnion system,
                                        char* email);

/**
 * Create a new room in a relevent company.
 *
 * add new room to the relevent company in the system. This function initiate
 * the room by the relevent parameters.
 *
 * @param system the EscapeTechnion object
 * @param email the string of email for the relevent company
 * @param room_id the id number of the new room
 * @param price the price for the visiting the new room
 * @param num_ppl the recomended number of people at this room
 * @param working_hrs the opening and closing hours for this room
 * @param difficulty the difficulty level of that room
 * @return
 * in case of allocation fail, return ESCAPE_TECHNION_OUT_OF_MEMORY
 * in case of invaild parameters, return ESCAPE_TECHNION_INVALID_PARAMETER
 * in case that the email is doesn't belong to any comapny at 
 *      the system, ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST
 * in case there is already a room this the same id at this company or to one 
 *      of other companies of the same faculty, ESCAPE_TECHNION_ID_ALREADY_EXIST
 * in case of success, returns ESCAPE_TECHNION_SUCCESS
 */
EscapeTechnionErrorCode escapeTechnionAddRoom(EscapeTechnion system, char* email,
                    int room_id, int price, int num_ppl, char* working_hrs, int difficulty);




EscapeTechnionErrorCode escapeTechnionRemoveRoom(EscapeTechnion system,
                                              TechnionFaculty faculty, int room_id);

EscapeTechnionErrorCode escapeTechnionAddEscaper(EscapeTechnion system, char* email,
                                         TechnionFaculty faculty, int skil_level);

EscapeTechnionErrorCode escapeTechnionRemoveEscaper(EscapeTechnion system, char* email);

EscapeTechnionErrorCode escapeTechnionAddOrder(EscapeTechnion system, char* email,
                          TechnionFaculty faculty, int id, char* time, int num_ppl);

EscapeTechnionErrorCode escapeTechnionRecommendedOrder(EscapeTechnion system, char* email, int num_ppl);

EscapeTechnionErrorCode escapeTechnionReportDay(EscapeTechnion system, FILE* outputChannel);

EscapeTechnionErrorCode escapeTechnionReportBest(EscapeTechnion system, FILE* outputChannel);

EscapeTechnion escapeTechnionCopy(EscapeTechnion system);

#endif /* ESCAPE_TECHNION_H_ */
