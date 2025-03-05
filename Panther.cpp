/*
This library provides functions to program the Panther Logger board from electrorex.io.
This library has been tested extensively, but is provided free as is with no guarantees.
Author: Todd R. Miller (electrorex.io)
*/

#include "Arduino.h"
#include <Panther.h>

TwoWire Wire2(&sercom2,4,3);

HDC1080JS tempsensor;

void Panther::begin(){
  Wire.begin();
  Wire2.begin();
  pinPeripheral(4, PIO_SERCOM_ALT);
  pinPeripheral(3, PIO_SERCOM_ALT);
  setupMCP();
  pinPeripheral(4, PIO_SERCOM_ALT);
  pinPeripheral(3, PIO_SERCOM_ALT);
}

void Panther::setupMCP(){
  Wire2.beginTransmission(0x20);
  Wire2.write(0x00); // IODIRA register
  Wire2.write(0x00); // set all of port A to outputs
  Wire2.endTransmission();
  Wire2.beginTransmission(0x20);
  Wire2.write(0x01); // IODIRB register
  Wire2.write(0x00); // set all of port B to outputs
  Wire2.endTransmission();
}

//Sets the pin mode of a pin on the GPIO expander
void Panther::mcpMode(int pin, int mode){
  if (pin > 7){
    int pin2 = pin - 8;
    Wire2.beginTransmission(0x20);
    Wire2.write(0x13); //Select B port
    mcpModeB[pin2] = mode;
    int mcpModeBint = 0b10000000*!!mcpModeB[7] + 0b1000000*!!mcpModeB[6] + 0b100000*!!mcpModeB[5] +0b10000*!!mcpModeB[4] +0b1000*!!mcpModeB[3] +0b100*!!mcpModeB[2] + 0b10*!!mcpModeB[1] + !!mcpModeB[0];
    Wire2.write(mcpModeBint);
    Wire2.endTransmission();
  } else {
    Wire2.beginTransmission(0x20);
    Wire2.write(0x12); //Select A port
    mcpModeA[pin] = mode;
    int mcpModeAint = 0b10000000*!!mcpModeA[7] + 0b1000000*!!mcpModeA[6] + 0b100000*!!mcpModeA[5] +0b10000*!!mcpModeA[4] +0b1000*!!mcpModeA[3] +0b100*!!mcpModeA[2] + 0b10*!!mcpModeA[1] + !!mcpModeA[0];
    Wire2.write(mcpModeAint);
    Wire2.endTransmission();
  }
}

//Writes to a pin on the GPIO expander
void Panther::mcpWrite(int pin, int polarity){
  if (pin > 7){
    int pin2 = pin - 8;
    Wire2.beginTransmission(0x20);
    Wire2.write(0x13); //Select B port
    mcpB[pin2] = polarity;
    int mcpBint = 0b10000000*!!mcpB[7] + 0b1000000*!!mcpB[6] + 0b100000*!!mcpB[5] +0b10000*!!mcpB[4] +0b1000*!!mcpB[3] +0b100*!!mcpB[2] + 0b10*!!mcpB[1] + !!mcpB[0];
    Wire2.write(mcpBint);
    Wire2.endTransmission();
  } else {
    Wire2.beginTransmission(0x20);
    Wire2.write(0x12); //Select A port
    mcpA[pin] = polarity;
    int mcpAint = 0b10000000*!!mcpA[7] + 0b1000000*!!mcpA[6] + 0b100000*!!mcpA[5] +0b10000*!!mcpA[4] +0b1000*!!mcpA[3] +0b100*!!mcpA[2] + 0b10*!!mcpA[1] + !!mcpA[0];
    Wire2.write(mcpAint);
    Wire2.endTransmission();
  }
}

//Turn on or off one of the four LEDs on the Panther Logger board
//LEDs are numbered 1 through 4
void Panther::LED(int LED, int Polarity){
  if (LED == 1){
    pinMode(13,OUTPUT);
    digitalWrite(13,Polarity);
  } else if (LED == 2){
    mcpMode(8,OUTPUT);
    mcpWrite(8,Polarity);
  } else if (LED == 3){
    mcpMode(9,OUTPUT);
    mcpWrite(9,Polarity);
  } else if (LED == 4){
    mcpMode(10,OUTPUT);
    mcpWrite(10,Polarity);
  }
}

//Set all LEDs to on or off (HIGH or LOW)
void Panther::LEDs(int Polarity){
  mcpMode(10,OUTPUT);
  digitalWrite(10,Polarity);
  mcpMode(8,OUTPUT);
  mcpWrite(8,Polarity);
  mcpMode(9,OUTPUT);
  mcpWrite(9,Polarity);
  mcpMode(10,OUTPUT);
  mcpWrite(10,Polarity);
}

//Turn on or off (HIGH or LOW) the 3.3V power supply
void Panther::set3v3(int Polarity){
  mcpMode(4,OUTPUT);
  mcpWrite(4,Polarity);
}

//Turn on or off (HIGH or LOW) the 12V power supply
void Panther::set12v(int Polarity){
  mcpMode(7,OUTPUT);
  mcpWrite(7,Polarity);
}

//Read the temperature sensor on the board (returns a float)
float Panther::pTemp(){
  tempsensor.readTempHumid();
  return(tempsensor.getTemp());
}

//Read the humidity sensor on the board (returns a float)
float Panther::pHumid(){
  tempsensor.readTempHumid();
  return(tempsensor.getRelativeHumidity());
}

//Read voltage on an analog pin (returns a float)
float Panther::Volts(int pin) {                                                                          
  analogReadResolution(12);                                                                         
  float mvolts = analogRead(pin); 
  mvolts *= 2;
  mvolts *= (3.3 / 4096);
  mvolts *= 1000;
  return mvolts;
}

//Read battery voltage on the Panther Logger (returns a float)                                                                                                    
float Panther::bat() {
  return(Volts(A4)/1000);                                                                        
}

//Select the serial port to use on the UART multiplexer on the Panther Logger 
//Run this prior to attempting communications on one of the RS232 ports, the open UART port or with the LoRa modem
//Port 0 = LoRa
//Port 1 = RS232-1
//Port 2 = RS232-2
//Port 3 = Open UART
void Panther::selectSerial2(int port){
  switch (port) {
    case 0:
    mcpMode(11,OUTPUT); 
    mcpWrite(11,LOW); //E
    delay(100);
    mcpMode(12,OUTPUT); 
    mcpWrite(12,LOW); //S0
    delay(100);
    mcpMode(13,OUTPUT);
    mcpWrite(13,LOW); //S1
    delay(100);
      break;
    case 1:
    mcpMode(11,OUTPUT); 
    mcpWrite(11,LOW); //E
    delay(100);
    mcpMode(12,OUTPUT); 
    mcpWrite(12,HIGH); //S0
    delay(100);
    mcpMode(13,OUTPUT);
    mcpWrite(13,LOW); //S1
    delay(100);
      break;
    case 2:
    mcpMode(11,OUTPUT); 
    mcpWrite(11,LOW); //E
    delay(100);
    mcpMode(12,OUTPUT); 
    mcpWrite(12,LOW); //S0
    delay(100);
    mcpMode(13,OUTPUT);
    mcpWrite(13,HIGH); //S1
    delay(100);
      break;
    case 3:
    mcpMode(11,OUTPUT); 
    mcpWrite(11,LOW); //E
    delay(100);
    mcpMode(12,OUTPUT); 
    mcpWrite(12,HIGH); //S0
    delay(100);
    mcpMode(13,OUTPUT);
    mcpWrite(13,HIGH); //S1
    delay(100);
  }
}
