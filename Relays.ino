/*----------(Testing Relays)---------------*/
void Relays()
{
  Serial.println("Testing Relays...");
  Serial.println("Check Relay LEDs");
  digitalWrite(pumpRelay1, LOW);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  digitalWrite(pumpRelay2, LOW);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  digitalWrite(node1Relay, LOW);
  digitalWrite(node2Relay, LOW);
  digitalWrite(node3Relay, LOW);
  digitalWrite(node4Relay, LOW);
  digitalWrite(node5Relay, LOW);
  digitalWrite(node6Relay, LOW);
  delay(3000);
  digitalWrite(pumpRelay1, HIGH);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  digitalWrite(pumpRelay2, HIGH);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  digitalWrite(node1Relay, HIGH);
  digitalWrite(node2Relay, HIGH);
  digitalWrite(node3Relay, HIGH);
  digitalWrite(node4Relay, HIGH);
  digitalWrite(node5Relay, HIGH);
  digitalWrite(node6Relay, HIGH);
  Serial.println("Relay Tested OK");
  
}
