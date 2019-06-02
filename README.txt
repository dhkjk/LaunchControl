USC Racing Launch Control 2018

Rotary Encoder manual:
http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/keyes-ky-040-arduino-rotary-encoder-user-manual/
LCD tutorial:
http://www.thomasclausen.net/en/walking-through-the-1602-lcd-keypad-shield-for-arduino/

Launch Control Parts:
-Arduino Uno
-Three LED
-Rotary Encoder
-LCD Shield

Port Assignments 

Output:
D 11 = Rev Limiter (Signal to ECU)
A 2 = LED lights
A 3 = LED lights
A 4 = LED lights

Input:
D 2 = Rotary Encoder Port A(clk)
D 3 = Rotary Encoder Port B(Dt)
D 4 = LCD
D 5 = LCD
D 6 = LCD
D 7 = LCD
D 8 = LCD
D 9 = LCD
D 12 = Clutch Switch Sensor
D 13 = Launch Control Switch

*There are 5 states in this Launch Control: IDLE; LaunchRdy, LaunchON; Sustain; OFF; Wait
	LaunchRdy and LaunchON are in the same state

	IDLE:
		Wait for the Launch Control Switch to be switched on
		Can set the Launch Control Delay still
	
	LaunchRdy/LaunchON:
		LaunchRdy-The state is in LaunchRdy when the Launch Control Switch is switched on but the Clutch Switch is NOT initiated
			(Can set the Launch Control Delay still)
		LaunchON-Launch Control Switch is switched on and the Clutch Switch IS initiated

	Sustain:
		Keep the Launch Control On
	
	OFF:
		Turn off the Launch Control
	
	Wait:
		Wait for the Launch Control Switch to be turned off