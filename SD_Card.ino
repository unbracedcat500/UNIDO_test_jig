
/*----(Testing SD Card Module)-----*/
void SdCard()
{
  Serial.println("Testing SD card...");
  if (!SD.begin(sdcs)) {                             //checks SD card is present or not on given SS pin
    DPRINTLN(F("Card failed, or not present"));
  }
  else
  {
    DPRINTLN(F("card initialized."));
  }
  dataFile = SD.open("parli.txt", FILE_WRITE);
  dataFile.print("SD Card Tested OK");
  dataFile.close();
  Serial.println("SD Card Tested OK");

}
