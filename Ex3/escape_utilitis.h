#ifndef ESCAPE_UTILITIES_H_
#define ESCAPE_UTILITIES_H_

#include <stdio.h>
#include <stdbool.h>
#include "mtm_ex3.h"


//#define NUM_OF_FACULTYS (18)
#define NUM_OF_FACULTYS UNKNOWN         // unknown is the last faculty


/**
 * Email Container
 *
 * Implements a email container type.
 *
 * The following functions are available:
 *
 *   emailCreate        - Creates a new email
 *   emailDestroy       - Deletes an existing email and frees all resources
 *   emailCompare       - Comparing the emails
 *   emailCopy          - Make a copy of email
 *   emailToStr         - Convert email to a string(char*)
 */

/**
 * This type defines all errors for the Room ADT.
 */
typedef enum {
    EMAIL_OUT_OF_MEMORY, // You should exit program after this error
    EMAIL_NULL_PARAMETER,
    EMAIL_INVALID_PARAMETER,
    EMAIL_SUCCESS
} EmailErrorCode;

/** Type for defining the company */
typedef struct Email_t *Email;


/**
 * Create a new Email.
 *
 * Creates a new email. This function resive string of email.
 * in addition checks that the email is ligal(there is one '@' in email addr).
 * @param email_address string of the new Email container
 * @return
 * 	NULL - in case the email is iligal or allocations failed.
 * 	A new Email in case of success.
 */
Email emailCreate(char* email_address, EmailErrorCode *error);

/**
 * Deallocates an existing email. Clears all elements by using the
 * stored free function.
 *
 * @param email Target to be deallocated. If email is NULL nothing will be
 * done
 */
void emailDestroy(Email email);

/**
 * Returns if the emails are equal.
 *
 * @param email1 The first email to compare to.
 * @param email2 The second email to compare with.
 * @return
 * 0 if the emails are equal.
 * 1 if the first email is bigger.
 * -1 if the second email is bigger.
 */
int emailCompare(Email email1, Email email2);

/**
 * Create a copy of Email.
 *
 * Creates a copy of email. This function resive email.
 * @param email The email to copy from
 * @return
 * 	NULL - in case allocations failed.
 * 	A copy of Email in case of success.
 */
Email emailCopy(Email email);

/**
 * .Turn Email to str.
 *
 * Creates str copy of email address. This function resive email and pointer for 
 * the str.
 * @param email The email to copy from.
 */
char* emailToStr(Email email);

#endif /*ESCAPE_UTILITIES_H_*/
