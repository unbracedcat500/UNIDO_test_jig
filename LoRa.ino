void LoRa()
{
  /*---------(Testing LoRa)------*/
  DPRINTLN("Testing LoRa...");
  if (!manager.init())
  {
    DPRINTLN(F("init failed!"));
    disp("LoRa Init Failed!");
  }
  else
  { DPRINTLN(F("Lora tested ok"));
    disp("LoRa Tested OK");
  }
}
