#ifndef ROOM_H_
#define ROOM_H_


#include <stdbool.h>
#include "escape_utilitis.h"
#include "mtm_ex3.h"


/**
 * Room Container
 *
 * Implements a room container type.
 *
 * The following functions are available:
 *
 *   roomCreate                 - Creates a new room
 *   roomDestroy                - Deletes an existing room and frees all
 *                                resources
 *   roomGetId                  - Returns the ID of the room
 *   roomGetPrice               - Returns the price of the room
 *   roomGetNumOfPeople         - Returns the num of people of the room
 *   roomGetOpenTime            - Returns the opening time of the room
 *   roomGetCloseTime           - Returns the closing time of the room
 *   roomGetDifficulty          - Returns the difficulty of the room
 *   roomGetNumberOfOrders      - Returns the number of orders
 *   roomIncNumberOfOrders      - Increase the number of orders by one
 *   roomDecNumberOfOrders      - Decrease the number of orders by one
 *   roomCopy                   - Returns a Copy of room
 *   roomCompare                - Comparing between two room(id compare)
 */

/** Type for defining the room */
typedef struct Room_t *Room;


/**
 * This type defines all errors for the Room ADT.
 */
typedef enum {
    ROOM_OUT_OF_MEMORY, // You should exit program after this error
    ROOM_NULL_PARAMETER,
    ROOM_INVALID_PARAMETER,
    ROOM_SUCCESS
} RoomErrorCode;

/**
 * This function create the room
 * @param room_id the id number of the new room
 * @param price the cost per person for ordering this room
 * @param num_ppl the recomended number of people at this room
 * @param working_hrs the working hours of this room("xx-yy" xx- open time, 
 * yy- close time)
 * @param difficulty the difficulty level of this room
 * @param error the error returning parameter code
 * @return
 * ROOM_INVALID_PARAMETER in case of invaild one or more of parameters
 * ROOM_NULL_PARAMETER if working_hrs is ptr to NULL
 * ROOM_OUT_OF_MEMORY in case of allocation fail
 * ROOM_SUCCESS in case of success, returns new room object
 */
Room roomCreate(int room_id,int price, int num_ppl, char* working_hrs,
                int difficulty, RoomErrorCode* error);

/**
 * This function destroys the room
 * @param room Target to be deallocated. If room is NULL nothing will be done
 */
void roomDestroy(Room room);

/**
 * This function get the id of the room
 * @param room the current room object to get from(its assume that room not null
 * @return
 * the id of the room
 */
int roomGetId(Room room);

/**
 * This function get the price
 * @param room the current room object to get from(its assume that room not null
 * @return
 * the price of the room
 */
int roomGetPrice(Room room);

/**
 *This function get the number of people for the room
 * @param room the current room object to get from(its assume that room not null
 * @return
 * the number of people for room
 */
int roomGetNumOfPepole(Room room);

/**
 *This function get the opening time
 * @param room the current room object to get from(its assume that room not null
 * @return
 * the opening time
 */
int roomGetOpenTime(Room room);

/**
 *This function get the closing time
 * @param room the current room object to get from(its assume that room not null
 * @return
 * the closing time
 */
int roomGetCloseTime(Room room);

/**
 * this function get the difficulty level of the room
 * @param room the current room object to get from(its assume that room
 * not null)
 * @return
 * the difficulty level of the room
 */
int roomGetDifficulty(Room room);

/**
 * this function get the number of orders of the room
 * @param room the current room object to get from(its assume that room
 * not null)
 * @return
 * the number of active orders for this room
 */
int roomGetNumberOfOrders(Room room);

/**
 * this function increase the number of orders of the room
 * @param room the current room object to get from(its assume that room
 * not null)
 */
void roomIncNumberOfOrders(Room room);

/**
 * this function decrease the number of orders of the room
 * @param room the current room object to get from(its assume that room not null
 */
bool roomDecNumberOfOrders(Room room);

/**
 * this function makes copy of room
 * @return
 * returns a copied room object
 */
Room roomCopy(Room room);

/**
 * this function compares two rooms by id
 * @return
 * 0 if equal, 1 if param1 id is bigger then param2 id, otherwise -1 otherwise
 */
int roomCompare(Room room1, Room room2);


#endif /*ROOM_H_*/
