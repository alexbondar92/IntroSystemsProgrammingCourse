#ifndef ESCAPER_H_
#define ESCAPER_H_

#include <stdbool.h>
#include "escape_utilitis.h"
#include "mtm_ex3.h"

/**
 * Escaper Container
 *
 * Implements a escaper container type.
 *
 * The following functions are available:
 *
 *   escaperCreate          - Creates a new escaper
 *   escaperDestroy         - Deletes an existing escaper and frees all
 *                            resources
 *   escaperGetEmail        - Getting the Email of a escaper
 *   escaperGetFaculty      - Getting the faculty of a escaper
 *   escaperGetSkillLevel   - Getting the skill level of a escaper
 *   escaperCopy            - Make a copy of escaper
 *   escaperComaper         - Comparing between two escapers(by email)
 */

/** Type for defining the escaper */
typedef struct Escaper_t *Escaper;

/**
 * This type defines all errors for the Escaper ADT.
 */
typedef enum {
    ESCAPER_OUT_OF_MEMORY,
    ESCAPER_NULL_PARAMETER,
    ESCAPER_INVALID_PARAMETER,
    ESCAPER_SUCCESS
} EscaperErrorCode;



/**
 * Create a new Escaper.
 *
 * Creates a new escaper. This function receive all the data for first initial
 * of new escaper, and reset the rest.
 * @param email of the current new escaper
 * @param faculty the fuculty that ownes this escaper
 * @param skill_level the skill level of this escaper
 * @param error the error returning parameter code
 * @return
 * ESCAPER_NULL_PARAMETER if email is ptr to NULL
 * ESCAPER_INVALID_PARAMETER in case of invaild one or more of parameters
 * ESCAPER_OUT_OF_MEMORY in case of allocation fail
 * ESCAPER_SUCCESS in case of success, returns new escaper object
 */
Escaper escaperCreate(char *email, TechnionFaculty faculty, int skill_level,
                      EscaperErrorCode *error);

/**
 * Deallocates an existing escaper. Clears all elements by using the
 * stored free function.
 *
 * @param escaper Target to be deallocated. If escaper is NULL nothing will be
 * done
 */
void escaperDestroy(Escaper escaper);

/**
 * Returns the email of the current escaper.
 *
 * @param escaper the current room object to get from(its assume that room
 * not null)
 * @return
 * the email of the escaper.
 */
Email escaperGetEmail(Escaper escaper);

/**
 * Returns the faculty of the current escaper.
 *
 * @param escaper the current room object to get from(its assume that room
 * not null)
 * @return
 * The faculty of the escaper.
 */
TechnionFaculty escaperGetFaculty(Escaper escaper);

/**
 * Returns the skill level of the current escaper.
 *
 * @param escaper the current object to get from(its assume that room not null)
 * @return
 * The skill level of the escaper.
 */
int escaperGetSkillLevel(Escaper escaper);

/**
 * this function makes copy of escaper
 * @param escaper the current object to make a copy
 * @return
 * returns a copied escaper object
 */
Escaper escaperCopy(Escaper escaper);

/**
 * this function compares between escapers by email
 * @return
 * 0 if equal, 1 if param1 id is bigger then param2 id, otherwise -1
 */
int escaperComapare(Escaper escaper1, Escaper escaper2);

#endif /*ESCAPER_H_*/
