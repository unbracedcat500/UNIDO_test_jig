void manualMode()
{
  
  int buttonState = digitalRead(manualIn);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      Serial.println("Sicca is in Manual Mode");
    }
    if (buttonState == LOW){
      // if the current state is LOW then the button went from on to off:
      Serial.println("Sicca is in Auto Mode");
    }
    // Delay a little bit to avoid bouncing
    delay(50); 
  }
  lastButtonState = buttonState;
}
