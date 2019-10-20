#include <stdbool.h>

#ifndef ESCAPEROOM_H
#define ESCAPEROOM_H


typedef struct escaperoom_t* EscapeRoom;

typedef enum{
    ESCAPEROOM_SUCCESS , ESCAPEROOM_NULL_ARG , ESCAPEROOM_BAD_PARAM
}RoomResult;

#ifdef __cplusplus
extern "C" {
#endif
//Creates a new EscapeRoom Object with the details given as params,
//Also, assigning 0 as votes number and 0 as avg rate.
//
//@param: name - the name of the escape room.
//@param: maxTime - the maximum time to escape - integer between 30 and 90.
//@param: maxParticipants - maximum number of participants - integer bigger than 1.
//@param: level - the level of the escape room  - integer between 1 and 10.
//@return: the room created. if encountered problems, NULL is returned.
EscapeRoom escapeRoomCreate(char *name, int maxTime, int maxParticipants, int level);

//Copy function for Escape room.
//
//@param: room - the room to be copied.
//@return: the new copy of the room. if encountered problems, NULL is returned.
EscapeRoom escapeRoomCopy(EscapeRoom room);

//Functions Checks if rooms are equal by this conditions:
//Two rooms will be equal if their power is equal.
//power(room) = (level*maxTime)/maxParticipants.
//
//@param: room1 - the first room to be compared.
//@param: room2 - the second room to be compared.
//@return: true if rooms are equal, false if not.
//Note: if one of the params is NULL, false will be returned.
bool areEqualRooms(EscapeRoom room1, EscapeRoom room2);

//Functions Checks if if first room is bigger than the second one.
//A room is bigger than another if it's power is bigger the other's.
//power(room) = (level*maxTime)/maxParticipants.
//
//@param: room1 - the first room to be compared.
//@param: room2 - the second room to be compared.
//@return: true if first room is bigger than second, false if not.
//Note: if one of the params is NULL, false will be returned.
bool isBiggerRoom(EscapeRoom room1, EscapeRoom room2);

//Function returns the level of the room given as parameter.
//
//@param: room - the room from which level is wanted.
//@return: return the level of the specified room. -1 is returned if room is NULL;
int getLevel(EscapeRoom room);

//Functions updates the rate of the room and number of voters.
//Rate must be an integer between 1 and 5.
//
//@param: room - the room to be updated.
//@param: newRate - the new rate to be added to the room.
//@return:
//  ESCAPEROOM_SUCCESS - in case the function succeeds.
//  ESCAPEROOM_NULL_ARG - if room is NULL.
//  ESCAPEROOM_BAD_PARAM - if newRate is out of range.
RoomResult updateRate(EscapeRoom room, int newRate);

//Function returns a copy of the name of the specified room.
//
//@param: room - the room from which name is wanted.
//@return: the name of the room specified.
//         a copy is returned, you must free it in the end of use.
//         function returns NULL if room is NULL or if malloc failed.
char *roomGetName(EscapeRoom room);

//Function returns the maximum time of the specified room.
//
//@param: room - the room from which max time is wanted.
//@return: the max time of the room specified. -1 if room is NULL.
int roomGetMaxTime(EscapeRoom room);

//Function returns the maximum participants of the specified room.
//
//@param: room - the room from which max participants is wanted.
//@return: the max participants of the room specified. -1 if room is NULL.
int roomGetMaxParticipants(EscapeRoom room);

//Function Destroys the room specified, freeing all memory allocated.
//
//@param: room - the room to be destroyed.
//Note: Nothing happens if room is NULL.
void escapeRoomDestroy(EscapeRoom room);

//Function returns the average rate of the specified room.
//
//@param: room - the room from which rate is wanted.
//@return: the rate of the room specified. -1 if room is NULL.
double roomGetRate(EscapeRoom room);

#ifdef __cplusplus
}
#endif


#endif //ESCAPEROOM_H
