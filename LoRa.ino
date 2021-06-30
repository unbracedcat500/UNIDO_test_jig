void LoRa()
{
/*---------(Testing LoRa)------*/
  DPRINTLN("Testing LoRa...");
  if (!manager.init())
    DPRINTLN(F("init failed!"));
  else
    DPRINTLN(F("Lora tested ok"));

}
