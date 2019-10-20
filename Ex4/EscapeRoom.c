#include "EscapeRoom.h"
#include <stdlib.h>
#include <string.h>

struct escaperoom_t{
    char* name;
    int maxTime;
    int level;
    int maxParticipants;
    double avgRate;
    int votes;
};

EscapeRoom escapeRoomCreate(char* name, int maxTime,int maxParticipants, int level){
    EscapeRoom room = (EscapeRoom)malloc(sizeof(*room));
    if(!room){
        return NULL;
    }
    char* newName = (char*)malloc(strlen(name) +1);
    if(!newName){
        free(room);
        return NULL;
    }
    strcpy(newName, name);
    room->name = newName;
    room->maxTime = maxTime;
    room->maxParticipants = maxParticipants;
    room->level = level;
    room->votes = 0;
    room->avgRate = 0;
    return room;
}

EscapeRoom escapeRoomCopy(EscapeRoom room){
    if(!room) return NULL;
    EscapeRoom newRoom = escapeRoomCreate(room->name,room->maxTime,room->maxParticipants,room->level);
    if(!newRoom){
        return NULL;
    }
    newRoom->votes = room->votes;
    newRoom->avgRate = room->avgRate;
    return newRoom;
}

static double power(EscapeRoom r){
    return ((double)(r->level * r->maxTime)/(double)(r->maxParticipants));
}

bool areEqualRooms(EscapeRoom room1, EscapeRoom room2){
    if(!room1 || !room2){
        return false;
    }

    return (power(room1) == power(room2)) && (strcmp(room1->name, room2->name) == 0);
}

bool isBiggerRoom(EscapeRoom room1, EscapeRoom room2){
    if(!room1 || !room2){
        return false;
    }
    return power(room1) > power(room2);
}

int getLevel(EscapeRoom room){
    if(!room){
        return -1;
    }
    return room->level;
}

RoomResult updateRate(EscapeRoom room, int newRate){
    if(!room) return ESCAPEROOM_NULL_ARG;
    if(newRate < 0 || newRate > 5) return ESCAPEROOM_BAD_PARAM;
    int sum = room->avgRate * room->votes;
    sum += newRate;
    room->votes++;
    room->avgRate = ((double)sum/room->votes);
    return ESCAPEROOM_SUCCESS;
}

char* roomGetName(EscapeRoom room){
    if(!room) return NULL;
    char* nameCopy = (char*)malloc(strlen(room->name) +1);
    if(!nameCopy) return NULL;
    strcpy(nameCopy, room->name);
    return nameCopy;
}

int roomGetMaxTime(EscapeRoom room){
    if(!room) return -1;
    return room->maxTime;
}

int roomGetMaxParticipants(EscapeRoom room){
    if(!room) return -1;
    return room->maxParticipants;
}

double roomGetRate(EscapeRoom room){
    if(!room) return -1;
    return room->avgRate;
}

void escapeRoomDestroy(EscapeRoom room){
    if(!room) return;
    free(room->name);
    free(room);
}
