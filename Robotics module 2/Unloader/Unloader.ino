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

  Serial.println(distance1);
  Serial.println(distance2);

  int step = 1000;
  // Check if an object 
  if(distance1< 15 && distance2> 15){
    //Pick up 
    //pahse 1
    move(middle, 180);
    move(left, 65);
    move(right, 40);
    move(claw, 20);
    //pahse 2
    move(middle, 190);
    move(left, 35);
    move(right, 110);
    //pahse 3
    move(claw, 180);

    //Drop
    //pahse 1
    move(left, 60);
    move(right, 80);
    //pahse 2
    move(middle, 65);
    //pahse 3
    move(left, -5);
    move(right, 125);
    //pahse 4
    move(claw, 0);
    //pahse 5
    move(left, -15);
    move(right, 90);
    //pahse 6
    move(middle, 90);
    move(left, 90);
    move(right, 90);
    move(claw, 90);
    delay(15000);
    
    
  }

  // Wait a short period before reading the sensors again
  delay(1000);
}

