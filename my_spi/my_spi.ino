// Arduino SPI 
// https://www.circuitbasics.com/how-to-set-up-spi-communication-for-arduino/

#include <SPI.h>

void setup() {
  pinMode(10,OUTPUT); // set SS pin as output pin
  SPI.begin();        // Initialize SPI library
  Serial.begin(9600);
}

void loop() {

  digitalWrite(10, LOW);          // set SS pin connected to MCP4131 to LOW
  
  for(byte wiper_value = 0; wiper_value <= 128; wiper_value++) {

    SPI.transfer(0x00);             // send write command to MCP4131 to write at registry address 0x00
    SPI.transfer(wiper_value);      // send new wiper value

    Serial.println(analogRead(A0)); // read value from analog pin A0 and send to serial
    delay(1000); 
  }

  digitalWrite(10, HIGH);         // set SS pin connected to MCP4131 to HIGH
}
