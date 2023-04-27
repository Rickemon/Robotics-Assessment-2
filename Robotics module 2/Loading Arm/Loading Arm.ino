#include <Arduino.h>
#include <Servo.h>
 
Servo middle, left, right, claw;

// Define the pins for the sensors
const int trigPin1 = 12;
const int echoPin1 = 13;
const int trigPin2 = 9;
const int echoPin2 = 10;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  
  // Initialize the pins for the first sensor
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // Initialize the pins for the second sensor
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

 //Initalise MeArm  
  middle.attach(5);
  left.attach(4);
  right.attach(3);
  claw.attach(2);
}

void move(Servo motor, int pos ){
  
  int currentPos = motor.read();

  int direction = currentPos < pos ? 1 : -1;

  // Move the servo slowly to the target position
  for (int i = currentPos; i != pos; i += direction) {
    motor.write(i);
    delay(10);
  }

  // Set the servo to the target position
  motor.write(pos);
}

void loop() {
  // Read the distance from the first sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  float duration1 = pulseIn(echoPin1, HIGH);
  float distance1 = duration1 * 0.034 / 2;

  // Read the distance from the second sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  float duration2 = pulseIn(echoPin2, HIGH);
  float distance2 = duration2 * 0.034 / 2;
  int step = 1000;
  // Check if an object 
  if(distance1< 15 && distance2 < 15){
    Serial.println('DETECTED');
    delay(step);
    //Pick object up
    //phase 1
    // Pick up object
    // Phase 1
    move(middle, 75);
    move(left, 100);
    move(right, 0);
    move(claw, 0);

    // Phase 2
    move(middle, 65);
    move(left, 125);

    // Phase 3
    move(left, 130);

    // Phase 4
    move(right, 35);
    move(claw, 180);

    // Drop object
    // Phase 1
    move(left, 30);
    move(right, 55);
    move(middle, 155);

    // Phase 2
    move(middle, 160);

    // Phase 3
    move(left, 85);
    move(right, 55);

    // Phase 4
    move(claw, 0);

    // Phase 5
    move(left, 75);
    move(right, 65);

    // Phase 6
    move(middle, 90);
  }

  // Wait a short period before reading the sensors again
  delay(100);
}

