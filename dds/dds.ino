/**
 *        Author:         danboe90
 *        Date:           28-02-2017
 *        Version:        1.0.0
 *        Description:    This file holds functions for controlling an AD9851 and AD8302 with an Arduino Nano.
 */






/************************************************** PINNING **************************************************/
// Source:  http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/DDS_AD9830_3.jpg
//          http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/
//          http://www.elechouse.com/elechouse/images/product/AD985x%20DDS%20Module/ad9850_1%20manual.pdf
// 
//
//       ________________________ _________________________
//      |        Arduino (Pins)  |       AD9851 (Pins)     |
//      |________________________|_________________________|
//      |           D2           |          FQ_UD          |
//      |           D3           |          WCLK           |
//      |           D4           |          D7  (DATA)     |
//      |           GND          |          GND            |
//      |           +5V          |          Vcc            |
//      |________________________|_________________________|
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
String          inString;                     // holds received message from UART
boolean         stringComplete    = false;    // defines if received message from UART has ended and was terminated with '\n'
char            mode;                         // defines the mode received from the GUI

// Generation Modes - are set depending on content of 'char mode'
boolean         continuousSweep;               // true if in continuous mode 
boolean         singleSweep;                   // true if in single sweep mode

// for the LCD
LiquidCrystal   lcd(7,8,9,10,11,12);          // Pinning listed above for the Display


// for the ADC
unsigned int    adcmag;
unsigned int    adcphs;
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
    for(unsigned long i=start_frequency; i<=stop_frequency ; i=i+diff_frequency)
    {
      updateFrequency(i);   // setting frequency on the DDS
      mag_ph_ADC();         // obtaining received values from AD8302
      sendFrequency(i);     // sending values over UART
    }
    updateFrequency(0);
    singleSweep = false;
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
      // split the string into substrings to get the components
      char buf[200];
      inString.toCharArray(buf, inString.length());
      int rtn = sscanf(buf, "<%c,%lu,%lu,%lu>\n", &mode, &start_frequency, &stop_frequency, &step_frequency);

      if(rtn != -1)
      {
        
        if(stop_frequency > start_frequency)
        {
          // values where passed correctly
        }
        else
        {
          stop_frequency = 0;
          start_frequency = 0;
          mode='e';
        }
      }
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("fsta=");
      if(start_frequency/1000000 > 0)
      {
        lcd.print((float)(start_frequency/1000000.0));
        lcd.print("MHz");
      }
      else if(start_frequency/1000 > 0)
      {
        lcd.print((float)(start_frequency/1000.0));
        lcd.print("kHz");
      }
      else
      {
        lcd.print(start_frequency);
        lcd.print("Hz");
      }
      

      // display the Mode
      if(mode== 'c')
      {
        continuousSweep = true;        
        singleSweep = false;
        lcd.setCursor(15,0);
        lcd.print("C");
      }
      if(mode == 's')
      {
        continuousSweep = false;
        singleSweep = true;
        lcd.setCursor(15,0);
        lcd.print("S");
      }
      if(mode == 'e')
      {
        continuousSweep = false;
        singleSweep = false;
        lcd.setCursor(15,0);
        lcd.print("E");
      }

      
      // second row
      lcd.setCursor(0,1);
      lcd.print("fsto=");
      if(stop_frequency/1000000 > 0)
      {
        lcd.print((float)(stop_frequency/1000000.0));
        lcd.print("MHz");
      }
      else if(stop_frequency/1000 > 0)
      {
        lcd.print((float)(stop_frequency/1000.0));
        lcd.print("kHz");
      }
      else
      {
        lcd.print(stop_frequency);
        lcd.print("Hz");
      }
      
      stringComplete = false;
      inString = "";
    }

    
 }











/**
 *    @brief    Set the obtained Value as described in the Datasheet found at: 
 *              http://www.analog.com/media/en/technical-documentation/data-sheets/AD9851.pdf
 *              (Figure 13 on Page 14)
 *              Function taken from http://fritzing.org/media/fritzing-repo/projects/d/dds-generator-ad9851-with-keypad-and-lcd/code/AD9851_ARDUINO.ino
 *    @param    frequency, interpreted as Hz
 */
void updateFrequency(unsigned long frequency)
{
  unsigned long tuning_word = (frequency * pow(2, 32)) / DDS_CLOCK;
  digitalWrite (FQ_UD, LOW); // take load pin low

  for(int i = 0; i < 32; i++)
  {
    if ((tuning_word & 1) == 1)
      outOne();
    else
      outZero();
    tuning_word = tuning_word >> 1;
  }
  byte_out(0x09);

  digitalWrite (FQ_UD, HIGH); // Take load pin high again
}


void sendFrequency(unsigned long frq)
{
  Serial.print("f=");
  Serial.print(frq);
  Serial.print("Hz/");
  Serial.print("MAG: ");
  Serial.print(magFinal);
  Serial.print("/");
  Serial.print("PHASE: ");
  Serial.print(phsFinal);
  Serial.print('\n');
}


/**
 *    @brief      Reading values from the ADC. Adaptation to full scale is done and stored the final value in the 
 *                ***Final-Variables.
 */
void mag_ph_ADC()
{
  // fetch value from ADC
  adcmag = analogRead(PWR_IN);
  adcphs = analogRead(PH_IN);

  //adaptation of the Value
  magFinal = (60.0 /1024) * adcmag -60.0;
  phsFinal = (180/1024) * adcphs;
}


/************************************************** HELPERFUNCTIONS **************************************************/


/**
 *    @brief    HelperFunction to write an entire byte to the AD9851 Module
 */
void byte_out(unsigned char byte)
{
  int i;

  for (i = 0; i < 8; i++)
  {
    if ((byte & 1) == 1)
      outOne();
    else
      outZero();
    byte = byte >> 1;
  }
}



/**
 *    @brief    Helper function to write '1' (BIN, Base=2) to the AD9851 Module
 */
void outOne()
{
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA, HIGH);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(DATA, LOW);
}



/**
 *    @brief    Helper fucntion to write '0' (BIN, Base=2) to the AD9851 Module
 */
void outZero()
{
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, HIGH);
}









