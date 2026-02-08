#Arduino Industrial Automation System

##Overview
This project presents an industrial automation system implemented using Arduino UNO as a low-cost alternative to traditional PLC-based systems.
The system monitors temperature, humidity, and gas concentration and performs real-time control actions based on predefined threshold values.
##System Objectives
-	Replace PLC with a low-cost microcontroller solution
-	Monitor environmental conditions in real time
-	Trigger alarms and actuators when safety thresholds are exceeded
-	Implement a fail-safe interrupt-based control mechanism
##Hardware Components
-	Arduino UNO
-	DHT22 Temperature & Humidity Sensor
-	MQ-5 Gas Sensor
-	16x2 LCD Display (LM016L)
-	Relay Module (5V)
-	DC Fan (12V)
-	Solenoid Valve (12V)
-	Buzzer
-	NPN Transistor (2N3904)
-	N-Channel MOSFET (IRLZ44N)
-	External Interrupt Button
##System Features
-	Interrupt-based system ON/OFF control
-	Temperature threshold monitoring and fan activation
-	Humidity warning display on LCD
-	Gas leakage detection with solenoid valve control
-	Real-time LCD data visualization
-	Non-blocking timing using millis()
-	Safe shutdown of all actuators on interrupt

##Control Logic Summary
1.	System starts in standby mode
2.	External interrupt activates the system
3.	Temperature and humidity are read from DHT22
4.	Gas concentration is calculated from MQ-5 sensor
5.	Actuators respond according to threshold conditions
6.	LCD displays sensor data cyclically
7.	External interrupt safely turns the system OFF at any time
8.	
##Software & Tools
-	Arduino IDE
-	Proteus (for simulation and validation)

##Author
Embedded Systems & Mechatronics Engineering Student
Industrial Automation Project

##License
This project is intended for educational purposes.

##Notes
-	The system was tested in a simulation environment, therefore sensor readings match displayed values exactly.
-	In real hardware applications, minor measurement errors are expected due to noise and sensor tolerances.
-	The Proteus simulation file is intentionally not included to keep the repository clean and focused on code quality.


##References
[1] Altungül S. ve Erdinç F., SIEMENS S7-1200 ile PLC Programlama & Otomasyon
[2] Dr.Ozan Vahit Altınpınar project .
[3] Röle Datasheet: https://datasheet4u.com/datasheet/HLS/HLS-14F3L-909859
[4] MQ-5 Datasheet: https://www.winsen-sensor.com/d/files/MQ-5.pdf 
[5] 2N3904 General Purpose Transistor, Datasheet.
https://www.alldatasheet.com/html-pdf/11470/ONSEMI/2N3904/180/1/2N3904.html
[6]  IRLZ44N Logic Level N-Channel MOSFET, Datasheet.
IIRLZ44N datasheet(1/2 Pages) ISC | N-Channel MOSFET Transistor  



