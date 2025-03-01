
![ElectroRexLogo_Github](https://github.com/user-attachments/assets/c46993d4-a2e9-4d48-a9d2-b3c85fddbec2)

# Panther Library


![PantherLogger2_GithubB](https://github.com/user-attachments/assets/c530cc08-f9d0-4673-95eb-7aa9acbb40bd)

This library is used to program the Electrorex Panther Logger 

[Electrorex Panther Logger](https://electrorex.io/shop/ols/products/electrorex-iot-loggerone)

A list of functions in this library is listed below.

For further documentation and tutorials see the [Electrorex Learning Center](https://electrorex.io/pantherlogger-tutorials) 

The Panther library provides functions to program the Panther Logger board including setting up serial ports, turning on switched voltage rails, turning on indicator LEDs and reading the onboard sensors. Instantiate the class with: 
	
Panther ptr;

And then precede all functions in this class with ptr, for example:
	
ptr.begin();

## begin
Sets up the Panther Logger hardware
Inputs: None
Outputs: None
Usage:  ptr.begin();

## setupMCP
Sets up the GPIO expander
Inputs: None
Outputs: None
Usage: ptr.setupMCP

## mcpMode
Sets the pin mode of one of the GPIO expander pins
Inputs:
Pin number
Function either INPUT or OUTPUT
Outputs: None
Usage: Mode(3,OUTPUT);

## mcpWrite
Writes the polarity of one of the GPIO expander pins
Inputs:
Pin number
Polarity either HIGH or LOW
Outputs: None
Example:
Write(3,HIGH);

## LED
Turns on (HIGH) or off (LOW) an LED on the Panther Logger board
Inputs: LED number as integer, Polarity (either HIGH or LOW)
Outputs: None
Example: ptr.LED(1, HIGH);

LEDs
Turns on (HIGH) or off (LOW) all LEDs simultaneously
Inputs: Polarity, either HIGH or LOW
Outputs: None
Example: LEDs(HIGH);

## set3v3
Turn on or off the switched 3.3V power rail
Inputs: Polarity, either HIGH or LOW
Outputs: None
Usage: ptr.set3v3(HIGH); //Turns on the switched 3.3V rail

## set12v
Turn on (HIGH) or off (LOW) the switched 12V power rail
Inputs: Polarity, either HIGH or LOW
Outputs: None
Usage: ptr.set12v(HIGH);

## pTemp
Read the temperature sensor on the Panther Logger board
Inputs: None
Outputs: float value
Usage: ptr.pTemp();

## pHumid
Read the humidity sensor on the Panther Logger board
Input: None
Outputs: float value
Usage: ptr.pHumid();

## Volts
Read voltage on an analog pin
Inputs: analog pin to read 
Outputs: float value
Usage: ptr.Volts(A0);

## Bat
Read battery voltage
Inputs: None
Outputs: float value
Usage: ptr.bat();

## selectSerial2
Select the serial port to use on the UART multiplexer on the Panther Logger 
Run this prior to attempting communications on one of the RS232 ports, the open UART port or with the LoRa modem
Port 0 = LoRa, Port 1 = RS232-1, Port 2 = RS232-2, Port 3 = Open UART
Inputs: port number
Outputs: none
Usage: ptr.selectSerial2(1);


