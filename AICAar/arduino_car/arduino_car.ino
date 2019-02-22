int SLOW_SPEED = 150;
int FAST_SPEED = 200;

int Left_motor_go=8;     //IN1
int Left_motor_back=9;   //IN2

int Right_motor_go=10;   //IN3
int Right_motor_back=11; //IN4

int button=A2;
int buzzer=A3;

int readBit0 = 2;
int readBit1 = 3;
int readBit2 = 5;
int readBit3 = 6;

int mode = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  
  pinMode(button,INPUT); //button A2
  pinMode(buzzer,OUTPUT); //buzzer A3
  
  pinMode(readBit0, INPUT);
  pinMode(readBit1, INPUT);
  pinMode(readBit2, INPUT);
  pinMode(readBit3, INPUT);
}

void walk() {
  digitalWrite(Right_motor_go,HIGH);  //Set left motor as forward
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,SLOW_SPEED);  //PWM of right motor [0, 255]
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  //Set left motor as forward
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);  //PWM of left motor [0, 255]
  analogWrite(Left_motor_back,SLOW_SPEED);
//  delay(time * 100);  //time interval
}

void run() {
  digitalWrite(Right_motor_go,HIGH);  //Set left motor as forward
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,FAST_SPEED);  //PWM of right motor [0, 255]
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  //Set left motor as forward
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);  //PWM of left motor [0, 255]
  analogWrite(Left_motor_back,FAST_SPEED);
//  delay(time * 100);  //time interval
}

void brake() {
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
//  delay(time * 100);  //time interval
}

void left() {
  digitalWrite(Right_motor_go,HIGH);
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,150); 
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);
//  delay(time * 100); //time interval
}

void right() {
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);
//  delay(time * 100);
}

void back() {
  digitalWrite(Right_motor_go,LOW); //Set right motor as backward
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,SLOW_SPEED); //PWM of right motor [0, 255]
  digitalWrite(Left_motor_go,HIGH);  //Set left motor as backward
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,SLOW_SPEED);  //PWM of left motor [0, 255]
  analogWrite(Left_motor_back,0);
//  delay(time * 100); //time interval
}

void back_fast() {
  digitalWrite(Right_motor_go,LOW);  //Set right motor as backward
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,FAST_SPEED);  //PWM of right motor [0, 255]
  digitalWrite(Left_motor_go,HIGH);   //Set left motor as backward
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,FAST_SPEED);  //PWM of left motor [0, 255]
  analogWrite(Left_motor_back,0);
//  delay(time * 100); //time interval
}

void loop() {
  /*
   * Modes
   * 0: Stop
   * 1: Forward slowly
   * 2: Forward fast
   * 3: Back slowly
   * 4: Back fast
   * 5: Turn left
   * 6: Turn right
   * 
   */
  int mode = digitalRead(readBit0)*1+digitalRead(readBit1)*2+digitalRead(readBit2)*4+digitalRead(readBit3)*8;
  Serial.println(mode);
  if (mode == 1) {
    walk();
  } else if (mode == 2) {
    run();
  } else if (mode == 3) {
    back();
  } else if (mode == 4) {
    back_fast();
  } else if (mode == 5) {
    left();
  } else if (mode == 6) {
    right();
  } else {
    brake();
  }
}










