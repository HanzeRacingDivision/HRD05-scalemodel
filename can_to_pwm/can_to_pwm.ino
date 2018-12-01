/*
      __  __                          ____             _                ____  _       _      _           
     / / / /___ _____  ____  ___     / __ \____ ______(_)___  ____ _   / __ \(_)   __(_)____(_)___  ____ 
    / /_/ / __ `/ __ \/_  / / _ \   / /_/ / __ `/ ___/ / __ \/ __ `/  / / / / / | / / / ___/ / __ \/ __ \
   / __  / /_/ / / / / / /_/  __/  / _, _/ /_/ / /__/ / / / / /_/ /  / /_/ / /| |/ / (__  ) / /_/ / / / /
  /_/ /_/\__,_/_/ /_/ /___/\___/  /_/ |_|\__,_/\___/_/_/ /_/\__, /  /_____/_/ |___/_/____/_/\____/_/ /_/ 
  
  CAN Reciever code for the HRD05
  Mark Oosting, Wout Veltman, 2019
  
*/

#include <CAN.h>

#define ESC1_OUT 3
#define ESC2_OUT 5
#define STEER_OUT 9
#define MAX_TIMEOUT 500

int MOTOR1 = 191;
int MOTOR2 = 191;
int STEER = 194; // Calibrate this value

unsigned long current_time;
unsigned long latest_message_time;

void setup() {
  pinMode(ESC1_OUT, OUTPUT);
  pinMode(ESC2_OUT, OUTPUT);
  pinMode(STEER_OUT, OUTPUT);
   
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN RECEIVER");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {

  // RECEIVE CAN MESSAGES
  int packetSize = CAN.parsePacket();

  byte data[11];

  unsigned int i = 0;
  
  if(packetSize) {
    
    while (CAN.available()) {
      data[i] = CAN.read();
      i++;
    }
    
    int packetID = CAN.packetId();
    
    switch (packetID) {
      
      // MOTOR CONTROL
      case 0x12:

        //REVERSE = map(data[1], 0, 255, 191, 127);
        
        MOTOR2 = map(data[0], 0, 255, 191, 220);
        MOTOR1 = map(data[0], 0, 255, 191, 220); // Map this to the second motor value

        latest_message_time = millis();
        
        break;


        
      // STEERING CONTROL; MID: 194, Right: 155, Left: 234
      case 0x15:

        STEER = map(data[0], 0, 255, 155, 234);
        
        latest_message_time = millis();
        
        break;
        

      // FALLBACK
      default:
        Serial.print("Unknown ID: ");
        Serial.print(packetID);
        Serial.println();
        break;
    }
  }
  
  current_time = millis();
  
  // Reset to safe values if CAN communication is lost
  if(current_time - latest_message_time > MAX_TIMEOUT) {
    
    MOTOR1 = 191;
    MOTOR2 = 191;
    STEER = 194;
    Serial.println("CAN TIMEOUT");
    
  } else {
    Serial.print("STEER: ");
    Serial.print(STEER);
    Serial.print("\t");
    Serial.print("MOTOR1: ");
    Serial.print(MOTOR1);
    Serial.print("\t");
    Serial.print("MOTOR2: ");
    Serial.print(MOTOR2);
    Serial.println();
  }

//  analogWrite(ESC1_OUT, MOTOR1);
//  analogWrite(ESC2_OUT, MOTOR2);
  analogWrite(STEER_OUT, STEER);

}
