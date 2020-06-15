//Transmitter Code
// https://www.circuitbasics.com/wired-communication-between-two-arduinos/

 #include <SoftwareSerial.h>
 SoftwareSerial link(2, 3); // Rx, Tx
 byte lm35Pin = A0;
 float lm35V = 0;
 float tempC = 0;
 byte greenLED = 12;
 char text[20] ;
 char charVal[6];
  ////////////////////////////////////
  void setup() 
  {
    link.begin(9600);
    Serial.begin(9600);
    pinMode(greenLED, OUTPUT);
  }
  ///////////////////////////////////////////
  void loop()  
  {
   strcat(text, "Temp is: "); //append to empty string
   digitalWrite(greenLED, HIGH);
   delay(10);
   digitalWrite(greenLED, LOW);
   lm35V = analogRead(lm35Pin);
   tempC = (lm35V/1023) * 500;
   //this is a float we want it as a c-string:
   dtostrf(tempC, 5, 1, charVal);  
   //5 is min width, 1 is precision; float value is copied to charVal
   strcat(text, charVal); //append the value
   text[16] = 0; //terminate the cstring
   strcat(text, "C");  //append a C
   Serial.println(text); //print to local screen for debug
   link.println(text);
      
   delay(200);
  }
  ////////////////////////////////////////////////////
