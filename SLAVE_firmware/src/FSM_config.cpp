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
    mySensor.debounce();    // Read TOF sensor
    finalSensor.debounce(); // Read 2nd

    // If starting time isnt defined and 1 of the sensors are blocked
    if (!gait_assessment.hasBegun() && (mySensor.getStatus() || finalSensor.getStatus()))
    {
        (mySensor.getStatus()) ? (mySensor.flag++) : (finalSensor.flag++);
        gait_assessment.setStartTime();
        myFSM.setEvent(events::speed_measured);
    }

    // If start time was recorded, and reading the opposite
    else if (gait_assessment.hasBegun() && ((mySensor.getStatus() && finalSensor.flag) || (finalSensor.getStatus() && mySensor.flag)))
    {
        gait_assessment.computeSpeed();
        myFSM.setEvent(speed_measured);
        mySensor.flag++;
        finalSensor.flag++;
    }

    else if (mySensor.flag && finalSensor.flag && !mySensor.getStatus() && !finalSensor.getStatus())
    {
        mySensor.flag = 0;
        finalSensor.flag = 0;
        gait_assessment.reset();
    }

    switch (myFSM.getEvent())
    {
    case events::back:

        mySensor.flag = 0;
        finalSensor.flag = 0;
        gait_assessment.reset();
        myFSM.setState(INIT_stateHandler);
        break;

    case events::select:
        finalSensor.flag = 0;
        mySensor.flag = 0;
        gait_assessment.reset();
        //Serial.println("reseted!");
        break;

    case events::speed_measured:
        break;

    default:
        break;
    }
}
