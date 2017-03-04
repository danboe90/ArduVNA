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
