# ArduVNA

##General
This project aims to realize a Vector Network Analizer (VNA) with the help of an Arduino Nano.
All including functions are a mix of *"found somewere on the web"* and *"written on my own"*. 

##Hardware Used
The following components have been used:
- [x] Arduino Nano
- [x] AD9851
- [x] LCD DEM16216
- [x] AD8302

##Hardware Pinning


|        Arduino (Pins)  |       AD9851 (Pins)     |
| ---------------------- | ----------------------- |
|           D2           |          FQ_UD          |
|           D3           |          WCLK           |
|           D4           |          D7  (DATA)     |
|           GND          |          GND            |
|           +5V          |          Vcc            |
AD9851 requires 3 digital IO Pins to set the output-frequency.


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
There are several other displays that support the same pinning.


|		Arduino (Pins)	 |			AD8302 (Pins)   |
| ---------------------- | ------------------------ |
|			+5V			 |			+V			    |
|			GND			 |			GND			    |
|			A1			 |			PH				|
|			nc			 |			VREF			|
|			A0			 |			PWR				|


##Usage
Open *.ino with the Arduino IDE.
Flash the Project onto the Arduino Nano.
Send ```<mode,f_start,f_stop,steps>\n``` to the Ardunio via UART.
Alternativly it is posible to just configure on output-frequency with ```<mode,frequency>\n```.

###Mode (mode)
| mode | 		Explanation 	 |
| ---- | ----------------------- |
|  c   |	continuous SweepMode |
|  s   |    single Sweep Mode	 |
|  f   |    single frequency Mode|

###Start Frequency (f_start)
**type:** unsigned long 

###Stop Frequency (f_stop)
**type:** unsigned long

###Steps (steps)
**type:** unsigned long  
Defines the amout of steps the sweep takes to get from f_start to f_stop.  
This value cant be higher than ```f_stop - f_start```


##ToDo's
Currently open things:
- [x] setup pinmaping for AD8302
- [x] Upload Source Code for the Arduino
- [x] Add frequency dependen delays to obtain valid meassuring values (relevant for f<10MHz)
- [ ] Avoid: steps > f_stop - f_start
- [x] Avoid: receive from UART mode != ('c' | 's' | 'f')
- [x] Add time-measuring for one sweep
- [ ] ensuring a flexible communication protocol over UART
- [ ] adding several features to the existant Continuous and Single Sweep
- [x] adding Hardware (receiver hardware) -> to measure Bode-Diagramms etc
- [ ] adding transmission protocol of measured values


## References and Sources
Unfortunatly not all sources where stored during the research. 
Part of the code was taken from the following sources:
- https://github.com/umarsear/Arduino-AD9851-DDS-Direct-Digital-synthesizer-Signal-Generator

Other Information was taken from:
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/DDS_AD9830_3.jpg
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/ad9850_1%20manual.pdf