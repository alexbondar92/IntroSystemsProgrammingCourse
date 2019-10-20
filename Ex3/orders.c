#include "orders.h"
#include <assert.h>
#include <stdlib.h>



/* Order Struct */
struct Order_t{
    int days;
    int time;
    int room_id;
    int num_ppl;
    int total_price;
    TechnionFaculty faculty;
    Email escaper_email;
    Email company_email;
};


Order orderCreate(int days, int time, int room_id, TechnionFaculty faculty,
                  Email company_email, int num_ppl, int price,
                  Email escaper_email, OrderErrorCode* error){
    if( days < 0 || time < 0 || time > 23 || room_id <= 0 || num_ppl <= 0 ||
       price <= 0 || (int)faculty < 0 || faculty > (NUM_OF_FACULTYS-1)){
        *error = ORDER_INVALID_PARAMETER;
        return NULL;
    }
    if ( company_email == NULL || escaper_email == NULL){
        *error = ORDER_NULL_PARAMETER;
        return NULL;
    }
    Order order = malloc(sizeof(*order));
    if (order == NULL){
        *error = ORDER_OUT_OF_MEMORY;
        return NULL;
    }
    order->days = days;
    order->time = time;
    order->num_ppl = num_ppl;
    order->total_price = price;
    order->room_id = room_id;
    order->faculty = faculty;
    order->company_email = emailCopy(company_email);
    order->escaper_email = emailCopy(escaper_email);
    *error = ORDER_SUCCESS;
    return order;
}

void orderDestroy(Order order){
    if (order == NULL){
        return;
    }
    emailDestroy(order->company_email);
    emailDestroy(order->escaper_email);
    free(order);
}

Email orderGetCompanyEmail(Order order){
    assert(order != NULL);
    return order->company_email;
}

Email orderGetEscaperEmail(Order order){
    assert(order != NULL);
    return order->escaper_email;
}

int orderGetRoomId(Order order){
    assert(order != NULL);
    return order->room_id;
}

TechnionFaculty orderGetFaculty(Order order){
    assert(order != NULL);
    return order->faculty;
}

int orderGetDaysTillOrder(Order order){
    assert(order != NULL);
    return order->days;
}


int orderGetTimeOfOrder(Order order){
    assert(order != NULL);
    return order->time;
}

int orderGetTotalPrice(Order order){
    assert(order != NULL);
    return order->total_price;
}

int orderGetPeopleNumber(Order order){
    assert(order != NULL);
    return order->num_ppl;
}

void orderReduceDay(Order order){
    assert(order != NULL);
    --(order->days);
}

Order orderCopy(Order order){
    assert(order != NULL);
    OrderErrorCode error;
    return orderCreate(order->days, order->time, order->room_id, order->faculty,
                       order->company_email, order->num_ppl, order->total_price,
                       order->escaper_email, &error);
}

int orderDayCompare(Order order1, Order order2){
    assert(order1 != NULL && order2 != NULL);
    if (order1->days == order2->days && order1->time == order2->time){
        return 0;
    }
    if (order1->days < order2->days || (order1->days == order2->days &&
            order1->time < order2->time)){
        return 1;
    }
    return -1;
}

int orderEmailCompare(Order order1, Order order2){
    assert(order1 != NULL && order2 != NULL);
    if (emailCompare(order1->escaper_email, order2->escaper_email)==0){
        return 1;
    }
    return 0;
}
