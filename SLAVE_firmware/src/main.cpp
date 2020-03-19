#include "main.h"


ISR(WDT_vect)
{
  //tact::timerCount(); // Very important to use this version when not using simultaneous presses (changes long press period)
  //Serial.println((int)&selectPin.hold_ptr, HEX);
}

/*
//example use of timer 1
ISR(TIMER1_COMPA_vect)
{
  TCNT1 = 0;
  PORTD ^= (1 << timerLedPin);
  selectPin.debounce(); // Debounce is useful when not sleeping (i.e. when an timer ISR can handle it)
}
*/

void setup()
{
  Serial.begin(9600); //Serial.begin(38400); // Speed to comm with HC05
  BTserial.begin(9600);
  //Serial.println("fuck you");

  //pinMode(ledPin, OUTPUT);
  //pinMode(LedPin2, OUTPUT);
  //pinMode(LedPin3, OUTPUT);


  WDT_setup();
  //timer1_setup();
  sleep_setup();
  //lcd_setup();
  tof_setup();
  myFSM.init();
}

void loop()
{

  myFSM.doState();

  read_BT_events();

  //shift_reg_snapshot();
  //buttons_shift.data = transfer_shift_reg_data();



  //activate_sleep();
}
