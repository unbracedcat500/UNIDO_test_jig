/*----------(Testing Relays)---------------*/
void Relays()
{
  Serial.println("Testing Relays...");
  Serial.println("Check Relay LEDs");
  disp("Check Relay LEDs");
  delay(3000);
  digitalWrite(pumpRelay1, LOW);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  delay(1000);
  digitalWrite(pumpRelay2, LOW);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  delay(1000);
  digitalWrite(node1Relay, LOW);
  delay(1000);
  digitalWrite(node2Relay, LOW);
  delay(1000);
  digitalWrite(node3Relay, LOW);
  delay(1000);
  digitalWrite(node4Relay, LOW);
  delay(1000);
  digitalWrite(node5Relay, LOW);
  delay(1000);
  digitalWrite(node6Relay, LOW);
  delay(1000);
  digitalWrite(pumpRelay1, HIGH);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  delay(1000);
  digitalWrite(pumpRelay2, HIGH);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  delay(1000);
  digitalWrite(node1Relay, HIGH);
  delay(1000);
  digitalWrite(node2Relay, HIGH);
  delay(1000);
  digitalWrite(node3Relay, HIGH);
  delay(1000);
  digitalWrite(node4Relay, HIGH);
  delay(1000);
  digitalWrite(node5Relay, HIGH);
  delay(1000);
  digitalWrite(node6Relay, HIGH);
  delay(1000);
  Serial.println("Relay Tested OK");
  disp("Relay Tested OK");
  
  
}
