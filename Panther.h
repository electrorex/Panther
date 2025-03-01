/*
This library provides functions to program the Panther Logger board from electrorex.io.
This library has been tested extensively, but is provided free as is with no guarantees.
Author: Todd R. Miller (electrorex.io)
*/

#ifndef Panther_h
#define Panther_h

#include "Arduino.h"
#include "Wire.h"
#include "wiring_private.h"
#include "HDC1080JS.h"

extern TwoWire Wire2;


class Panther
{
  public:
    void begin();
    void setupMCP();
    void mcpMode(int pin, int mode);
    void mcpWrite(int pin, int polarity);
    int mcpModeB[8] = {0,0,0,0,0,0,0,0};
    int mcpModeA[8] = {0,0,0,0,0,0,0,0};
    int mcpB[8] = {0,0,0,0,0,0,0,0};
    int mcpA[8] = {0,0,0,0,0,0,0,0};
    char result_char[2000]; 
    int Check;
    void LED(int LED, int Polarity);
    void LEDs(int Polarity);
    void set3v3(int Polarity);
    void set12v(int Polarity);
    float pTemp();
    float pHumid();
    float Volts(int pin);
    float bat();
    void selectSerial2(int port);
  private:    
};

#endif
