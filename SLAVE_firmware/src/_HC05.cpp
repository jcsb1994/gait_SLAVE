#include "_HC05.h"

SoftwareSerial BTserial(9, 10);

void testBT()
{
  if (BTserial.available())
  {
    byte x = BTserial.read();
    Serial.write(x);
  }

  if (Serial.available())
  {
    byte y = Serial.read();
    BTserial.write(y);
  }
}

#define ENTER_MEASURING_MODE_MESSAGE
#define RFID_RECOGNIZED_MESSAGE 1
#define START_TIME_MEASURED_MESSAGE 97 // a
#define TEST_RESULT_MILLISEC_MESSAGE 2

void read_BT_events()
{
  if (BTserial.available())
  {
    uint8_t receivedByte = BTserial.read();
    //BTserial.write(y);
    switch (receivedByte)
    {
    case START_TIME_MEASURED_MESSAGE:
      //record time NOW
      break;

    case RFID_RECOGNIZED_MESSAGE:
      myFSM.setEvent(events::RFID_detected);
      break;

    case TEST_RESULT_MILLISEC_MESSAGE:

      break;

    default:
      break;
    }
  }
}

void send_byte_BT(uint8_t message)
{
  BTserial.write(message);
}