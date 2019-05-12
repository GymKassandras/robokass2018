/*********
Gymnasio Kassandras RoboArm
*********/
#include <Servo.h>

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

const int servo10down = 50;
const int servo10up = 120;

const int servo9_start = 0;
const int servo9_20 = 80;
const int servo9_10 = 160;

Servo servo_9; //Horizontal movement
Servo servo_10; //Verical movement

int _delay;
int redFrequency;
int greenFrequency;
int blueFrequency;
int deka;
int eikosi;
int total;
char tot[3];

void setup() {
  servo_9.attach(9);
  servo_10.attach(10);

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(11, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);

  redFrequency = 0;
  greenFrequency = 0;
  blueFrequency = 0;
  deka = 0;
  eikosi = 0;
  total = 0;
  _delay = 1500;
}

void loop() {
  servo_10.write(servo10up); //raise arm 
  delay(_delay); // Wait
  servo_9.write(servo9_start); //rotate to start position 
  delay(_delay); // Wait 
  servo_10.write(servo10down);//lower the arm
  delay(_delay);
  digitalWrite(11, HIGH);//start pump 
  delay(_delay); // Wait
  
  // Read RED Color
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  // Read GREEN Color
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Read BLUE Color
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  if (redFrequency > blueFrequency) {
  // 20euro
    eikosi += 1;
    servo_10.write(servo10up);
    delay(_delay);  
    servo_9.write(servo9_20);
    delay(_delay); 
    servo_10.write(servo10down);
    delay(_delay);
    digitalWrite(11, LOW);
    delay(_delay); 
  } 
  else if (redFrequency < blueFrequency) {
    // 10euro
    deka += 1;
    servo_10.write(servo10up);
    delay(_delay); 
    servo_9.write(servo9_10);
    delay(_delay); 
    servo_10.write(servo10down);
    delay(_delay);
    digitalWrite(11, LOW);
    delay(_delay); 
  }
  else {
    digitalWrite(11, LOW);
  }
  
  //Calculate Total
  total = (eikosi*20)+(deka*10);
  
 
  delay(100);
}
