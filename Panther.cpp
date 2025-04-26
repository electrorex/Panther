/*
This library provides functions to program the Panther Logger board from electrorex.io.
This library has been tested extensively, but is provided free as is with no guarantees.
Author: Todd R. Miller (electrorex.io)
*/

#include <Panther.h>
#define MCP23017_I2C_ADDRESS 0x20 
TwoWire ptrWire(&sercom2,4,3);
MCP23017 mcp = MCP23017(MCP23017_I2C_ADDRESS,ptrWire);  

ClosedCube_HDC1080 hdc1080;

void Panther::begin(){
  Wire.begin();
  ptrWire.begin();
  pinPeripheral(4, PIO_SERCOM_ALT);
  pinPeripheral(3, PIO_SERCOM_ALT);
  mcp.init();
  hdc1080.begin(0x40);
  hdc1080.setResolution(HDC1080_RESOLUTION_11BIT, HDC1080_RESOLUTION_14BIT);
}

//Sets the pin mode of a pin on the GPIO expander
void Panther::Mode(int pin, int mode){
    mcp.pinMode(pin, mode);
}

//Writes to a pin on the GPIO expander
void Panther::Write(int pin, int polarity){
    mcp.digitalWrite(pin, polarity);
}

//Turn on or off one of the four LEDs on the Panther Logger board
//LEDs are numbered 1 through 4
void Panther::LED(int LED, int Polarity){
  switch (LED) {
    case 1:
    pinMode(13,OUTPUT);
    digitalWrite(13,Polarity);
    break;
    case 2:
    mcp.pinMode(8,OUTPUT);
    mcp.digitalWrite(8,Polarity);
    break;
    case 3:
    mcp.pinMode(9,OUTPUT);
    mcp.digitalWrite(9,Polarity);
    break;
    case 4:
    mcp.pinMode(10,OUTPUT);
    mcp.digitalWrite(10,Polarity);
  }
}

//Set all LEDs to on or off (HIGH or LOW)
void Panther::LEDs(int Polarity){
  digitalWrite(13,Polarity);
  mcp.digitalWrite(8,Polarity);
  mcp.digitalWrite(9,Polarity);
  mcp.digitalWrite(10,Polarity);
}

//Turn on or off (HIGH or LOW) the 3.3V power supply
void Panther::set3v3(int Polarity){
    mcp.pinMode(4,OUTPUT);
    mcp.digitalWrite(4,Polarity);
}

//Turn on or off (HIGH or LOW) the 12V power supply
void Panther::set12v(int Polarity){
    mcp.pinMode(7, OUTPUT);
    mcp.digitalWrite(7,Polarity);
}

//Read the temperature sensor on the board (returns a float)
float Panther::pTemp(){
  return(hdc1080.readTemperature());
}

//Read the humidity sensor on the board (returns a float)
float Panther::pHumid(){
  return(hdc1080.readHumidity());
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
    mcp.pinMode(11, OUTPUT);
    mcp.digitalWrite(11,LOW); //E
    delay(10);
    mcp.pinMode(12, OUTPUT);
    mcp.digitalWrite(12,LOW); //S0
    delay(10);
    mcp.pinMode(13, OUTPUT);
    mcp.digitalWrite(13,LOW); //S1
    delay(10);
      break;
    case 1:
    mcp.pinMode(11, OUTPUT);
    mcp.digitalWrite(11,LOW); //E
    delay(10);
    mcp.pinMode(12, OUTPUT);
    mcp.digitalWrite(12,HIGH); //S0
    delay(10);
    mcp.pinMode(13, OUTPUT);
    mcp.digitalWrite(13,LOW); //S1
    delay(10);
      break;
    case 2:
    mcp.pinMode(11, OUTPUT);
    mcp.digitalWrite(11,LOW); //E
    delay(10);
    mcp.pinMode(12, OUTPUT);
    mcp.digitalWrite(12,LOW); //S0
    delay(10);
    mcp.pinMode(13, OUTPUT);
    mcp.digitalWrite(13,HIGH); //S1
    delay(10);
      break;
    case 3:
    mcp.pinMode(11, OUTPUT);
    mcp.digitalWrite(11,LOW); //E
    delay(10);
    mcp.pinMode(12, OUTPUT);
    mcp.digitalWrite(12,HIGH); //S0
    delay(10);
    mcp.pinMode(13, OUTPUT);
    mcp.digitalWrite(13,HIGH); //S1
    delay(10);
  }
}

