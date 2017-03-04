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
