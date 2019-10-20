#ifndef ORDERS_H_
#define ORDERS_H_

#include <stdbool.h>
#include "escape_utilitis.h"
#include "mtm_ex3.h"

/**
 * Orderd Container
 *
 * Implements a order container type.
 *
 * The following functions are available:
 *
 *   orderCreate            - Creates a new order
 *   orderDestroy           - Deletes an existing order and frees all resources
 *   orderGetEscaperEmail   - Getting the Email of the escaper
 *   orderGetCompanyEmail   - Getting the Email of the escaper
 *   orderGetRoomId         - Getting the room Id
 *   orderGetFaculty        - Getting the faculty of the order
 *   orderGetDaysTillOrder  - Getting the number of days till the order day
 *   orderGetTimeOfOrder    - Getting the time of the order
 *   orderGetTotalPrice     - Getting the total price of the order
 *   orderGetPeopleNumber   - Getting the total number of people for this order
 *   orderReduceDay         - Reduces a day from number of days till the order
 *                            day
 *   orderCopy              - create a copy of order
 *   orderDayCompare        - compares between two orders by date
 */

/**
 * This type defines all errors for the Order ADT.
 */
typedef enum {
    ORDER_OUT_OF_MEMORY, // You should exit program after this error
    ORDER_NULL_PARAMETER,
    ORDER_INVALID_PARAMETER,
    ORDER_SUCCESS
} OrderErrorCode;

/** Type for defining the order */
typedef struct Order_t *Order;


/**
 * Create a new Order.
 *
 * Creates a new order. This function resive all the data for first initial of
 * new order, and reset the rest
 * @param days number of days till the order date
 * @param time of the order
 * @param room_id the id of the room witch the order is
 * @param faculty the fuculty that ownes the company witch own the room
 * @param company_email email of the company
 * @param num_ppl the people number for current order
 * @param price the price of that order
 * @param escaper_email of the escaper
 * @param error the error returning parameter code
 * @return
 * ORDERS_INVALID_PARAMETER in case of invaild one or more of parameters
 * ORDERS_OUT_OF_MEMORY in case of allocation fail
 * ORDERS_SUCCESS in case of success, returns new order object
 */
Order orderCreate(int days, int time, int room_id, TechnionFaculty faculty,
                  Email company_email, int num_ppl, int price,
                  Email escaper_email, OrderErrorCode* error);

/**
 * This function destroys the order
 * @param order Target to be deallocated. If room is NULL nothing will be done
 */
void orderDestroy(Order order);

/**
 * This function get the email of company of the order
 * @param order the current order object to get from(its assume that room
 * not null)
 * @return
 * the company email of the order
 */
Email orderGetCompanyEmail(Order order);

/**
 * This function get the email of escaper of the order
 * @param order the current order object to get from(its assume that room
 * not null)
 * @return
 * the escaper email of the order
 */
Email orderGetEscaperEmail(Order order);

/**
 * This function get the id of room of the order
 * @param order the current order object to get from(its assume that room not null)
 * @return
 * the room id of the order
 */
int orderGetRoomId(Order order);

/**
 * This function get the faculty of the order
 * @param order the current order object to get from(its assume that room not null)
 * @return
 * the faculty of the order
 */
TechnionFaculty orderGetFaculty(Order order);


/**
 * This function get the days till order time
 * @param order the current order object to get from(its assume that room not null)
 * @return
 * the number of days till order time
 */
int orderGetDaysTillOrder(Order order);

/**
 * This function get the time  of the order
 * @param order the current order object to get from(its assume that room not null)
 * @return
 * the time of the order
 */
int orderGetTimeOfOrder(Order order);

/**
 * This function get the total price of the order
 * @param order the current order object to get from(its assume that room
 * not null)
 * @return
 * the total price of the order
 */
int orderGetTotalPrice(Order order);

/**
 * This function get the total number of people  in the order
 * @param order the current order object to get from(its assume that room
 * not null)
 * @return
 * the total number of people in the order
 */
int orderGetPeopleNumber(Order order);

/**
 * This function reduce a day by one of the order
 * @param order the current order object to get from(its assume that room not null)
 */
void orderReduceDay(Order order);

/**
 * This function make a copy of order
 * @param order the current order object to get from(its assume that room not null)
 * @return
 * the copy order object
 */
Order orderCopy(Order order);

/**
 * This function compare two orders by thier time.
 * @param order1 the current order object to get from(its assume that room not null)
 * @param order2 the current order object to get from(its assume that room not null)
 * @return
 * 0 if equal, 1 if param1 order time sooner then param2 order time, otherwise -1 otherwise
 */
int orderDayCompare(Order order1, Order order2);


#endif /*ORDERS_H_*/
