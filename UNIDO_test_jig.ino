/*This code is used to test UNIDO SICCA as a test jig for testing the working of all it's components
   This code is written by Faizan Shaikh, Co-Founder Sense It Out
*/
#include <RHReliableDatagram.h>                     //Manager class radiohead
#include <RH_RF95.h>                                //Radiohead driver class
#include <SPI.h>                                    //for SPI
#include <LiquidCrystal_I2C.h>                      //liquid crystal i2c library
#include <EEPROM.h>                                 //Library for saving SICCA status inside eeprom
#include "EmonLib.h"                                //Include Emon Library for current sensor
#include <SD.h>                                     //sd card library

#define DPRINT(...)   Serial.print(__VA_ARGS__)
#define DPRINTLN(...) Serial.println(__VA_ARGS__)
#define BUFFER_SIZE 250
#define pumpRelay1 4                                 //Relay pin 1 for turn ON/OFF the autocon and S1 of starter(7)     relayVersion2:4
#define pumpRelay2 5                                //Relay pin 2 for turn ON/OFF the S2 of starter(6)                  relayVersion2:5
#define node1Relay 6                                //Relay pin 2 for turn ON/OFF the valve 1 (6)                       relayVersion2:6
#define node2Relay 7                                //Relay pin 3 for turn ON/OFF the valve 2 (5)                       relayVersion2:7
#define node3Relay 8                                //Relay pin 4 for turn ON/OFF the valve 3 (4)                       relayVersion2:8
#define node4Relay 9                               //Relay pin 5 for turn ON/OFF the valve 4 (11)                       relayVersion2:9
#define node5Relay 10                               //Relay pin 6 for turn ON/OFF the valve 5 (10)                      relayVersion2:10
#define node6Relay 11
#define sdcs 44
#define manualOut 36
#define manualIn 38

#define CONTROLLER_ADDRESS 20                       //CONTROLLER ADDRESS FOR RELIABLE RECEPTION AND TRANSMISSION IT SHOULD BE 10
#define electricityTimer 180

char GSM_String[BUFFER_SIZE];
char url[100] = "sicca-api.herokuapp.com";
char apn[20] = "tempApn";
double Irms = 0;
int tokenName = 100;
int lastButtonState = 0;
/*---------( instances )---------*/
RH_RF95 driver(53, 2);                                               //Singleton instance of the radio driver declared above(CHIP SELECT, INTERRUPT)
RHReliableDatagram manager(driver, CONTROLLER_ADDRESS);              //Class to manage message delivery and receipt, using the driver
LiquidCrystal_I2C lcd(0x27, 20, 4);                                  //20*4 LCD i2c address is 0x27( try 0X3F if nothing display )
EnergyMonitor emon1;                                                 // Instance for current sensor library
File dataFile;                                                       //instance for sd card


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("start");
  

  pinMode(pumpRelay1, OUTPUT);                        //FOR pump 1
  pinMode(pumpRelay2, OUTPUT);                        //FOR pump 1
  pinMode(node1Relay, OUTPUT);                       //FOR node 1
  pinMode(node2Relay, OUTPUT);                       //FOR node 2
  pinMode(node3Relay, OUTPUT);                       //FOR node 3
  pinMode(node4Relay, OUTPUT);                       //FOR node 4
  pinMode(node5Relay, OUTPUT);                       //FOR node 5
  pinMode(node6Relay, OUTPUT);                       //FOR node 6
  digitalWrite(pumpRelay1, HIGH);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  digitalWrite(pumpRelay2, HIGH);                     //RELAY BOARD OPTOCOUPLER IS ACTIVE LOW
  digitalWrite(node1Relay, HIGH);
  digitalWrite(node2Relay, HIGH);
  digitalWrite(node3Relay, HIGH);
  digitalWrite(node4Relay, HIGH);
  digitalWrite(node5Relay, HIGH);
  digitalWrite(node6Relay, HIGH);

  /*----------( Manual Mode Setup )----------*/
  pinMode(manualOut, OUTPUT);                        //PINS USED FOR DETECTING MANUAL MODE
  pinMode(manualIn, INPUT);

  digitalWrite(manualOut, HIGH);

  /*----------( Current Sensor Setup)----------*/
  emon1.current(15, 6);

  /*----------(LCD setup)----------------*/
  lcd. begin();
  lcd. backlight();
  lcd.clear();

  LoRa();
  SdCard();
  Relays();
  Gprs();
  Current();
  Serial.println("Testing Auto/Manual Switch...");


}

void loop() {
  // put your main code here, to run repeatedly:
  manualMode();
  disp();
}
