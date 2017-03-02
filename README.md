# ArduVNA

##General
This project aims to realize a Vector Network Analizer (VNA) with the help of an Arduino Nano.
All including functions are a mix of "found somewere on the web" and "written on my own". Unfortunatly not all sources
where stored during the research. 
Part of the code was taken from the following sources:
- https://github.com/umarsear/Arduino-AD9851-DDS-Direct-Digital-synthesizer-Signal-Generator

##Hardware Used
The following components have been used:
- Arduino Nano
- AD9851
- LCD DEM16216

##ToDo's
Currently open things:
- ensuring a flexible communication protocol over UART
- adding several features to the existant Continuous and Single Sweep
- adding Hardware (receiver hardware) -> to measure Bode-Diagramms etc
- adding transmission protocol of measured values