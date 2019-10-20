#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "visitor_room.h"

/* IMPLEMENT HERE ALL WHAT IS NEEDED */

/* The init_challenge_activity function
 * Purpose: initialize the challenge activity object.
 * Parameters: activity - ptr to activity,
 *                         challenge - ptr to challenge of this activity.
 * Returns: NULL_PARAMETER - in case activity or challenge equal NULL.
 *          OK - in case of success.
 */
Result init_challenge_activity(ChallengeActivity *activity,
                               Challenge *challenge){
    if (activity == NULL || challenge == NULL) {
        return NULL_PARAMETER;
    }
    activity->challenge = challenge;
    activity->visitor = NULL;
    activity->start_time = 0;
    return OK;
}

/* The reset_challenge_activity function
 * Purpose: reset the challenge activity object.
 * Parameters: activity - ptr to activity.
 * Returns: NULL_PARAMETER - in case activity or challenge equal NULL.
 *          OK - in case of success.
 */
Result reset_challenge_activity(ChallengeActivity *activity){
    if (activity == NULL) {
        return NULL_PARAMETER;
    }
    activity->challenge = NULL;
    activity->visitor = NULL;
    activity->start_time = 0;
    return OK;
}

/* The init_visitor function
 * Purpose: initialize the visitor object.
 * Parameters: visitor - ptr to visitor, name - ptr to visitor name,
 *             id - id of visitor.
 * Returns: NULL_PARAMETER - in case visitor or name equal NULL.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result init_visitor(Visitor *visitor, char *name, int id){
    if (visitor == NULL || name == NULL) {
        return NULL_PARAMETER;
    }
    int name_len = (int)strlen(name)+1;
    visitor->visitor_name = (char*)malloc(name_len* sizeof(char));
    if (visitor->visitor_name == NULL) {
        return  MEMORY_PROBLEM;
    }
    memcpy(visitor->visitor_name, name, name_len);
    visitor->visitor_id = id;
    visitor->room_name = NULL;
    visitor->current_challenge = NULL;
    return OK;
}

/* The reset_visitor function
 * Purpose: reset the visitor object.
 * Parameters: visitor - ptr to visitor.
 * Returns: NULL_PARAMETER - in case visitor equal NULL.
 *          OK - in case of success.
 */
Result reset_visitor(Visitor *visitor){
    if (visitor == NULL) {
        return NULL_PARAMETER;
    }
    free(visitor->visitor_name);
    visitor->visitor_name = NULL;
    visitor->visitor_id = 0;
    visitor->room_name = NULL;
    visitor->room_name = NULL;
    return OK;
}

/* The init_room function
 * Purpose: initialize the room object.
 * Parameters: room - ptr to room, name - ptr to room name,
 *             num_challenges - number of challenges for a room.
 * Returns: NULL_PARAMETER - in case room or name equal NULL.
 *          ILLEGAL_PARAMETER - in case num_challenges less than 1.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result init_room(ChallengeRoom *room, char *name, int num_challenges){
    if (room == NULL || name == NULL) {
        return NULL_PARAMETER;
    } else if (num_challenges < 1) {
        return ILLEGAL_PARAMETER;
    }
    room->name = NULL;
    Result return_flag = change_room_name(room, name);
    if (return_flag != OK) {
        return  return_flag;
    }
    room->num_of_challenges = num_challenges;
    room->challenges = malloc(num_challenges*sizeof(ChallengeActivity));
    if (room->challenges == NULL) {
        free(room->name);
        return MEMORY_PROBLEM;
    }
    for (int i=0; i < num_challenges; i++) {
        Result return_flag = reset_challenge_activity(&room->challenges[i]);
        if (return_flag != OK) {
            free(room->name);
            free (room->challenges);
            return return_flag;
        }
    }
    return OK;
}

/* The reset_room function
 * Purpose: reset the room object.
 * Parameters: room - ptr to room.
 * Returns: NULL_PARAMETER - in case room equal NULL.
 *          OK - in case of success.
 */
Result reset_room(ChallengeRoom *room){
    if (room == NULL) {
        return NULL_PARAMETER;
    }
    free(room->name);
    room->name = NULL;
    for (int i=0; i < room->num_of_challenges; i++) {
        Result return_flag = reset_challenge_activity(&room->challenges[i]);
        if (return_flag != OK) {
            return return_flag;
        }
    }
    free(room->challenges);
    room->challenges = NULL;
    room->num_of_challenges = 0;
    return OK;
}

/* The num_of_free_places_for_level function
 * Purpose: getting the number of free places in the room object.
 * Parameters: room - ptr to room, lavel - type of activities level,
 *             places - ptr to number of places.
 * Returns: NULL_PARAMETER - in case room or places equal NULL.
 *          OK - in case of success.
 */
Result num_of_free_places_for_level(ChallengeRoom *room,
                                    Level level, int *places){
    if (room == NULL || places == NULL) {
        return NULL_PARAMETER;
    }
    *places = 0;
    for (int i=0; i < room->num_of_challenges; i++) {
        if (room->challenges[i].challenge != NULL &&
            room->challenges[i].visitor == NULL &&
            room->challenges[i].start_time == 0) {
            if (room->challenges[i].challenge->level == level||
                level == All_Levels){
                (*places)++;
            }
        }
    }
    return OK;
}

/* The change_room_name function
 * Purpose: changing the room name object.
 * Parameters: room - ptr to room, new_name - ptr to new room name.
 * Returns: NULL_PARAMETER - in case room or new_name equal NULL.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result change_room_name(ChallengeRoom *room, char *new_name){
    if (room == NULL || new_name == NULL) {
        return NULL_PARAMETER;
    }
    int name_len = (int)strlen(new_name)+1;
    char* tmp_ptr = realloc(room->name, name_len*sizeof(char));
    if (tmp_ptr == NULL) {
        return MEMORY_PROBLEM;
    }
    room->name = tmp_ptr;
    memcpy(room->name, new_name, name_len);
    return  OK;
}

/* The room_of_visitor function
 * Purpose: getting the name of the room where the visitor is.
 * Parameters: room - ptr to room, new_name - ptr to new room name.
 * Returns: NULL_PARAMETER - in case room or new_name equal NULL.
 *          NOT_IN_ROOM - in case that a visitor isn't inside room.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result room_of_visitor(Visitor *visitor, char **room_name){
    if (visitor == NULL || room_name == NULL) {
        return NULL_PARAMETER;
    }
    if (visitor->room_name == NULL) {
        return NOT_IN_ROOM;
    }
    int name_len = (int)strlen(*(visitor->room_name))+1;
    char *tmp_ptr = (char*)malloc(name_len*sizeof(char));
    if (tmp_ptr == NULL) {
        return MEMORY_PROBLEM;
    }
    memcpy(tmp_ptr, *visitor->room_name, name_len);
    *room_name = tmp_ptr;
    return OK;
}

/* The visitor_enter_room function
 * Purpose: connecting visitor to a room with the needed changes.
 * Parameters: room - ptr to room, visitor - ptr to visitor, 
 *             level - level that the visitor want, start_time - entering time.
 * Returns: NULL_PARAMETER - in case room or new_name equal NULL.
 *          ALREADY_IN_ROOM - in case that visitor already in room.
 *          OK - in case of success.
 */
Result visitor_enter_room(ChallengeRoom *room, Visitor *visitor, Level level,
                          int start_time){
    if (room == NULL || visitor == NULL) return NULL_PARAMETER;
    if (visitor->room_name != NULL) return ALREADY_IN_ROOM;
        
    int best_match = -1;
    for (int i=0; i<room->num_of_challenges; i++) {
        if (room->challenges[i].visitor == NULL &&
            room->challenges[i].challenge != NULL &&
                (room->challenges[i].challenge->level == level ||
                 level == All_Levels)) {
            if (best_match == -1) {
                best_match = i;
            } else if (strcmp(room->challenges[i].challenge->name,
                              room->challenges[best_match].challenge->name)<0) {
                best_match = i;
            }
        }
    }
    if (best_match != -1) {
        visitor->room_name = &room->name;
        visitor->current_challenge = &room->challenges[best_match];
        room->challenges[best_match].visitor = visitor;
        room->challenges[best_match].start_time = start_time;
        inc_num_visits(visitor->current_challenge->challenge);
        return OK;
    }
    return  NO_AVAILABLE_CHALLENGES;
}

/* The visitor_quit_room function
 * Purpose: quiting visitor from a room with the needed changes.
 * Parameters: visitor - ptr to visitor, quit_time - exiting time.
 * Returns: NULL_PARAMETER - in case visitor equal NULL.
 *          NOT_IN_ROOM - in case visitor isn't inside some room.
 *          OK - in case of success.
 */
Result visitor_quit_room(Visitor *visitor, int quit_time){
    if (visitor == NULL) {
        return NULL_PARAMETER;
    } else if (visitor->room_name == NULL) {
        return NOT_IN_ROOM;
    }
    int time = quit_time - visitor->current_challenge->start_time;
    set_best_time_of_challenge(visitor->current_challenge->challenge, time);
    visitor->current_challenge->visitor = NULL;
    visitor->current_challenge->start_time = 0;
    visitor->room_name = NULL;
    visitor->current_challenge = NULL;
    return OK;
}

