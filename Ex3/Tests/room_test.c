#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test_utilities.h"
#include "../room.h"


static bool testRoomCreate() {
    char* working_hrs = "08-12";
    char* bad_hrs1 = "23-11";
    char* bad_hrs2 = "23-56";
    char* bad_hrs3 = "10_18";
    RoomErrorCode error = ROOM_SUCCESS;
    Room room = roomCreate(-1, 40, 1, working_hrs, 2, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(0, 40, 1, working_hrs, 2, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 7, 1, working_hrs, 2, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 0, 1, working_hrs, 2, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 0, working_hrs, 2, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, working_hrs, 0, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, working_hrs, 11, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, bad_hrs1, 7, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, bad_hrs2, 7, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, bad_hrs3, 7, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    
    room = roomCreate(34, 28, 10, "232-34", 5, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, "232.34", 5, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, "aa-34", 5, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    room = roomCreate(34, 28, 10, "11-1823", 5, &error);
    ASSERT_TEST(error == ROOM_INVALID_PARAMETER && room == NULL);
    
    room = roomCreate(55, 124, 6, working_hrs, 5, &error);
    ASSERT_TEST(error == ROOM_SUCCESS && room != NULL);
    
    ASSERT_TEST(roomGetId(room) == 55);
    ASSERT_TEST(roomGetPrice(room) == 124);
    ASSERT_TEST(roomGetOpenTime(room) == 8);
    ASSERT_TEST(roomGetCloseTime(room) == 12);
    ASSERT_TEST(roomGetDifficulty(room) == 5);
    ASSERT_TEST(roomGetNumOfPepole(room) == 6);
    
    roomDestroy(room);
    return true;
}

static bool testRoomCompare() {
    char* working_hrs1 = "05-19";
    RoomErrorCode error = ROOM_SUCCESS;
    Room room1 = roomCreate(79, 48, 12, working_hrs1, 2, &error);
    ASSERT_TEST(room1 != NULL);
    char* working_hrs2 = "12-23";
    Room room2 = roomCreate(79, 44, 10, working_hrs2, 2, &error);
    ASSERT_TEST(room2 != NULL);
    
    Room room3 = roomCreate(1, 44, 10, working_hrs2, 2, &error);
    ASSERT_TEST(room3 != NULL);
    
    ASSERT_TEST(roomCompare(room1, room2) == 0);
    ASSERT_TEST(roomCompare(room2, room3) == 1);
    ASSERT_TEST(roomCompare(room3, room1) == -1);
    
    roomDestroy(room1);
    roomDestroy(room2);
    roomDestroy(room3);
    return true;
}

static bool testRoomCopy() {
    char* working_hrs = "05-19";
    RoomErrorCode error = ROOM_SUCCESS;
    Room room = roomCreate(79, 48, 12, working_hrs, 2, &error);
    ASSERT_TEST(room != NULL);
    
    Room new_room = roomCopy(room);
    ASSERT_TEST(new_room != NULL);
    ASSERT_TEST(roomGetId(room) == roomGetId(new_room));
    ASSERT_TEST(roomGetPrice(room) == roomGetPrice(new_room));
    ASSERT_TEST(roomGetOpenTime(room) == roomGetOpenTime(new_room));
    ASSERT_TEST(roomGetCloseTime(room) == roomGetCloseTime(new_room));
    ASSERT_TEST(roomGetNumOfPepole(room) == roomGetNumOfPepole(new_room));
    ASSERT_TEST(roomGetDifficulty(room) == roomGetDifficulty(new_room));
    ASSERT_TEST(roomGetNumberOfOrders(room) == roomGetNumberOfOrders(new_room));
    
    roomDestroy(room);
    roomDestroy(new_room);
    return true;
}


static bool testRoomDestroy() {
    /* ====================== already had been checked ====================== */
    return true;
}

int main/*RoomTest*/(){
    RUN_TEST(testRoomCreate);
    RUN_TEST(testRoomCompare);
    RUN_TEST(testRoomCopy);
    RUN_TEST(testRoomDestroy);
    return 0;
}


