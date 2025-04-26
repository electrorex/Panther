/*
This library provides functions to program the Panther Logger board from electrorex.io.
This library has been tested extensively, but is provided free as is with no guarantees.
Author: Todd R. Miller (electrorex.io)
*/

#ifndef Panther_h
#define Panther_h

#include "Arduino.h"
#include "ClosedCube_HDC1080.h"
#include <Panther.h>
#include "Wire.h"
#include "wiring_private.h"
#include <MCP23017.h>

class Panther
{
  public:
    void begin();
    void Mode(int pin, int mode);
    void Write(int pin, int polarity);
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
};

#endif
