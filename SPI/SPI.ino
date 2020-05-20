#include <SPI.h>

void setup (void)
  {
  digitalWrite(SS, HIGH);  // ensure SS stays high
  SPI.begin ();
  } // end of setup

void loop (void)
  {
  byte c;

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "Fab" ; c = *p; p++)
    SPI.transfer (c);

  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (100);
  } // end of loop
