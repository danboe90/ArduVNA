/************************************************** HELPERFUNCTIONS **************************************************/




void checkProtocol()
{
  int rtn;              // return Value for the sscanf function
  char buf[200];        // char array to handle the 
  // split the string into substrings to get the components
  
  

  
  if(inString.charAt(1) == 'f')
  {
    continuousSweep = false;
    singleSweep     = false;
    inString.toCharArray(buf, inString.length());
    rtn = sscanf(buf, "<%c,%lu>\n", &mode, &single_frequency);
    if(rtn > 0)
    {
      if(single_frequency < MAX_FREQUENCY)
      {
        updateFrequency(single_frequency);
        lcdSingleFrequency(single_frequency);
        lcdSweepMode('F');
      }
      else
      {
        // print error
      }
    }
    inString="";
  }





  
  else if(inString.charAt(1) == 'c' || inString.charAt(1) == 's')
  {
    inString.toCharArray(buf, inString.length());
    rtn = sscanf(buf, "<%c,%lu,%lu,%lu>\n", &mode, &start_frequency, &stop_frequency, &step_frequency);

    if(inString.charAt(1) == 'c')
    {
      singleSweep       = false;
      continuousSweep   = true;
    }
    if(inString.charAt(1) == 's')
    {
      singleSweep       = true;
      continuousSweep   = false;
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

