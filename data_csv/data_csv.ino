// Arduino Data CSV
// https://www.circuitbasics.com/logging-arduino-data-to-files-on-a-computer/

#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; 
float QNH = 1024.67; //Change the "1022.67" to your current sea level barometric pressure (https://www.wunderground.com)
const int BMP_address = 0x76;
float pressure;   
float temperature;  
float altimeter; 
//char charRead;
char dataStr[100] = "";
char buffer[7];

void setup(){
  Serial.begin(9600);
  bmp.begin(BMP_address); 
}

void loop(void){
 dataStr[0] = 0; //clean out string
 pressure = bmp.readPressure()/100;  //and convert Pa to hPa
 temperature = bmp.readTemperature();
 altimeter = bmp.readAltitude (QNH); //QNH is local sea level pressure
 //----------------------- using c-type ---------------------------
 //convert floats to string and assemble c-type char string for writing:
 ltoa( millis(),buffer,10); //convert long to charStr
 strcat(dataStr, buffer); //add it to the end
 strcat( dataStr, ", "); //append the delimiter
 
 //dtostrf(floatVal, minimum width, precision, character array);
 dtostrf(pressure, 5, 1, buffer);  //5 is minimum width, 1 is precision; float value is copied onto buff
 strcat( dataStr, buffer); //append the converted float
 strcat( dataStr, ", "); //append the delimiter

 dtostrf(temperature, 5, 1, buffer);  //5 is minimum width, 1 is precision; float value is copied onto buff
 strcat( dataStr, buffer); //append the converted float
 strcat( dataStr, ", "); //append the delimiter

 dtostrf(altimeter, 5, 1, buffer);  //5 is minimum width, 1 is precision; float value is copied onto buff
 strcat( dataStr, buffer); //append the converted float
 strcat( dataStr, 0); //terminate correctly 
 Serial.println(dataStr);
 delay(1000);  
} 
