int readStrings(int timeout)
{
  int  index = 0;
  int  inByte = 0;
  char WS[3];

  /*----------( erase GSM_String )----------*/
  memset(GSM_String, 0, BUFFER_SIZE);         //used to clear the GSM_String SYSNTAX:(function, value, locations)
  memset(WS, 0, 3);

  /*----------( wait for outgoing data )----------*/
  Serial1.flush();

  /*----------( Clear Serial Line Buffer )----------*/
  while (Serial1.available())
  {
    Serial1.read();
  }

  /*----------( wait of the first character for "timeout" ms )----------*/
  Serial1.setTimeout(timeout);
  inByte = Serial1.readBytes(WS, 1);
  GSM_String[index++] = WS[0];

  /*----------( wait of further characters until a pause of 30 ms occures )----------*/
  while (inByte > 0)
  {
    Serial1.setTimeout(1000);
    inByte = Serial1.readBytes(WS, 1);
    GSM_String[index++] = WS[0];
  }
  DPRINTLN(GSM_String);

  if (strstr(GSM_String, "OK\r\n"))
  {
    if (strstr(GSM_String, "DEACT OK\r\n"))
    {
      return 5;
    }
    else
    {
      return 1;
    }
  }
  if (strstr(GSM_String, "CONNECT\r\n"))
  {
    return 4;
  }
  if (strstr(GSM_String, "+CREG: 0,5"))
  {
    return 3; //Internet connected
  }

  return 0;
}
