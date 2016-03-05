/*
* `<Author>`         `<Time>`        `<Version>`  
*   xiaoyu          2016/03/04          1.0.0    
*/
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int servoPin = A0;  //arduino Pin on ZeroPi A0 A1 A2 A3 M0SI MISO SCK PIN_WIRE_SDA PIN_WIRE_SCL 0 1
void setup() {
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

