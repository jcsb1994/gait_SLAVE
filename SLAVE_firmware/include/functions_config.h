#ifndef TACT_ACT_H
#define TACT_ACT_H

#include "main.h"

/*####################################################################################################
    Tact switch buttons actions (create a function for each) **in tact config cpp file
####################################################################################################*/


/*####################################################################################################
    Pages to print (create a function for each) **in menu config cpp file
####################################################################################################*/

#define INIT_SETUP_POS 0
#define INIT_START_POS 2
//void print_init_page();

#define SETUP_TEST_TYPE_POS 0
#define SETUP_EXACT_DISTANCE 1
#define SETUP_BT_PAIR_POS 2
//void print_setup_page();

//void print_wait_for_rfid_page();

//void print_rfid_detected_page();

/*####################################################################################################
    State Machine (FSM) events (list all possible events here, STARTING WITH = 1)
####################################################################################################*/
enum events
{
    select = 1,
    increment,
    decrement = 3,

    TOF_blocked,
    calib_request,
    stop_measuring_request,
   // calib_success,

    RFID_detected,
    back,
    speed_measured, //maybe?
    RFID_left
};

/*####################################################################################################
    State Machine (FSM) state handlers (create a function for each) **in FSM config cpp file
####################################################################################################*/

void INIT_stateHandler();

void SETUP_stateHandler();

void TOF_CALIB_stateHandler();

void BT_PAIR_stateHandler();

void WAIT_FOR_RFID_stateHandler();

void TOF_stateHandler();

#endif