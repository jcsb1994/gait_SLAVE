#ifndef _TOF_H
#define _TOF_H

#include "main.h"
#include <VL53L1X.h>

class TOF
{
private:
  VL53L1X *linked_sensor;

  int currentReading;
  int lastReading;
  bool maybeFlag;
  int integrator;
  bool tof_status;

  //bool calibrationFlag;
  int minimumClearValue;

public:
  TOF(VL53L1X &sensor_to_link) : linked_sensor(&sensor_to_link)
  {
  }

  bool calibrate(); // calibrates with current wall distance before entering measurement mode
  //bool isCalibrationDone;

 /* bool isCalibrated()
  {
    return calibrationFlag;
  }*/

  void debounce();
  void init();
  bool getStatus()
  {
    return tof_status;
  }
  bool flag;
};

//---------------------------------------------------------------

extern VL53L1X slaveSensor;
extern TOF mySlaveSensor;

void tof_setup();

#endif