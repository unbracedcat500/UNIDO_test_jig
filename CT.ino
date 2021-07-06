void Current()
{
  
  Serial.println("Checking Current Ampere...");
  Irms = emon1.calcIrms(1480);
  DPRINT("Current: ");
  DPRINTLN(Irms);
  sprintf(show,"Current: %d A",(int)Irms);
  disp(show);
}
