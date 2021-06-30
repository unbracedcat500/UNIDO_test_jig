void Gprs()
{
  uint8_t flagGprs = 1;                   //the variable is used for ladder type logic of AT commands
  int statusCode = 0;                     //the variable is used for ladder type loguc of AT commands
  char url[250];                           //the array used to store alert msg in this array
  char buff[250];        
  
  unsigned long baudrate[9] = {4800, 9600, 19200, 38400, 57600, 74880, 115200, 230400, 250000};
  for (int i = 0; i < 9; i++)
  {
    DPRINT(F("Testing module at baudrate "));
    DPRINT(baudrate[i]);
    DPRINTLN(F("....."));
    Serial1.begin(baudrate[i]);
    Serial1.print(F("AT\r\n"));
    if (readStrings(100) == 1)
    {
      DPRINT(F("Module responded at "));
      DPRINTLN(baudrate[i]);
      i = 10;
    }
  }

char apn[20] = "NOT AVAILABLE";
  char simName[20] = "NOT AVAILABLE";

  /*----(STRING MANIPULATION)-----*/
  if (strstr(GSM_String, "Airtel") || strstr(GSM_String, "airtel"))              //"airtel" is the word used to compare apn
  {
    strcpy(apn, "airtelgprs.com");
    strcpy(simName, "AIRTEL");
  }
  else if (strstr(GSM_String, "Vodafone IN"))
  {
    strcpy(apn, "www");
    strcpy(simName, "VODAFONE");
  }
  else if (strstr(GSM_String, "idea"))
  {
    strcpy(apn, "imis/internet");
    strcpy(simName, "IDEA");
  }
  else if (strstr(GSM_String, "TATA DOCOMO"))
  {
    strcpy(apn, "TATA.DOCOMO.INTERNET");
    strcpy(simName, "TATA DOCOMO");
  }
  else if (strstr(GSM_String, "BSNL"))                            //need to record response of BSNL network
  {
    strcpy(apn, "bsnlnet");
    strcpy(simName, "BSNL");
  }
  else
  {
    strcpy(apn, "NO NETWORK");
    strcpy(simName, "NO NETWORK");
  }
  DPRINT(F("Registered network is: "));
  DPRINTLN(simName);
  DPRINT(F("Set apn is: "));
  DPRINTLN(apn);

  Serial1.println(F("AT"));
  readStrings(100);
  Serial1.println(F("AT+QSPN?"));
  readStrings(300);



  for (int i = 0; i < 5; i++)
  {
    Serial1.print("AT+CREG?\r");
    if (readStrings(300) == 3)
    {
      DPRINTLN(F("Internet connected!"));
      i = 10;
    }
    else {
      DPRINT(F("Internet not connected, try....."));
      DPRINTLN(i);
    }
  }

  if (flagGprs == 1)
  {
    Serial1.print(F("AT+QIFGCNT=0\r\n"));  //select a context as foreground context
    if (readStrings(1000) == 1)
    {
      flagGprs++;
    }
    else
    {
      statusCode = 1000;
    }
  }
  if (flagGprs == 2)
  {
    int len = sprintf(url, "http://sicca-api.herokuapp.com/alert");
    sprintf(buff, "AT+QHTTPURL = % d, 30", len);                       //send HTTP server url
    Serial1.println(buff);
    if (readStrings(30000) == 4)
    {
      flagGprs++;
    }
    else  {
      statusCode = 1000;
    }

  }

  if (flagGprs == 3)
  {
    Serial1.print(url);
    if (readStrings(15000) == 1)
    {
      flagGprs++;
      strcpy(buff, "\0");                            //clear the buff array for future use
      strcpy(url, "\0");                             //clear the url array for future use
    }
    else  {
      statusCode = 1000;
    }

  }

  if (flagGprs == 4)
  {
    int len = sprintf(url, "&Authorization=%d&message=%s", tokenName, alertNode);
    sprintf(buff, "AT+QHTTPPOST=%d,40,10", len);
    Serial1.println(buff);
    readStrings(2000);
    if (readStrings(60000) == 4)
    {
      flagGprs++;
    }
    else  {
      statusCode = 1000;

    }
  }
  if (flagGprs == 5)
  {
    Serial1.println(url);
    if (readStrings(60000) == 1)
    {
      flagGprs++;
    }
    else
    {
      statusCode = 1000;
    }
  }
  if (flagGprs == 6)
  {
    Serial1.println(F("AT+QHTTPREAD=30"));
    if (readStrings(20000) == 1)
    {
      flagGprs++;
    }
    else
    {
      statusCode = 1000;
    }
  }
  if (flagGprs == 7)
  {
    DPRINTLN(F("Data uploaded!"));
    statusCode = 1000;
  }

  if (statusCode == 1000)
  {
    Serial1.println(F("AT+QIDEACT"));                               //Deactivate GPRS/CSD PDP Context
    if (readStrings(120000) == 5)
    {
      DPRINTLN(F("close successed!"));
      if (flagGprs < 7)
      {
        DPRINTLN(F("Data failed to upload!"));
        return 0;
      }
      else
      {
        return 1;
      }
    }
    else
    {
      DPRINTLN(F("close failed!"));
    }
    if (flagGprs < 7)
    {
      DPRINTLN(F("Data failed to upload!"));
    }
  }
  return 0;

  
}
