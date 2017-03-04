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
