#ifndef _HC05_H
#define _HC05_H

#include <SoftwareSerial.h>
extern SoftwareSerial BTserial; // SRX | STX

#include "main.h"

// Bluetooth messages
#define ENTER_MEASURING_MODE_MESSAGE 'a' // 97 // Request to turn On RFID
#define RFID_RECOGNIZED_MESSAGE      'b'    // Request to turn on VL53

#define TIME_MEASURED_MESSAGE         'c'    // Slave sends signal to save time to Master. must be followed by a RF ID
#define TEST_RESULT_MILLISEC_MESSAGE 'd'    

void testBT();

void read_BT_events();

void send_byte_BT(unsigned char message);

#endif