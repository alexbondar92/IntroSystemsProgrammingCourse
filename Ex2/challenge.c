#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>


#include "challenge.h"

/* IMPLEMENT HERE ALL WHAT IS NEEDED */


/* The init_challenge function
 * Purpose: initialize the challenge object.
 * Parameters: challenge - ptr to challenge, id - current challenge id,
 *             name - ptr to challenge name, level - level for this challenge.
 * Returns: NULL_PARAMETER - in case challenge or name equal NULL.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result init_challenge(Challenge *challenge, int id, char *name, Level level){
    if (challenge == NULL || name == NULL) {
        return NULL_PARAMETER;
    }
    int len_name = (int)strlen(name)+1;
    challenge->name = malloc(len_name*sizeof(char));
    if (challenge->name == NULL) {
        return MEMORY_PROBLEM;
    }
    memcpy(challenge->name, name, len_name);
    challenge->id = id;
    challenge->level = level;
    challenge->best_time = 0;
    challenge->num_visits = 0;
    return OK;
}

/* The reset_challenge function
 * Purpose: reset the chaleenge object.
 * Parameters: challenge - ptr to challenge.
 * Returns: NULL_PARAMETER - in case challenge equal NULL.
 *          OK - in case of success.
 */
Result reset_challenge(Challenge *challenge){
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    challenge->id = 0;
    free(challenge->name);
    challenge->name = NULL;
    challenge->level = 0;
    challenge->best_time = 0;
    challenge->num_visits = 0;
    return OK;
}

/* The change_name function
 * Purpose: changing the name of a existing challenge object.
 * Parameters: challenge - ptr to challenge, name - ptr to challenge name.
 * Returns: NULL_PARAMETER - in case challenge or name equal NULL.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result change_name(Challenge *challenge, char *name){
    if (challenge == NULL || name == NULL) {
        return NULL_PARAMETER;
    }
    int len_name = (int)strlen(name)+1;
    char* tmp_ptr = realloc(challenge->name, len_name*sizeof(char));
    if (tmp_ptr == NULL) {
        return MEMORY_PROBLEM;
    }
    challenge->name = tmp_ptr;
    memcpy(challenge->name, name, len_name);
    return OK;
}

/* The set_best_time_of_challenge function
 * Purpose: setting a best time for a challenge.
 * Parameters: challenge - ptr to challenge, time - time to set.
 * Returns: NULL_PARAMETER - in case challenge equal NULL.
 *          ILLEGAL_PARAMETER - in case the allocation failed.
 *          OK - in case of success.
 */
Result set_best_time_of_challenge(Challenge *challenge, int time) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    int best_time = challenge->best_time;
    if (time < 0 || (best_time < time && best_time != 0)) {
        return ILLEGAL_PARAMETER;
    }
    if (time != 0) {
        challenge->best_time = time;
    }
    return OK;
}

/* The best_time_of_challenge function
 * Purpose: getting the best time of a challenge.
 * Parameters: challenge - ptr to challenge, time - ptr to time as return value.
 * Returns: NULL_PARAMETER - in case challenge equal NULL.
 *          OK - in case of success.
 *          *time - best time of the challenge.
 */
Result best_time_of_challenge(Challenge *challenge, int *time) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    *time = challenge->best_time;
    return OK;
}

/* The inc_num_visits function
 * Purpose: increase number of visitors for a challenge.
 * Parameters: challenge - ptr to challenge.
 * Returns: NULL_PARAMETER - in case challenge equal NULL.
 *          OK - in case of success.
 */
Result inc_num_visits(Challenge *challenge){
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    challenge->num_visits++;
    return OK;
}

/* The num_visits function
 * Purpose: getting the number of visitors of a challenge.
 * Parameters: challenge - ptr to challenge, 
 *                         visits - ptr to number as return value.
 * Returns: NULL_PARAMETER - in case challenge equal NULL.
 *          OK - in case of success.
 *          *visits - number of visits of the challenge.
 */
Result num_visits(Challenge *challenge, int *visits) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    *visits = challenge->num_visits;
    return OK;
}

