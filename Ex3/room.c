#include "room.h"
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * this function insert the working hours to a room object
 * @param room the current room object to get from(its assume that room not null)
 * @param working_hrs the working hours of room at "xx-yy" template
 */
static void insertWorkingHrs(Room room, char* working_hrs);

/**
 * this function checks that the working hours at the current form
 * @param working_hrs a string to check.
 * @return
 * true in case of current form, else returns false
 */
static bool checkWorkingHrs(char* working_hrs);


/* Room Struct */
struct Room_t{
    int id;
    int price;
    int num_ppl;
    int open_time;
    int close_time;
    int difficulty;
    int num_of_orders;
};


Room roomCreate(int id,int price, int num_ppl, char* working_hrs,
                int difficulty, RoomErrorCode* error){
    if (working_hrs == NULL){
        *error = ROOM_NULL_PARAMETER;
        return NULL;
    }
    if ((price <= 0 || price%4 != 0) || id <= 0 || num_ppl <= 0 ||
        checkWorkingHrs(working_hrs) == false || difficulty < 1 ||
            10 < difficulty){
        *error = ROOM_INVALID_PARAMETER;
        return NULL;
    }
    Room room = malloc(sizeof(*room));
    if (room == NULL){
        *error = ROOM_OUT_OF_MEMORY;
        return NULL;
    }
    room->id = id;
    insertWorkingHrs(room, working_hrs);
    room->difficulty = difficulty;
    room->price = price;
    room->num_ppl = num_ppl;
    room->num_of_orders = 0;
    *error = ROOM_SUCCESS;
    return room;
}

void roomDestroy(Room room){
    if (room == NULL){
        return;
    }
    free(room);
}

int roomGetId(Room room) {
    assert(room != NULL);
    return room->id;
}

int roomGetPrice(Room room){
    assert(room != NULL);
    return room->price;
}

int roomGetNumOfPepole(Room room){
    assert(room != NULL);
    return room->num_ppl;
}

int roomGetOpenTime(Room room){
    assert(room != NULL);
    return room->open_time;
}

int roomGetCloseTime(Room room){
    assert(room != NULL);
    return room->close_time;
}

int roomGetDifficulty(Room room){
    assert(room != NULL);
    return room->difficulty;
}

int roomGetNumberOfOrders(Room room){
    assert(room != NULL);
    return room->num_of_orders;
}

void roomIncNumberOfOrders(Room room){
    assert(room != NULL);
    room->num_of_orders++;
}

bool roomDecNumberOfOrders(Room room){
    assert(room != NULL);
    if(room->num_of_orders == 0){
        return false;
    }
    room->num_of_orders--;
    return false;
}

Room roomCopy(Room room){
    assert(room != NULL);
    Room new_room = malloc(sizeof(*room));
    if(new_room == NULL){
        return NULL;
    }
    new_room->id = room->id;
    new_room->open_time = room->open_time;
    new_room->price = room->price;
    new_room->num_ppl = room->num_ppl;
    new_room->close_time = room->close_time;
    new_room->difficulty = room->difficulty;
    new_room->num_of_orders = room->num_of_orders;
    return new_room;
}

int roomCompare(Room room1, Room room2){
    assert(room1 != NULL && room2 != NULL);
    if(room1->id > room2->id){
        return 1;
    } else if (room1->id < room2->id){
        return -1;
    }
    return 0;
}


static void insertWorkingHrs(Room room, char* working_hrs){
    assert(room != NULL && working_hrs != NULL);
    room->open_time = ((*working_hrs-'0')*10 + *(working_hrs+1)-'0');
    room->close_time = ((*(working_hrs+3)-'0')*10 + *(working_hrs+4)-'0');
}

static bool checkWorkingHrs(char* working_hrs){
    assert(working_hrs != NULL);
    if (working_hrs[0] < '0' || '9' < working_hrs[0] || working_hrs[1] < '0' ||
        '9' < working_hrs[1]){
        return false;
    }
    int open_time = (working_hrs[0] - '0')*10 + (working_hrs[1] - '0');
    if (working_hrs[2] != '-'){
        return false;
    }
    if (working_hrs[3] < '0' || '9' < working_hrs[3] || working_hrs[4] < '0' ||
        '9' < working_hrs[4]){
        return false;
    }
    int close_time = (working_hrs[3] - '0')*10 + (working_hrs[4] - '0');
    if (open_time >= close_time || 24 < open_time || 24 < close_time){
        return false;
    }
    if (working_hrs[5] != 0){
        return false;
    }
    return true;
}
