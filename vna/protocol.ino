/**
 *        Author:         danboe90
 *        Date:           05-03-2017
 *        Version:        1.0.0
 *        Description:    This file holds functions for the protocol for the UART transmission between GUI and Arduino Nano.
 */



/************************************************** HELPERFUNCTIONS **************************************************/




void checkProtocol()
{
  int rtn;              // return Value for the sscanf function
  char buf[200];        // char array to handle the 
  // split the string into substrings to get the components
  
  

  /**************************************************/
  /*                 Single Frequency Mode          */ 
  /**************************************************/
  if(inString.charAt(1) == 'f')
  {
    continuousSweep = false;
    singleSweep     = false;
    inString.toCharArray(buf, inString.length());
    rtn = sscanf(buf, "<%c,%lu>\n", &mode, &single_frequency);
    if(rtn > 0)
    {
      if(single_frequency <= MAX_FREQUENCY)
      {
        updateFrequency(single_frequency);
        lcdSingleFrequency(single_frequency);
        lcdSweepMode('F');
      }
      else
      {
        printError(2);
      }
    }
    else
    {
      printError(3);
    }
    inString="";
  }





  /**************************************************/
  /*         Single/Continuous Sweep Mode           */ 
  /**************************************************/
  else if(inString.charAt(1) == 'c' || inString.charAt(1) == 's')
  {
    inString.toCharArray(buf, inString.length());
    rtn = sscanf(buf, "<%c,%lu,%lu,%lu>\n", &mode, &start_frequency, &stop_frequency, &step_frequency);

    if(rtn > 0)
    {
      if((stop_frequency > start_frequency) && (step_frequency < (stop_frequency - start_frequency)))
      {
        lcdDualFrequency(start_frequency, stop_frequency);
        if(inString.charAt(1) == 'c')
        {
          lcdSweepMode('C');
          singleSweep       = false;
          continuousSweep   = true;
        }
        if(inString.charAt(1) == 's')
        {
          lcdSweepMode('S');
          singleSweep       = true;
          continuousSweep   = false;
        }
      }
      else
      {
        printError(2);
      }
    }
    else
    {
      printError(3);
    }
  }




  
  else
  {
    // Huston we have a problem
    singleSweep       = false;
    continuousSweep   = false;
    printError(1);
  }

  inString="";
  stringComplete = false;
}

