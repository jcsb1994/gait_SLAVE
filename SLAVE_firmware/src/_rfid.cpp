#include "_rfid.h"

#define LEFT_MAX 3

void Patient_RFID::scanUIDs()
{
    if (millis() - last_RFID_read > 200)
    {
        last_RFID_read = millis();
        if (linked_RFID->PICC_IsNewCardPresent() && linked_RFID->PICC_ReadCardSerial()) // If card is read, read the active
        {
            UID_integrator = 0; // Reset count before being sure they left
            for (int i = 0; i < 4; i++)
            {
                activeID[i] = linked_RFID->uid.uidByte[i];
            }
            setUID();
            myFSM.setEvent(events::RFID_detected);
            Serial.println("detec");
        }

        else
        {
            UID_integrator++;
            if (UID_integrator >= LEFT_MAX)
            {
                //patient_UID_flag = 0;
                memset(activeID, 0, sizeof(activeID));
                myFSM.setEvent(events::RFID_left);

                setUID();
            Serial.println("out");

            }
        }
    }
}

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
Patient_RFID myRFID(mfrc522);
