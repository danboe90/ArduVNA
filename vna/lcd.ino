

void printError(int err)
{
  lcd.clear();
  lcd.setCursor(0,0);


  
  switch(err)
  {
    case 1:   lcd.print("Error occured");
              lcdSweepMode('E');
              break;
  }
}




void lcdSweepMode(char mode)
{
  lcd.setCursor(15,0);
  lcd.print(mode);
}


void printSingleF(unsigned long frequency)
{
  
}

