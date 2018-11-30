/*
      __  __                          ____             _                ____  _       _      _           
     / / / /___ _____  ____  ___     / __ \____ ______(_)___  ____ _   / __ \(_)   __(_)____(_)___  ____ 
    / /_/ / __ `/ __ \/_  / / _ \   / /_/ / __ `/ ___/ / __ \/ __ `/  / / / / / | / / / ___/ / __ \/ __ \
   / __  / /_/ / / / / / /_/  __/  / _, _/ /_/ / /__/ / / / / /_/ /  / /_/ / /| |/ / (__  ) / /_/ / / / /
  /_/ /_/\__,_/_/ /_/ /___/\___/  /_/ |_|\__,_/\___/_/_/ /_/\__, /  /_____/_/ |___/_/____/_/\____/_/ /_/ 
  
  CAN Reciever code for the HRD05
  Mark Oosting, 2019
  
*/

#include <CAN.h>

#define ESC1_OUT 3
#define ESC2_OUT 5
#define SERVO_OUT 9

int THROTTLE = 0;
int REVERSE = 0;
int STEER = 0;

void setup() {  
  pinMode(ESC1_OUT, OUTPUT);
  pinMode(ESC2_OUT, OUTPUT);
  pinMode(SERVO_OUT, OUTPUT);
   
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  byte data[8];
  
  if(packetSize) {
  
    int packetID = CAN.packetId();
    
    unsigned int i = 0;
    
    while (CAN.available() && (i < 8)) {
      data[i] = CAN.read();
      i++;
    }

    int CANthrottle = data[0];
  
//    for(int i = 0; i < sizeof(data); i++){
//      Serial.print("Byte ");
//      Serial.print(i);
//      Serial.print(": ");
//      Serial.print(data[i]);
//      Serial.println();
//    }
    
    switch (packetID) {
      case 0x12:
        while (CAN.available() && (i < 8)) {
          data[i] = CAN.read();         
          i++;
        }

        THROTTLE = map(data[0], 0, 255, 191, 255);
        REVERSE = map(data[1], 0, 255, 191, 127);
        STEER = map(data[2], 0, 255, 127, 255);

        
        Serial.println(THROTTLE);
        Serial.println(REVERSE);
        Serial.println(STEER);
        
        
        break;
      default:
        Serial.print("Unknown ID: ");
        Serial.print(packetID);
        Serial.println();
        break;
    }
  }
  
//  Serial.println(data[0]);
//  Serial.println();

//  if (packetSize) {
//    // received a packet
//    Serial.print("Received ");
//
//    if (CAN.packetExtended()) {
//      Serial.print("extended ");
//    }
//
//    if (CAN.packetRtr()) {
//      // Remote transmission request, packet contains no data
//      Serial.print("RTR ");
//    }
//
//    Serial.print("packet with id 0x");
//    Serial.print(CAN.packetId(), HEX);
//
//    if (CAN.packetRtr()) {
//      Serial.print(" and requested length ");
//      Serial.println(CAN.packetDlc());
//    } else {
//      Serial.print(" and length ");
//      Serial.println(packetSize);
//
//      // only print packet data for non-RTR packets
//      while (CAN.available()) {
//        Serial.println((char)CAN.read());
//      }
//      Serial.println();
//    }
//
//    Serial.println();
//  }
}
