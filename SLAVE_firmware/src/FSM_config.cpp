#include "FSM.h"

FSM myFSM;

// FSM events must be listed in functions_config.h

/*####################################################################################################
    setup which initial state for the State machine (and print its page)
####################################################################################################*/

void FSM::init()
{
    myFSM.setState(INIT_stateHandler);
}

/*####################################################################################################
    create your state handling functions for your FSM here
####################################################################################################*/

/***************************************************************************
 * States:
 * INIT, SETUP, WAIT_FOR_RFID, TOF, 
 * 
 ***************************************************************************/

void INIT_stateHandler()
{
    if (myFSM.getEvent() == events::calib_request)
    {
        myFSM.setState(TOF_CALIB_stateHandler);
    }
}

void TOF_CALIB_stateHandler()
{
    if(mySlaveSensor.calibrate())
    {
        myFSM.setState(TOF_stateHandler);
        send_byte_BT(CALIB_SUCCESSFUL_MESSAGE);
    }
    else
    {
        myFSM.setState(INIT_stateHandler);
    }
    
}

void WAIT_FOR_RFID_stateHandler()
{
    switch (myFSM.getEvent())
    {
    case events::back:

        myFSM.setState(INIT_stateHandler);
        break;

    case events::RFID_detected:

        myFSM.setState(TOF_stateHandler);
        break;

    case events::select: // Pressing select gets you into continuous reading
        myFSM.setEvent(events::RFID_detected);
        break;

    default:
        break;
    }
}

void TOF_stateHandler()
{
    mySlaveSensor.debounce(); // Read TOF sensor

    //if status is blocked, we measure time and send it to Master. it will figure out what to do with it.
    if (mySlaveSensor.getStatus())
    {
        if (!mySlaveSensor.flag)
        {
            mySlaveSensor.flag++;
            myFSM.setEvent(events::TOF_blocked);
        }
    }
    else if (!mySlaveSensor.getStatus() && mySlaveSensor.flag)
        mySlaveSensor.flag = 0;

    switch (myFSM.getEvent())
    {
    case events::TOF_blocked:
        send_byte_BT(TIME_MEASURED_MESSAGE);
        //Serial.println("sent");

        break;

    case events::speed_measured:
        break;

    case events::stop_measuring_request:
    myFSM.setState(INIT_stateHandler);
    break;

    default:
        break;
    }
}
