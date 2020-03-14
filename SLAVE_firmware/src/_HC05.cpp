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
      Serial.println ("ye");
      break;

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



void send_byte_BT(unsigned char message)
{
  BTserial.write(message);
}