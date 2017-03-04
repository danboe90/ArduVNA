

void printError(int err)
{
  lcd.clear();
  lcd.setCursor(0,0);


  
  switch(err)
  {
    case 1:   lcd.print("Protocol Err.");     // displayed when issues with 
              break;
    case 2:   lcd.print("Value Err.");       // displayed when values are incorrect
              break;
    case 3:   lcd.print("sscanf Err.")
              break;
  }
  lcdSweepMode('E');
}




void lcdSweepMode(char mode)
{
  lcd.setCursor(15,0);
  lcd.print(mode);
}


void lcdSingleFrequency(unsigned long frequency)
{  
  // Debug
  // Serial.print(frequency);
  // Serial.print('\n');
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("f=");

  if((frequency/1000000.0) > 1.0)
  {
    Serial.print(frequency/1000000.0);
    lcd.print(frequency/1000000.0);
    lcd.print("MHz");
  }
  else if((frequency/1000.0) > 1.0)
  {
    Serial.print(frequency/1000.0);
    lcd.print(frequency/1000.0);
    lcd.print("kHz");
  }
  else
  {
    lcd.print(frequency);
    lcd.print("Hz");
  }
}

