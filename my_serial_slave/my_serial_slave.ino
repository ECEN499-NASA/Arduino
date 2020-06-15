 //Receiver code
// https://www.circuitbasics.com/wired-communication-between-two-arduinos/
 
 #include <SoftwareSerial.h>
 SoftwareSerial link(2, 3); // Rx, Tx
  
  byte greenLED = 12;
  char cString[20];
  byte chPos = 0;
  byte ch = 0;
  char dataStr[6];
  ////////////////////////////////////////////
  void setup() 
  {
    link.begin(9600); //setup software serial
    Serial.begin(9600);    //setup serial monitor
    pinMode(greenLED, OUTPUT);
  }
  ////////////////////////////////////////////
  void loop()  
  {  
 // if (link.available())
 //     Serial.write(link.read());
 // if (Serial.available())
 //     link.write(Serial.read());  
   
   
   while(link.available())
   {
    //read incoming char by char:
     ch = link.read();
     cString[chPos] = ch;
     chPos++;     
     
   digitalWrite(greenLED, HIGH); //flash led to show data is arriving
   delay(10);
   digitalWrite(greenLED, LOW);
   }
   cString[chPos] = 0; //terminate cString
   chPos = 0;
   
   Serial.print(cString);
    
  }
  //////////////////////////////////////////////////////
