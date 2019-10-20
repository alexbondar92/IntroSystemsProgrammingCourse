#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>


#include "challenge_system.h"

/* IMPLEMENT HERE ALL WHAT IS NEEDED */

#define BUFFER_SIZE 51

/* typedef for SVisitorsList struct from challenge_system.h file */
typedef struct SVisitorsList VisitorsList;


/* The creating_system_name function
 * Purpose: creating system name.
 * Parameters: sys - ptr(**) to sys object, sys_file - FILE of system data file.
 * Returns: MEMORY_PROBLEM - in case the allocation failed,
 *          OK - in case of success.
 */
static Result creating_system_name(ChallengeRoomSystem **sys, FILE* sys_file);

/* The create_system_challenges function
 * Purpose: creating array of challenges and inserting the relevent data
 *          to the system.
 * Parameters: sys - ptr(**) to sys object, sys_file - FILE of system data file.
 * Returns: MEMORY_PROBLEM - in case the allocation failed,
 *          OK - in case of success.
 */
static Result create_system_challenges(ChallengeRoomSystem **sys,
                                FILE* sys_file);

/* The create_system_rooms function
 * Purpose: creating array of rooms and inserting the relevent data
 *          to the system.
 * Parameters: sys - ptr(**) to sys object, sys_file - FILE of system data file.
 * Returns: MEMORY_PROBLEM - in case the allocation failed,
 *          OK - in case of success.
 */
static Result create_system_rooms(ChallengeRoomSystem** sys, FILE* sys_file);

/* The create_visitors_list function
 * Purpose: creating new node of visitors_list, with relevent visitor.
 * Parameters: new_node - ptr(**) to new node object, 
 *             visitor_name - name of visitor, visitor_id - id number.
 * Returns: MEMORY_PROBLEM - in case the allocation failed,
 *          OK - in case of success.
 */
static Result create_visitors_list(VisitorsList **new_node,
                                char *visitor_name, int visitor_id);

/* The destroy_system_rec function
 * Purpose: helping func for the destroying func, 
 *          destroying rooms and challenges arrays.
 * Parameters: sys - ptr to system object.
 * Returns: OK - in case of success.
 */
static Result destroy_system_rec(ChallengeRoomSystem *sys);

/* The destroy_visitors_list function
 * Purpose: destroing all the list to visitors from the system.
 * Parameters: visitors_list - ptr to visitors_list object.
 * Returns: OK - in case of success.
 */
static Result destroy_visitors_list(VisitorsList *visitors_list);

/* The visitor_arrive_checkinges function
 * Purpose: check that arrival of new visitor is ok.
 * Parameters: sys - ptr to system object,
 *             room_name - ptr of name of room to enter,
 *             visitor_name - ptr of visitor's name, visitor_id - visitor's id,
 *             start_time - time at entering.
 * Returns: ILLEGAL_TIME - in case time is illegal,
 *          NULL_PARAMETER - in case sys point to null,
 *          ILLEGAL_PARAMETER - in case room_name or visitor_name equal null,
 *          ALREADY_IN_ROOM - in case that there is already this visitor in sys,
 *          OK - in case of success.
 */
static Result visitor_arrive_checkinges(ChallengeRoomSystem *sys,
                            char *room_name, char *visitor_name, int visitor_id,
                                        int start_time);

/* The check_visitor_in_system function
 * Purpose: check if there is visitor with that id.
 * Parameters: sys - ptr to system object, id - id number of visitor.
 * Returns: ALREADY_IN_ROOM - in case there is visitor this this id in sys,
 *          OK - in case of success.
 */
static Result check_visitor_in_system(ChallengeRoomSystem *sys, int id);

/* The insert_visitor_to_list function
 * Purpose: inserting relevent visitor to the list.
 * Parameters: sys - ptr to system object,
 *             entering_visitor - ptr of entering visitor.
 * Returns: OK - in case of success.
 */
static Result insert_visitor_to_list(ChallengeRoomSystem *sys,
                                VisitorsList *entering_visitor);

/* The clear_visitor_from_list function
 * Purpose: clearing relevent visitor from the list.
 * Parameters: previous_visitor_ptr - ptr to privious visitor in list object,
 *             poping_visitor - ptr of the visitor that needed to clear out.
 * Returns: OK - in case of success.
 */
static Result clear_visitor_from_list(VisitorsList *previous_visitor_ptr,
                                VisitorsList *poping_visitor);

/* The best_time_of_all_challenges function
 * Purpose: getting the best time from all the system challenges.
 * Parameters: sys - ptr to system object, 
 *             challenge_best_time - ptr(**) to relevent challenge.
 * Returns: MEMORY_PROBLEM - in case the allocation failed,
 *          OK - in case of success.
 */
static Result best_time_of_all_challenges(ChallengeRoomSystem *sys,
                                char** challenge_best_time);

/* The find_challenge function
 * Purpose: finding the relevent challenge object by id.
 * Parameters: sys - ptr to system object, id - id number,
 *             challenge - ptr(**) to relevent challenge.
 * Returns: NO_AVAILABLE_CHALLENGES - in case there isn't challenge with this id
 *          OK - in case of success.
 */
static Result find_challenge(ChallengeRoomSystem* sys, int id,
                                Challenge** challenge);

/* The create_str_copy function
 * Purpose: creating copy of string.
 * Parameters: source - ptr to source string, dest - ptr(**) to copy of string.
 * Returns: MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
static Result create_str_copy(char* source, char** dest);

/* ===========================================================================*/


/* The create_system function
 * Purpose: creating system object and initialize the room system from 
 *          the system init_file.
 * Parameters: init_file - ptr to name(or path) of init file, sys - ptr(**) to sys.
 * Returns: NULL_PARAMETER - in case sys or init_file equal NULL.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result create_system(char *init_file, ChallengeRoomSystem **sys) {
    if (sys == NULL || init_file == NULL) {
        return NULL_PARAMETER;
    }
    *sys = malloc(sizeof(ChallengeRoomSystem));
    (*sys)->last_system_update = 0;
    FILE* sys_file = fopen(init_file, "r");
    if (sys_file == NULL || *sys == NULL) {
        return MEMORY_PROBLEM;
    }
    (*sys)->visitor_list.visitor.visitor_name = NULL;
    (*sys)->visitor_list.next_visitor = NULL;
    Result flag = creating_system_name(sys, sys_file);
    if (flag != OK) {
        free(*sys);
        fclose(sys_file);
        return flag;
    }
    char* null_ptr = NULL;
    flag = create_system_challenges(sys, sys_file);
    if (flag != OK) {
        destroy_system(*sys, 1, &null_ptr, &null_ptr);
        free(null_ptr);
        fclose(sys_file);
        return flag;
    }
    flag = create_system_rooms(sys, sys_file);
    if (flag != OK) {
        destroy_system(*sys, 1, &null_ptr, &null_ptr);
        free(null_ptr);
        fclose(sys_file);
        return flag;
    }
    fclose(sys_file);
    return OK;
}


Result destroy_system(ChallengeRoomSystem *sys, int destroy_time,
                char **most_popular_challenge_p, char **challenge_best_time){
    if (sys == NULL || most_popular_challenge_p == NULL ||
        challenge_best_time == NULL) {
        return NULL_PARAMETER;
    } else if (destroy_time < sys->last_system_update) {
        return ILLEGAL_TIME;
    }
    sys->last_system_update = destroy_time;
    Result flag = all_visitors_quit(sys, destroy_time);
    if (flag != OK) {
        return flag;
    }
    flag = most_popular_challenge(sys, most_popular_challenge_p);
    if (flag != OK) {
        return flag;
    }
    flag = best_time_of_all_challenges(sys, challenge_best_time);
    if (flag != OK) {
        return flag;
    }
    return destroy_system_rec(sys);
}

/* The visitor_arrive function
 * Purpose: when a new visitor arriving, finding him a relevent room with the needed  object and returning the relevent
 *          stats(most popular challenge and best challenge time).
 * Parameters: sys - ptr to sys, destroy_time - time of destroying.
 *             most_popular_challenge_p - ptr to most popular challenge,
 *             challenge_best_time - ptr to best challenge time.
 * Returns: NULL_PARAMETER - in case sys or most_popular_challenge_p
 *                              or challenge_best_time equal NULL.
 *          ILLEGAL_TIME - in case that the destroy time is illigeal.
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result visitor_arrive(ChallengeRoomSystem *sys, char *room_name,
            char *visitor_name, int visitor_id, Level level, int start_time){
    Result flag = visitor_arrive_checkinges(sys, room_name, visitor_name,
                                            visitor_id, start_time);
    if (flag != OK) {
        return flag;
    }
    VisitorsList *tmp_ptr = NULL;
    flag = create_visitors_list(&tmp_ptr, visitor_name, visitor_id);
    if (flag != OK) return flag;
    for (int i=0; i < sys->num_of_rooms; i++) {
        if (strcmp(sys->rooms[i].name, room_name) == 0) {
            flag = visitor_enter_room(&sys->rooms[i],&(tmp_ptr->visitor)
                                      , level, start_time);
            if (flag == OK) {
                insert_visitor_to_list(sys, tmp_ptr);
                sys->last_system_update = start_time;
                return flag;
            }
            destroy_visitors_list(tmp_ptr);
            return flag;
        }
    }
    destroy_visitors_list(tmp_ptr);
    return ILLEGAL_PARAMETER;
}

/* The visitor_quit function
 * Purpose: quiting visitor from the room system with the relevent changes.
 * Parameters: sys - ptr to sys, visitor_id - id of the exiting visitor,
 *                   quit_time - time of quiting.
 * Returns: NULL_PARAMETER - in case sys equal NULL.
 *          ILLEGAL_TIME - in case that the quit time is illigeal.
 *          NOT_IN_ROOM - in case that there ins't any visitor with this id.
 *          OK - in case of success.
 */
Result visitor_quit(ChallengeRoomSystem *sys, int visitor_id, int quit_time){
    if (sys == NULL) {
        return NULL_PARAMETER;
    } else if (quit_time < sys->last_system_update) {
        return ILLEGAL_TIME;
    }
    VisitorsList *previous_visitor_ptr = &(sys->visitor_list);
    VisitorsList *visitor_ptr = sys->visitor_list.next_visitor;
    while (visitor_ptr != NULL) {
        if (visitor_ptr->visitor.visitor_id == visitor_id) {
            Result flag = visitor_quit_room(&(visitor_ptr)->visitor,
                                            quit_time);
            clear_visitor_from_list(previous_visitor_ptr, visitor_ptr);
            sys->last_system_update = quit_time;
            return flag;
        }
        previous_visitor_ptr = visitor_ptr;
        visitor_ptr = visitor_ptr->next_visitor;
    }
    return NOT_IN_ROOM;
}

/* The all_visitors_quit function
 * Purpose: quiting all visitors from the system with the relevent changes.
 * Parameters: sys - ptr to sys, quit_time - time of quiting.
 * Returns: NULL_PARAMETER - in case sys equal NULL.
 *          ILLEGAL_TIME - in case that the quit time is illigeal.
 *          OK - in case of success.
 */
Result all_visitors_quit(ChallengeRoomSystem *sys, int quit_time) {
    if (sys == NULL) {
        return NULL_PARAMETER;
    }
    if (quit_time < sys->last_system_update) {
        return ILLEGAL_TIME;
    }
    VisitorsList *visitor_ptr = sys->visitor_list.next_visitor;
    while (visitor_ptr != NULL) {
        visitor_quit_room(&(visitor_ptr)->visitor, quit_time);
        VisitorsList *tmp_ptr = visitor_ptr->next_visitor;
        clear_visitor_from_list(&(sys->visitor_list), visitor_ptr);
        visitor_ptr = tmp_ptr;
        
    }
    sys->last_system_update = quit_time;
    return OK;
}

/* The system_room_of_visitor function
 * Purpose: finding in what room the visitor is.
 * Parameters: sys - ptr to sys, visitor_name - ptr to name of visitor,
 *             room_name - ptr(**) to name of room.
 * Returns: NULL_PARAMETER - in case sys equal NULL.
 *          ILLEGAL_PARAMETER - in case room_name or visitor_name equal NULL.
 *          NOT_IN_ROOM - in case that there isn't any visitor with this name.
 *          OK - in case of success.
 */
Result system_room_of_visitor(ChallengeRoomSystem *sys, char *visitor_name,
                              char **room_name){
    if (sys == NULL) {
        return NULL_PARAMETER;
    } else if (visitor_name == NULL || room_name == NULL) {
        return ILLEGAL_PARAMETER;
    }
    VisitorsList *visitor_ptr = sys->visitor_list.next_visitor;
    while (visitor_ptr != NULL) {
        if (strcmp(visitor_ptr->visitor.visitor_name, visitor_name) == 0) {
            return create_str_copy(*(visitor_ptr->visitor.room_name),
                                   room_name);
        }
        visitor_ptr = visitor_ptr->next_visitor;
    }
    return NOT_IN_ROOM;
}

/* The change_challenge_name function
 * Purpose: changing name of a challenge name.
 * Parameters: sys - ptr to sys, challenge_id - id number of challenge, 
 *             new_name - ptr(**) to new challenge name.
 * Returns: NULL_PARAMETER - in case sys or new_name equal NULL.
 *          ILLEGAL_PARAMETER - in case that there isn't any challenge with id.
 *          OK - in case of success.
 */
Result change_challenge_name(ChallengeRoomSystem *sys, int challenge_id,
                             char *new_name){
    if (sys == NULL || new_name == NULL) {
        return NULL_PARAMETER;
    }
    for (int i=0; i < sys->num_of_challenges; i++) {
        if (challenge_id == sys->system_challenges[i].id) {
            return change_name(&sys->system_challenges[i], new_name);
        }
    }
    return ILLEGAL_PARAMETER;
}

/* The change_system_room_name function
 * Purpose: changing name of a room name.
 * Parameters: sys - ptr to sys, current_name - ptr to current name of a room,
 *                   new_name - ptr to new room name.
 * Returns: NULL_PARAMETER - in case sys or new_name equal NULL.
 *          ILLEGAL_PARAMETER - in case that there isn't any challenge with id.
 *          OK - in case of success.
 */
Result change_system_room_name(ChallengeRoomSystem *sys, char *current_name,
                               char *new_name){
    if (sys == NULL || current_name == NULL || new_name == NULL) {
        return NULL_PARAMETER;
    }
    for (int i=0; i < sys->num_of_rooms; i++) {
        if (strcmp(current_name,sys->rooms[i].name) == 0) {
            return change_room_name(&sys->rooms[i], new_name);
        }
    }
    return ILLEGAL_PARAMETER;
}

/* The best_time_of_system_challenge function
 * Purpose: getting the best challenge time in a challenge.
 * Parameters: sys - ptr to sys, challenge_name - ptr to name of challenge,
 *                   time - ptr to best challenge time.
 * Returns: NULL_PARAMETER - in case sys or challenge_name or time equal NULL.
 *          ILLEGAL_PARAMETER - in case that there isn't any challenge with name
 *          OK - in case of success.
 */
Result best_time_of_system_challenge(ChallengeRoomSystem *sys,
                                     char *challenge_name, int *time) {
    if (sys == NULL || challenge_name == NULL || time == NULL) {
        return NULL_PARAMETER;
    }
    for (int i = 0; i < sys->num_of_challenges; i++) {
        if (strcmp(sys->system_challenges[i].name, challenge_name) == 0) {
            return best_time_of_challenge(&(sys->system_challenges[i]), time);
        }
    }
    return ILLEGAL_PARAMETER;
}

/* The most_popular_challenge function
 * Purpose: getting the most popular challenge in the system.
 * Parameters: sys - ptr to sys, challenge_name - ptr(**) to name of challenge.
 * Returns: NULL_PARAMETER - in case sys or challenge_name equal NULL.
 *          ILLEGAL_PARAMETER - in case that there isn't any challenge with name
 *          MEMORY_PROBLEM - in case the allocation failed.
 *          OK - in case of success.
 */
Result most_popular_challenge(ChallengeRoomSystem *sys, char **challenge_name) {
    if (sys == NULL || challenge_name == NULL) {
        return NULL_PARAMETER;
    }
    *challenge_name = NULL;
    if (sys->num_of_challenges == 0) {
        return OK;
    }
    int max_num_of_visits = sys->system_challenges[0].num_visits;
    int popular_room = 0;
    for (int i = 1; i < sys->num_of_challenges; i++) {
        if (sys->system_challenges[i].num_visits > max_num_of_visits) {
            popular_room = i;
            max_num_of_visits = sys->system_challenges[i].num_visits;
        } else if (sys->system_challenges[i].num_visits == max_num_of_visits &&
                    strcmp(sys->system_challenges[i].name,
                           sys->system_challenges[popular_room].name) < 0) {
            popular_room = i;
            max_num_of_visits = sys->system_challenges[i].num_visits;
        }
    }
    if (popular_room != -1 && max_num_of_visits != 0) {
        return create_str_copy(sys->system_challenges[popular_room].name,
                               challenge_name);
    }
    return OK;
}


static Result creating_system_name(ChallengeRoomSystem **sys, FILE* sys_file){
    assert(sys != NULL && sys_file != NULL);
    char tmp_str[BUFFER_SIZE];
    fscanf(sys_file, "%s", tmp_str);
    return create_str_copy(tmp_str, &((*sys)->name));
}


static Result create_system_challenges(ChallengeRoomSystem **sys,
                                       FILE* sys_file){
    assert(sys_file != NULL && sys != NULL);
    int num_of_challenges;
    fscanf(sys_file, "%d", &num_of_challenges);
    (*sys)->num_of_challenges = num_of_challenges;
    (*sys)->system_challenges = malloc(num_of_challenges*sizeof(Challenge));
    if ((*sys)->system_challenges == NULL) {
        return MEMORY_PROBLEM;
    }
    for (int i=0; i < (*sys)->num_of_challenges; i++) {
        char name[BUFFER_SIZE];
        int id;
        int level;
        fscanf(sys_file, "%s %d %d", name, &id, &level);
        Result flag = init_challenge(&(*sys)->system_challenges[i], id, name,
                                     (Level)(level-1));
        if (flag != OK) {
            return flag;
        }
    }
    return OK;
}


static Result create_system_rooms(ChallengeRoomSystem** sys, FILE* sys_file){
    assert(sys != NULL && sys_file != NULL);
    fscanf(sys_file, "%d", &(*sys)->num_of_rooms);
    (*sys)->rooms = malloc((*sys)->num_of_rooms*sizeof(ChallengeRoom));
    if ((*sys)->rooms == NULL) {
        return MEMORY_PROBLEM;
    }
    for (int i=0; i < (*sys)->num_of_rooms; i++) {
        char name[BUFFER_SIZE];
        int num_of_activities;
        fscanf(sys_file, "%s %d", name, &num_of_activities);
        Result flag = init_room(&(*sys)->rooms[i], name, num_of_activities);
        if (flag != OK) {
            (*sys)->num_of_rooms = i;
            return flag;
        }
        for (int j=0; j < num_of_activities; j++) {
            int tmp_id;
            fscanf(sys_file, "%d", &tmp_id);
            Challenge* tmp_ptr;
            find_challenge(*sys, tmp_id, &tmp_ptr);
            init_challenge_activity(&((*sys)->rooms[i].challenges[j]), tmp_ptr);
        }
    }
    return OK;
}


static Result destroy_system_rec(ChallengeRoomSystem *sys){
    Result flag = OK;
    for (int i=0; i < sys->num_of_challenges; i++) {
        flag = reset_challenge(&(sys->system_challenges[i]));
        if (flag != OK) {
            return flag;
        }
    }
    free(sys->system_challenges);
    sys->system_challenges = NULL;
    for (int i=0; i < sys->num_of_rooms; i++) {
        flag = reset_room(&(sys->rooms[i]));
        if (flag != OK) {
            return flag;
        }
    }
    free(sys->rooms);
    sys->rooms = NULL;
    free(sys->name);
    sys->rooms = NULL;
    free(sys);
    return OK;
}


static Result visitor_arrive_checkinges(ChallengeRoomSystem *sys,
                                        char *room_name, char *visitor_name, int visitor_id,
                                        int start_time){
    if (sys != NULL && start_time < sys->last_system_update){
        return ILLEGAL_TIME;
    } else if (sys == NULL) {
        return NULL_PARAMETER;
    } else if (visitor_name == NULL || room_name == NULL) {
        return ILLEGAL_PARAMETER;
    }
    if (check_visitor_in_system(sys, visitor_id) == ALREADY_IN_ROOM) {
        return ALREADY_IN_ROOM;
    }
    return OK;
}


static Result check_visitor_in_system(ChallengeRoomSystem *sys, int id){
    assert(sys != NULL);
    //  VisitorsList *previous_visitor_ptr = &(sys->visitor_list);
    VisitorsList *visitor_ptr = sys->visitor_list.next_visitor;
    while (visitor_ptr != NULL) {
        if (visitor_ptr->visitor.visitor_id == id) {
            return ALREADY_IN_ROOM;
        }
        //previous_visitor_ptr = visitor_ptr;
        visitor_ptr = visitor_ptr->next_visitor;
    }
    return OK;
}


static Result create_visitors_list(VisitorsList **new_node, char *visitor_name,
                                   int visitor_id){
    *new_node = malloc(sizeof(VisitorsList));
    if (new_node == NULL) {
        return MEMORY_PROBLEM;
    }
    Result flag=init_visitor(&((*new_node)->visitor), visitor_name, visitor_id);
    if (flag != OK) {
        free(*new_node);
        return flag;
    }
    return OK;
}


static Result destroy_visitors_list(VisitorsList *visitors_list) {
    assert(visitors_list != NULL);
    Result flag = reset_visitor(&(visitors_list->visitor));
    if (flag != OK) {
        return flag;
    }
    free(visitors_list);
    return OK;
}


static Result insert_visitor_to_list(ChallengeRoomSystem *sys,
                                     VisitorsList *entering_visitor){
    assert(sys != NULL && entering_visitor != NULL);
    VisitorsList* tmp_ptr = sys->visitor_list.next_visitor;
    sys->visitor_list.next_visitor = entering_visitor;
    entering_visitor->next_visitor = tmp_ptr;
    return OK;
}


static Result clear_visitor_from_list(VisitorsList *previous_visitor_ptr,
                                      VisitorsList *poping_visitor){
    assert(previous_visitor_ptr != NULL && poping_visitor != NULL);
    (previous_visitor_ptr)->next_visitor = (poping_visitor)->next_visitor;
    reset_visitor(&(poping_visitor->visitor));
    free(poping_visitor);
    return OK;
}


static Result best_time_of_all_challenges(ChallengeRoomSystem *sys,
                                          char** challenge_best_time){
    *challenge_best_time = NULL;
    Result flag = OK;
    int best_time = -1;
    for (int i=0; i < sys->num_of_challenges; i++) {
        int tmp_best_time;
        flag = best_time_of_system_challenge(sys,sys->system_challenges[i].name,
                                             &tmp_best_time);
        if (flag != OK) {
            return flag;
        } else if (best_time == -1 && tmp_best_time != 0) {
            best_time = i;
        } else if (tmp_best_time != 0 &&
                   tmp_best_time < sys->system_challenges[best_time].best_time) {
            best_time = i;
        } else if (tmp_best_time != 0 &&
                   tmp_best_time == sys->system_challenges[best_time].best_time) {
            if (strcmp(sys->system_challenges[i].name,
                       sys->system_challenges[best_time].name) < 0) {
                best_time = i;
            }
        }
    }
    if (best_time != -1) {
        return create_str_copy(sys->system_challenges[best_time].name,
                               challenge_best_time);
    }
    return OK;
}


static Result find_challenge(ChallengeRoomSystem* sys, int id,
                             Challenge** challenge) {
    assert(sys != NULL && challenge != NULL);
    for (int i=0; i < sys->num_of_challenges; i++) {
        if (sys->system_challenges[i].id == id) {
            *challenge = &(sys->system_challenges[i]);
            return OK;
        }
    }
    return NO_AVAILABLE_CHALLENGES;
}


static Result create_str_copy(char* src, char** dest) {
    assert(src != NULL && dest != NULL);
    int src_len = (int)strlen(src)+1;
    *dest = malloc(src_len*sizeof(char));
    if (*dest == NULL) {
        return MEMORY_PROBLEM;
    }
    memcpy(*dest, src, src_len);
    return OK;
}
