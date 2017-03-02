# ArduVNA

##General
This project aims to realize a Vector Network Analizer (VNA) with the help of an Arduino Nano.
All including functions are a mix of "found somewere on the web" and "written on my own". Unfortunatly not all sources
where stored during the research. 
Part of the code was taken from the following sources:
- https://github.com/umarsear/Arduino-AD9851-DDS-Direct-Digital-synthesizer-Signal-Generator

Other Information was taken from:
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/DDS_AD9830_3.jpg
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/
- http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/ad9850_1%20manual.pdf

##Hardware Used
The following components have been used:
- Arduino Nano
- AD9851
- LCD DEM16216

##Hardware Pinning
 ________________________ _________________________
|        Arduino (Pins)  |       AD9851 (Pins)     |
|________________________|_________________________|
|           D2           |          FQ_UD          |
|           D3           |          WCLK           |
|           D4           |          D7  (DATA)     |
|           GND          |          GND            |
|           +5V          |          Vcc            |
|________________________|_________________________|

 ________________________ _________________________
|       Arduino (Pins)   |        LCD (Pins)       |
|________________________|_________________________|
|           D7           |          4       (RS)   |
|           D8           |          6       (E)    |
|           D9           |          11      (DB4)  |
|           D10          |          12      (DB5)  |
|           D11          |          13      (DB6)  |
|           D12          |          14      (DB7)  |
|           +5V          |          2       (VDD)  |
|           GND          |          1, 3, 5 (GND)  |
|________________________|_________________________|






##ToDo's
Currently open things:
- ensuring a flexible communication protocol over UART
- adding several features to the existant Continuous and Single Sweep
- adding Hardware (receiver hardware) -> to measure Bode-Diagramms etc
- adding transmission protocol of measured values