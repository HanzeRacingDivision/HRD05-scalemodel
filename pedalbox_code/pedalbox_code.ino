void setup() {

  Serial.begin(115200);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
}

void loop() {
  
  int throttle0  = analogRead(0);
  int throttle1  = analogRead(1);
  int reverse2   = analogRead(2);
  int reverse3   = analogRead(3);
  int steering4  = analogRead(4); 
  
  reverse2 = map(reverse2, 902, 447, 191, 127);
  reverse3 = map(reverse3, 1016, 505, 191, 127);
  int reverse = (reverse2 + reverse3)/2;
  
  throttle0 = map(throttle0, 300, 153, 191, 255);
  throttle1 = map(throttle1, 1014, 448, 191, 255);
  int throttle = (throttle0 + throttle1)/2;

  if(reverse < 191) {

    analogWrite(9, reverse);
    analogWrite(10, map(reverse, 191, 127, 191, 255)); 

  } else {

    analogWrite(9, throttle);
    analogWrite(10, map(throttle, 191, 255, 191, 127)); 
    
  }
  
  int steering = analogRead(4);
  analogWrite(11, map(steering, 0, 1023, 127, 255));
  
  delay(20);
  
  
}
