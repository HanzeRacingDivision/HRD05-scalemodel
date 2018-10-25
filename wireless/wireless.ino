void setup() {
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {jan willem curp
  int drive = analogRead(0) - analogRead(1);
  int steer = analogRead(2) - analogRead(3);

  Serial.println(steer);
  Serial.println();

  if(drive > 60 | drive < -60){
    analogWrite(3, map(drive, -700, 700, 127, 255));
    analogWrite(5, map(drive, 127, 255, 255, 127));
    
  }
    
  if(steer > 60 | steer < -60){
    analogWrite(9, map(steer, -700, 700, 127, 255));  
  }

}
