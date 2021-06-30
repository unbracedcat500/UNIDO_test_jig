void manualMode()
{
  Serial.println("Testing Auto/Manual Switch...");
  Serial.println("Please toggle the switch");
  delay(5000);
  bool switchState = digitalRead(manualIn);
  for (int i = 0; i < 2; i++)
  {
    Serial.println("Please toggle the switch");
    if (digitalRead(manualIn) == 1)
      DPRINTLN(F("SICCA is in ManualMode"));
    else()
      DPRINTLN(F("SICCA is in AutoMode"));
  }

}
