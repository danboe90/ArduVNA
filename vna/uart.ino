/**
 *    @brief    Sends the received values from the sweep over the UART to a GUI.
 *    @param    frq: is the Frequency at which the values are measured
 */
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


 void initUART()
 {
  // Serial set to 9600 Baud 8N1
  Serial.begin(115200);
  // save some space for the incoming messages from UART
  inString.reserve(200);
 }

