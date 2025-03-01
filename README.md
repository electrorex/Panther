
![ElectroRexLogo_Github](https://github.com/user-attachments/assets/c46993d4-a2e9-4d48-a9d2-b3c85fddbec2)

# Panther Library


![PantherLogger2_GithubB](https://github.com/user-attachments/assets/c530cc08-f9d0-4673-95eb-7aa9acbb40bd)



This library is used to program the Electrorex Panther Logger 

[Electrorex Panther Logger](https://electrorex.io/shop/ols/products/electrorex-iot-loggerone)

A list of functions in this library is listed below.

For further documentation and tutorials see the [Electrorex Learning Center](https://electrorex.io/pantherlogger-tutorials) 

Panther Class
The Panther Class provides functions to program the Panther Logger board including setting up serial ports, turning on switched voltage rails, turning on indicator LEDs and reading the onboard sensors. Instantiate the class with: 
	
Panther ptr;

And then precede all functions in this class with ptr, for example:
	
ptr.begin();

	begin
	Sets up the Panther Logger hardware
	Inputs: None
	Outputs: None
	Usage:  begin();

	Mode
	Sets the pin mode of one of the GPIO expander pins
	Inputs:
1.	Pin number
2.	Function either INPUT or OUTPUT
	Outputs: None
	Usage: Mode(3,OUTPUT);

	Write
	Writes the polarity of one of the GPIO expander pins
	Inputs:
1.	Pin number
2.	Polarity either HIGH or LOW
	Outputs: None
	Example:
Write(3,HIGH);

	LED1
	Turns on (HIGH) or off (LOW) LED number 1
	Inputs:
1.	Polarity, either HIGH or LOW
	Outputs: None
	Example:
LED1(HIGH);

	LED2
	Turns on (HIGH) or off (LOW) LED number 2
	Inputs:
1.	Polarity, either HIGH or LOW
	Outputs: None
	Example:
LED2(HIGH);

	LED3
	Turns on (HIGH) or off (LOW) LED number 3
	Inputs:
1.	Polarity, either HIGH or LOW
	Outputs: None
	Example:
LED3(HIGH);

	LED4
	Turns on (HIGH) or off (LOW) LED number 4
	Inputs:
1.	Polarity, either HIGH or LOW
	Outputs: None
	Example:
LED4(HIGH)

	LEDs
	Turns on (HIGH) or off (LOW) all LEDs simultaneously
	Inputs:
1.	Polarity, either HIGH or LOW
	Outputs: None
	Example:
LEDs(HIGH);

	s3v3
	Turn on or off the switched 3.3V power rail
	Inputs:
1.	Polarity, either HIGH or LOW
	Outputs: None
	Usage: s3v3(HIGH); //Turns on the switched 3.3V rail

	s12v
	Turn on (HIGH) or off (LOW) the switched 12V power rail
	Inputs
1.	Polarity, either HIGH or LOW
	Outputs: None
	Usage: s12v(HIGH);

	pTemp
	Read the temperature sensor on the Panther Logger board
	Inputs: None
	Outputs: float value
	Usage: pTemp();

	pHumid
	Read the humidity sensor on the Panther Logger board
	Input: None
	Outputs: float value
	Usage: pHumid();

	Bat
	Read battery voltage
	Inputs: None
	Outputs: float value
	Usage: Bat();

