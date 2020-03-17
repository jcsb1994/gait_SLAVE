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


void read_BT_events()
{
  if (BTserial.available())
  {
    uint8_t receivedByte = BTserial.read();
    //BTserial.write(y);
    switch (receivedByte)
    {
      case ENTER_MEASURING_MODE_MESSAGE:
      //Serial.println ("ye");
      break;

    case STOP_MEASURING_MESSAGE:
      myFSM.setEvent(events::stop_measuring_request);
      break;

    case RFID_RECOGNIZED_MESSAGE:
      myFSM.setEvent(events::RFID_detected);
      break;

    case ENTER_CALIB_MESSAGE:
    myFSM.setEvent(events::calib_request);
      break;

    default:
      break;
    }
  }
}



void send_byte_BT(unsigned char message)
{
  BTserial.write(message);
}