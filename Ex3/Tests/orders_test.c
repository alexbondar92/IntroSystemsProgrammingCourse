#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test_utilities.h"
#include "../orders.h"



 static bool testOrderCreate(){
     int days = 30;
     int iligal_day = -5;
     int time = 21;
     int iligal_time = 24;
     int room_id = 54;
     int iligal_room_id = -60;

     TechnionFaculty faculty = ELECTRICAL_ENGINEERING;
     
     char* escaper_email = "stasneiman@gmail.com";
     char* company_email = "BigImportentCompany@gmail.com";

     EmailErrorCode email_error = EMAIL_SUCCESS;
     Email escaper_Email = emailCreate(escaper_email, &email_error);
     Email company_Email = emailCreate(company_email, &email_error);
     
     
     OrderErrorCode order_error = ORDER_SUCCESS;
     Order order = orderCreate(iligal_day, time, room_id, faculty, company_Email, 4, 12, escaper_Email, &order_error);
     ASSERT_TEST(order_error == ORDER_INVALID_PARAMETER && order == NULL);
     order = orderCreate(days, iligal_time, room_id, faculty, company_Email, 4, 12 , escaper_Email, &order_error);
     ASSERT_TEST(order_error == ORDER_INVALID_PARAMETER && order == NULL);
     order = orderCreate(days, time, iligal_room_id, faculty, company_Email, 4, 12, escaper_Email, &order_error);
     ASSERT_TEST(order_error == ORDER_INVALID_PARAMETER && order == NULL);
     order = orderCreate(days, time, room_id, -20, company_Email, 4, 12, escaper_Email, &order_error);
     ASSERT_TEST(order_error == ORDER_INVALID_PARAMETER && order == NULL);
     order = orderCreate(days, time, room_id, faculty, company_Email, 0, 12, escaper_Email, &order_error);
     ASSERT_TEST(order_error == ORDER_INVALID_PARAMETER);
     order = orderCreate(days, time, room_id, faculty, company_Email, 4, 12, escaper_Email, &order_error);
     ASSERT_TEST(order_error == ORDER_SUCCESS && order != NULL);
     
     orderDestroy(order);
     emailDestroy(escaper_Email);
     emailDestroy(company_Email);
     return true;
}

static bool testOrderCopy(){
    int days = 30;
    int time = 21;
    int room_id = 54;
    
    TechnionFaculty faculty = ELECTRICAL_ENGINEERING;

    char* escaper_email = "stasneiman@gmail.com";
    char* company_email = "BigImportentCompany@gmail.com";

    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email escaper_Email = emailCreate(escaper_email, &email_error);
    Email company_Email = emailCreate(company_email, &email_error);


    OrderErrorCode order_error = ORDER_SUCCESS;
    Order order = orderCreate(days, time, room_id, faculty, company_Email, 4, 20, escaper_Email, &order_error);
    ASSERT_TEST(order_error == ORDER_SUCCESS && order != NULL);
    Order newCopyOrder = orderCopy(order);
    ASSERT_TEST(newCopyOrder != NULL);

    int days1 = orderGetDaysTillOrder(order);
    int days2 = orderGetDaysTillOrder(newCopyOrder);
    ASSERT_TEST(days1 == days2);


    int time1 = orderGetTimeOfOrder(order);
    int time2 = orderGetTimeOfOrder(newCopyOrder);
    ASSERT_TEST(time1 == time2);

    TechnionFaculty faculty1 = orderGetFaculty(order);
    TechnionFaculty faculty2 = orderGetFaculty(newCopyOrder);
    ASSERT_TEST(faculty1 == faculty2);

    int id1 = orderGetRoomId(order);
    int id2 = orderGetRoomId(newCopyOrder);
    ASSERT_TEST(id1 == id2);

    Email email1 = orderGetCompanyEmail(order);
    Email email2 = orderGetCompanyEmail(newCopyOrder);
    int flag = emailCompare(email1, email2);
    ASSERT_TEST(flag == 0);

    email1 = orderGetEscaperEmail(order);
    email2 = orderGetEscaperEmail(newCopyOrder);
    int flag1 = emailCompare(email1, email2);
    ASSERT_TEST(flag1 == 0);

    emailDestroy(company_Email);
    emailDestroy(escaper_Email);
    orderDestroy(order);
    orderDestroy(newCopyOrder);
    return true;

}

static bool testOrderReduceDay() {
    int days = 30;
    int time = 21;
    int room_id = 54;

    TechnionFaculty faculty = ELECTRICAL_ENGINEERING;

    char *escaper_email = "stasneiman@gmail.com";
    char *company_email = "BigImportentCompany@gmail.com";

    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email escaper_Email = emailCreate(escaper_email, &email_error);
    Email company_Email = emailCreate(company_email, &email_error);


    OrderErrorCode order_error = ORDER_SUCCESS;
    Order order = orderCreate(days, time, room_id, faculty, company_Email, 4, 24, escaper_Email, &order_error);
    ASSERT_TEST(order_error == ORDER_SUCCESS && order != NULL);
    ASSERT_TEST(orderGetDaysTillOrder(order) == 30);
    orderReduceDay(order);
    ASSERT_TEST(orderGetDaysTillOrder(order) == 29);

    emailDestroy(company_Email);
    emailDestroy(escaper_Email);
    orderDestroy(order);

    return true;
}

static bool testOrderCompare() {
    int days = 30;
    int time = 21;
    int room_id = 54;

    TechnionFaculty faculty = ELECTRICAL_ENGINEERING;

    char *escaper_email = "stasneiman@gmail.com";
    char *company_email = "BigImportentCompany@gmail.com";

    EmailErrorCode email_error = EMAIL_SUCCESS;
    Email escaper_Email = emailCreate(escaper_email, &email_error);
    Email company_Email = emailCreate(company_email, &email_error);


    OrderErrorCode order_error = ORDER_SUCCESS;
    Order order1 = orderCreate(days, time, room_id, faculty, company_Email, 4,
                               24, escaper_Email, &order_error);
    ASSERT_TEST(order_error == ORDER_SUCCESS && order1 != NULL);

    Order order2 = orderCopy(order1);
    ASSERT_TEST(orderDayCompare(order1, order2) == 0);
    orderDestroy(order2);


    Order order3 = orderCreate(days, time+1, room_id, faculty, company_Email, 4,
                               24, escaper_Email, &order_error);
    ASSERT_TEST(orderDayCompare(order1, order3) == 1);
    orderDestroy(order3);

    Order order4 = orderCreate(days+2, time, room_id, faculty, company_Email, 4,
                               24, escaper_Email, &order_error);
    ASSERT_TEST(orderDayCompare(order1, order4) == 1);
    orderDestroy(order4);

    Order order5 = orderCreate(days, time-5, room_id, faculty, company_Email, 4,
                               24, escaper_Email, &order_error);
    ASSERT_TEST(orderDayCompare(order1, order5) == -1);
    orderDestroy(order5);


    emailDestroy(company_Email);
    emailDestroy(escaper_Email);
    orderDestroy(order1);
    return true;
}

int main/*OrderTest*/(){
    RUN_TEST(testOrderCreate);
    RUN_TEST(testOrderCopy);
    RUN_TEST(testOrderReduceDay);
    RUN_TEST(testOrderCompare);
    return 0;
}
