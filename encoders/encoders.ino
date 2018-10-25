// pins for the encoder inputs
#define ENC_FR 3
#define ENC_FL 1
#define ENC_RR 2
#define ENC_RL 3

float WHEEL_DIAMETER = 80; // mm
float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * PI;
int ENC_RESOLUTION = 1; // Amount of magnets
int ENC_TIMER = 100; // ms

// variables to store the number of encoder pulses
volatile unsigned long FR_Count = 0;
volatile unsigned long FL_Count = 0;
volatile unsigned long RR_Count = 0;
volatile unsigned long RL_Count = 0;

float FR_Speed = 0;
float FL_Speed = 0;
float RR_Speed = 0;
float RL_Speed = 0;

void setup() {
  pinMode(ENC_FR, INPUT);
  pinMode(ENC_FL, INPUT);
  pinMode(ENC_RR, INPUT);
  pinMode(ENC_RL, INPUT);

  // initialize hardware interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_FR), encoderEvent, CHANGE);
  
  Serial.begin(115200);
}

void loop() {

  int FR_Count_Before = FR_Count;
  
  delay(ENC_TIMER);

  int FR_Count_After = FR_Count;

  int FR_diff = FR_Count_After - FR_Count_Before;

  FR_Speed = FR_diff * (WHEEL_CIRCUMFERENCE / ENC_RESOLUTION) / ENC_TIMER;

  Serial.println(FR_Speed);
  
}

// encoder event for the interrupt call
void encoderEvent() {
  if (digitalRead(ENC_FR) == LOW) {
    FR_Count++;
  }
}
 
