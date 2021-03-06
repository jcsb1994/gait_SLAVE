#include "_tof.h"

#define THRESHOLD 300
#define UBSTRUCTED_MAXIMUM 3
#define CLEAR_MAXIMUM -3
#define PATH_UBSTRUCTED 1
#define PATH_CLEAR 0

// TOF class to give proper measurement methods to each VL53L1X


#define CALIB_READINGS 10
#define MAX_CALIB_ATTEMPTS 5
bool TOF::calibrate()
{
  //calibrationFlag = 0; //reset last calibration results

  int curr;
  int max = linked_sensor->read();  // Max to make sure the minimum clear value is not due to someone blocking during calib
  uint8_t nAttempts;
  do
  {
    // Serial.println("trying calib");
    nAttempts++;

    for (int i = 0; i < CALIB_READINGS; i++)
    {
      curr = linked_sensor->read();
      minimumClearValue = curr;
      max = curr;

      if (curr < minimumClearValue)
        minimumClearValue = curr;
      if (curr > max)
        max = curr;
      delay(100);
    }

  } while ((max - minimumClearValue) > 800 && nAttempts < MAX_CALIB_ATTEMPTS); // Do again if more than 800 difference between calib readings
  // Serial.println("calib done");

  if (nAttempts < MAX_CALIB_ATTEMPTS)
    //calibrationFlag = 1; // Succesful calib
    return 1;
  else
  {
    //calibrationFlag = 0;
    return 0;
  }

}


void TOF::debounce()
{
  currentReading = linked_sensor->read(); //get the newest reading
  //Serial.println(currentReading);

  if (lastReading - currentReading > THRESHOLD) //if last was bigger, someone might be in front
  {
    if (integrator < UBSTRUCTED_MAXIMUM)
    {
      integrator++;
    }
  }
  else if (currentReading - lastReading > THRESHOLD) //if now is bigger, someone might have left
  {
    if (integrator > CLEAR_MAXIMUM)
    {
      integrator--;
    }
  }
  else if (integrator > 0 /*&& integrator < UBSTRUCTED_MAXIMUM*/)
    integrator--;
  else if (integrator < 0 /*&& integrator > CLEAR_MAXIMUM*/)
    integrator++;

  if (integrator >= UBSTRUCTED_MAXIMUM)
  {
    integrator = 0; // Defensive code if integrator got corrupted
    tof_status = PATH_UBSTRUCTED;
  }

  if (integrator <= CLEAR_MAXIMUM)
  {
    integrator = 0; // Defensive code if integrator got corrupted
    tof_status = PATH_CLEAR;
  }

  (integrator) ? (maybeFlag++) : (maybeFlag = 0, lastReading = currentReading);
}

void TOF::init()
{
  linked_sensor->setTimeout(500);
  //linked_sensor->init();
  linked_sensor->setDistanceMode(VL53L1X::Long);
  linked_sensor->setMeasurementTimingBudget(50000);
  linked_sensor->startContinuous(50);
}

VL53L1X slaveSensor;
TOF mySlaveSensor(slaveSensor);


#define sensorShutPin 2

void tof_setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(sensorShutPin, OUTPUT);
  Wire.setClock(400000); // use 400 kHz I2C
  //digitalWrite(sensorShutPin, HIGH);  //XSHUT is active Low

  slaveSensor.init(); //resets address back to default
  mySlaveSensor.init();  

}