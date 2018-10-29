// pins for the encoder inputs
#define ENC_FR 2
#define ENC_FL 3
#define ENC_RR 4
#define ENC_RL 5

float WHEEL_DIAMETER = 80; // mm
float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * PI;
int ENC_RESOLUTION = 4; // Number of magnets

float FR_RPM = 0;
float FL_RPM = 0;
float RR_RPM = 0;
float RL_RPM = 0;

unsigned long time;
unsigned long FR_latest_time;
unsigned long FL_latest_time;
unsigned long RR_latest_time;
unsigned long RL_latest_time;

void setup() {
  pinMode(ENC_FR, INPUT_PULLUP);
  pinMode(ENC_FL, INPUT_PULLUP);
  pinMode(ENC_RR, INPUT_PULLUP);
  pinMode(ENC_RL, INPUT_PULLUP);

  // Initialize hardware interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_FR), interrupt_FR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_FL), interrupt_FL, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_RR), interrupt_RR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_RL), interrupt_RL, RISING);
  
  Serial.begin(115200);
}

void loop() {

  // Global time
  time = millis();

  // float FR_Speed = FR_RPM * WHEEL_CIRCUMFERENCE;

  Serial.print(FR_RPM); Serial.print(" FR \t");
  Serial.print(FL_RPM); Serial.print(" FL \t");
  Serial.print(RR_RPM); Serial.print(" RR \t");
  Serial.print(RL_RPM); Serial.print(" RL \t");
  Serial.println();
  
  delay(50);
  
}

// Interrupt events
void interrupt_FR() {
  FR_RPM = getRPMandResetEncTimer(FR_latest_time);
}
void interrupt_FL() {
  FL_RPM = getRPMandResetEncTimer(FL_latest_time);
}
void interrupt_RR() {
  RR_RPM = getRPMandResetEncTimer(RR_latest_time);
}
void interrupt_RL() {
  RL_RPM = getRPMandResetEncTimer(RL_latest_time);
}

int getRPMandResetEncTimer(unsigned long & encoder_time) {
  int rpm = 60000 / ((millis() - encoder_time) * ENC_RESOLUTION);
  encoder_time = millis();
  return rpm;
}
