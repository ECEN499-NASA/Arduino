//nrf2401 transmitter:
// https://www.circuitbasics.com/wireless-communication-between-two-arduinos/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_BMP280.h>
RF24 nrf(9, 8);  // CE, CSN
Adafruit_BMP280 bmp; 

const byte linkAddress[6] = "link1";
float QNH = 1022.67; //Change the "1022.67" to your current sea level barrometric pressure (https://www.wunderground.com)
const int BMP_address = 0x76;

float pressure;   
float temperature;  
float altimeter; 
float data[3];
char charVal[17];
////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  Serial.println("BMP280/NRF24L01 link");
  nrf.begin();   
  bmp.begin(BMP_address); 
  nrf.openWritingPipe(linkAddress);  //set the address 
  //nrf.setPALevel(RF24_PA_LOW);   //keep tx level low to stop psu noise, can remove this but then put in decoupling caps
  // Options are: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,  RF24_PA_HIGH=0dBm.
  nrf.setPALevel(RF24_PA_HIGH); 
  nrf.stopListening();  //act as a transmitter
}
///////////////////////////////////////////////////
void loop()
{  
 pressure = bmp.readPressure()/100;  //and conv Pa to hPa
 temperature = bmp.readTemperature();
 altimeter = bmp.readAltitude (QNH); //QNH is local sea lev pressure
  
 data[0] = pressure;
 data[1] = temperature;
 data[2] = altimeter;
 //----- display on local monitor: ------------
 Serial.print(data[0]); Serial.print("hPa  ");
 Serial.print(data[1]); 
 Serial.write(0xC2);  //send degree symbol
 Serial.write(0xB0);  //send degree symbol
 Serial.print("C   ");  
 Serial.print(data[2]); Serial.println("m");
 //---------------------------------------------
 
  nrf.write(data, sizeof(data)); //spit out the data array
  
  delay(300);
}
/////////////////////////////////////////////////
