/**
 *        Author:         danboe90
 *        Date:           05-03-2017
 *        Version:        1.0.0
 *        Description:    This file holds functions for controlling an AD8302 with an Arduino Nano.
 */


/************************************************** PINNING **************************************************/
//
//
//       ________________________ _________________________
//      |       Arduino (Pins)   |        AD8302 (Pins)    |
//      |________________________|_________________________|
//      |          +5V           |         +V              |
//      |          GND           |         GND             |
//      |          A1            |         PH              |
//      |          A0            |         PWR             |
//      |          nc            |         VREF            |
//      |________________________|_________________________|
// 
// 



/**
 *    @brief      Reading values from the ADC. Adaptation to full scale is done and stored the final value in the 
 *                ***Final-Variables.
 */
void mag_ph_ADC()
{
  // fetch value from ADC
  unsigned int adcmag = analogRead(PWR_IN);
  unsigned int adcphs = analogRead(PH_IN);

  //adaptation of the Value
  magFinal = (60.0 /1024) * adcmag -60.0;
  phsFinal = (180/1024) * adcphs;
}



void initAD8302()
{
  // setting pins for AD8302 Module
  pinMode (PWR_IN, INPUT);
  pinMode (PH_IN, INPUT);
}

