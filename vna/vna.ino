/**
 *        Author:         danboe90
 *        Date:           28-02-2017
 *        Version:        1.0.0
 *        Description:    This file holds functions for controlling an AD9851 and AD8302 with an Arduino Nano.
 */






/************************************************** PINNING **************************************************/
//
//
//
//
//       ________________________ _________________________
//      |       Arduino (Pins)   |        LCD (Pins)       |
//      |________________________|_________________________|
//      |           D7           |          4       (RS)   |
//      |           D8           |          6       (E)    |
//      |           D9           |          11      (DB4)  |
//      |           D10          |          12      (DB5)  |
//      |           D11          |          13      (DB6)  |
//      |           D12          |          14      (DB7)  |
//      |           +5V          |          2       (VDD)  |
//      |           GND          |          1, 3, 5 (GND)  |
//      |________________________|_________________________|
// 
// 









/************************************************** DEFINES **************************************************/
#define FQ_UD                                       2               // Arduino Pin (D2)
#define DDS_CLOCK                                   180000000
#define CLOCK                                       3               // Arduino Pin (D3)
#define DATA                                        4               // Arduino Pin (D4)

#define PWR_IN                                      A0              // Arduino Pin (A0)
#define PH_IN                                       A1              // Arduino Pin (A1)


/************************************************** INCLUDES **************************************************/
#include <LiquidCrystal.h>




/************************************************** GLOBALS **************************************************/
// for the Serial IF
unsigned long   start_frequency   = 0;        // start frequency
unsigned long   stop_frequency    = 0;        // stop frequency
unsigned long   step_frequency    = 0;        // amount of steps between start and stop frequency
unsigned long   single_frequency  = 0;        // holds a single frequency value
String          inString;                     // holds received message from UART
boolean         stringComplete    = false;    // defines if received message from UART has ended and was terminated with '\n'
char            mode;                         // defines the mode received from the GUI

// Generation Modes - are set depending on content of 'char mode'
boolean         continuousSweep;               // true if in continuous mode 
boolean         singleSweep;                   // true if in single sweep mode

// for the LCD
LiquidCrystal   lcd(7,8,9,10,11,12);          // Pinning listed above for the Display


// for the ADC
float           magFinal;
int             phsFinal;










/************************************************** SETUP **************************************************/
/**
 *    @brief    setting up the Connections to the AD9851 Module and the Serial Interface
 */
void setup()
{

  // Serial set to 9600 Baud 8N1
  Serial.begin(115200);

  // Setup-Code for the LCD-Display
  lcd.begin(16, 2);
  
  // setting Pins for the AD9851 Module
  pinMode (DATA, OUTPUT);         // sets pin 10 as OUPUT
  pinMode (CLOCK, OUTPUT);        // sets pin 9 as OUTPUT
  pinMode (FQ_UD, OUTPUT);        // sets pin 8 as OUTPUT

  // setting pins for AD8302 Module
  pinMode (PWR_IN, INPUT);
  pinMode (PH_IN, INPUT);

  // save some space for the incoming messages from UART
  inString.reserve(200);
}











/************************************************** MAINLOOP **************************************************/

/**
 *    @brief    Wait until data is available. Then set the new values obtained 
 *              as new frequency for the AD9851 Module
 */
void loop()
{
  unsigned long diff_frequency = (stop_frequency - start_frequency) / step_frequency;

  /**************************************************/
  /*              Continuous Sweep Mode             */ 
  /**************************************************/
  if(continuousSweep)
  {
    for(unsigned long i=start_frequency; i<=stop_frequency ; i=i+diff_frequency)
    {
      updateFrequency(i);
    }
  }


  /**************************************************/
  /*                 Single Sweep Mode              */ 
  /**************************************************/
  else if(singleSweep)
  {
    // set all frequencies ones. Then set the AD9851 Module to output 0Hz
    // by setting singleSweep to false at the end of the for-loop another frequency sweep is avoided
    unsigned long timestamp = micros();
    for(unsigned long i=start_frequency; i<=stop_frequency ; i=i+diff_frequency)
    {
      updateFrequency(i);               // setting frequency on the DDS
      if(i<=10000000)
      {
        delayMicroseconds(10*(1/i));    // wait 10 periods of the set frequency to obtain correct values
      }
      mag_ph_ADC();                     // obtaining received values from AD8302
      sendFrequency(i);                 // sending values over UART
    }
    updateFrequency(0);                 // after completing sweep setting frequency back to zero
    singleSweep = false;                // avoiding continuous sweep
    Serial.print("Finished in: ");
    Serial.print((micros() - timestamp)/1000000.0);   // obtain value in seconds
    Serial.print("sec");
    Serial.print('\n');
  }
}



/**
 *    @brief    This function is called when a Serial Event happens. 
 *              Available Data is stored and sent to the UART when received a \n character
 */

 void serialEvent()
 {
    while (Serial.available()) 
    {
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inString:
      inString += inChar;
      if(inChar == '\n')
      {
        stringComplete = true;
      }
    }

    //  string is complete      string starts with '<'          string ends with '>\n'
    if( (stringComplete) && (inString.charAt(0) == '<') && (inString.charAt(inString.length()-2) == '>') ) 
    {
      checkProtocol();
    }
 }

















