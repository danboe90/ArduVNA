# ArduVNA

##General
This project aims to realize a Vector Network Analizer (VNA) with the help of an Arduino Nano.
All including functions are a mix of "found somewere on the web" and "written on my own". 
Unfortunatly not all sources where stored during the research. 
Part of the code was taken from the following sources:
- https://github.com/umarsear/Arduino-AD9851-DDS-Direct-Digital-synthesizer-Signal-Generator

Other Information was taken from:
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/DDS_AD9830_3.jpg
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/ad9850_1%20manual.pdf

##Hardware Used
The following components have been used:
- [x] Arduino Nano
- [x] AD9851
- [x] LCD DEM16216
- [ ] AD8302

##Hardware Pinning


|        Arduino (Pins)  |       AD9851 (Pins)     |
| ---------------------- | ----------------------- |
|           D2           |          FQ_UD          |
|           D3           |          WCLK           |
|           D4           |          D7  (DATA)     |
|           GND          |          GND            |
|           +5V          |          Vcc            |



|       Arduino (Pins)   |        LCD (Pins)       |
| ---------------------- | ----------------------- |
|           D7           |          4       (RS)   |
|           D8           |          6       (E)    |
|           D9           |          11      (DB4)  |
|           D10          |          12      (DB5)  |
|           D11          |          13      (DB6)  |
|           D12          |          14      (DB7)  |
|           +5V          |          2       (VDD)  |
|           GND          |          1, 3, 5 (GND)  |


|		Arduino (Pins)	 |			AD8302 (Pins)   |
| ---------------------- | ------------------------ |
|						 |			+V			    |
|						 |			GND			    |
|						 |			PH				|
|						 |			VREF			|
|						 |			PWR				|


##Usage
Open *.ino with the Arduino IDE.
Flash the Project onto the Arduino Nano.
Send '<mode,f_start,f_stop,steps>'\n to the Ardunio via UART.

###Mode (mode)
| mode | Explanation |
| ---- | ----------- |
|  c   |	continuous SweepMode |
|  s   |    single Sweep Mode

###Start Frequency (f_start)
type: unsigned long 

###Stop Frequency (f_stop)
type: unsigned long


##ToDo's
Currently open things:
- [x] setup pinmap for AD8302
- [ ] Upload Source Code for the Arduino
- [ ] ensuring a flexible communication protocol over UART
- [ ] adding several features to the existant Continuous and Single Sweep
- [ ] adding Hardware (receiver hardware) -> to measure Bode-Diagramms etc
- [ ] adding transmission protocol of measured values