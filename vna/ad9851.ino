/**
 *        Author:         danboe90
 *        Date:           05-03-2017
 *        Version:        1.0.0
 *        Description:    This file holds functions for controlling an AD9851 with an Arduino Nano.
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








/**
 *    @brief    Set the obtained Value as described in the Datasheet found at: 
 *              http://www.analog.com/media/en/technical-documentation/data-sheets/AD9851.pdf
 *              (Figure 13 on Page 14)
 *              Function taken from http://fritzing.org/media/fritzing-repo/projects/d/dds-generator-ad9851-with-keypad-and-lcd/code/AD9851_ARDUINO.ino
 *    @param    frequency, interpreted as Hz
 */
void updateFrequency(unsigned long frequency)
{
  // Serial.print("Set to: ");
  // Serial.print(frequency);
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











void initAD9851()
{
  // setting Pins for the AD9851 Module
  pinMode (DATA, OUTPUT);         // sets pin 10 as OUPUT
  pinMode (CLOCK, OUTPUT);        // sets pin 9 as OUTPUT
  pinMode (FQ_UD, OUTPUT);        // sets pin 8 as OUTPUT
}
}

