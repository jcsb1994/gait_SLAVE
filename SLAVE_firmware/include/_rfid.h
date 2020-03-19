#ifndef RFID_H
#define RFID_H

#include "main.h"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
uint8_t activeID[4];

void RFID_setup()
{
    SPI.begin();        // Initiate  SPI bus
    mfrc522.PCD_Init(); // Initiate MFRC522
}

void isPatientNear()
{
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) // If card is read, read the active
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            activeID[i] = mfrc522.uid.uidByte[i];
        }
    }
}

// receive an hex value and store it as activeID

void sendActiveID() //needs to send a flag that mentions we are talking about the RFID #, then the data.
{
    for (uint8_t i = 0; i < 4; i++)
    {
        Serial.print(activeID[1]);
    }
}

// Check for available data and 

#endif