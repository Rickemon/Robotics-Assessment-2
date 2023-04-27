#include <Zumo32U4.h>
Zumo32U4ButtonC buttonC;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;

int reverse = -1;

void setup() {
  Serial.begin(9600);
  lineSensors.initThreeSensors();
}

void loop(){
  unsigned int sensors[3];
  lineSensors.read(sensors);
  
  if(sensors[1] > 300){
    motors.setSpeeds(0, 0);
    while(Serial.available() == 0) {} // wait for a character to be received
    char command = Serial.read(); // read the character
    if(command == 'X') { // if the character is 'X', execute the turn
      int left = 100 * reverse;
      int right = -100 * reverse;
      motors.setSpeeds(left, right);
      if(reverse == -1){
        reverse = 1;
      }
      else{
        reverse = -1;
      }
      Serial.println(left);
      delay(2000);
    }
  }
  else if (sensors[0] > 1200) {
    motors.setSpeeds(100, -100);
  }
  else if (sensors[2] > 1800) {
    motors.setSpeeds(-100, 100);
  }
  else {
    motors.setSpeeds(100, 100);
  }
}