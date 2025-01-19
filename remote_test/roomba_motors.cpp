#include "roomba_motors.h"
//#include <iostream> // for debugging. comment this out when running within the Arduino terminal
//#include <Arduino.h>

//private methods
//These single motor methods are useful for rotation the roomba
void Motors::motor_forward(int motor1, int motor2) {
  //private method for turning a single motor forward
  //stop();
  analogWrite(motor1, motor_speed);
  analogWrite(motor2, LOW);
  //Serial.println("Motor started in forward direction");
}
void Motors::motor_reverse(int motor1, int motor2) {
  //private method for turning a single motor reversed
  //stop();
  analogWrite(motor1, LOW);
  analogWrite(motor2, motor_speed);
  //Serial.println("Motor started in reverse direction");
}
void Motors::stop_motor(int motor1, int motor2) {
  //private: stops a single motor
  analogWrite(motor1, LOW);
  analogWrite(motor2, LOW);
  //Serial.println("Motor stopped");
}

//public methods
Motors::Motors(int pin1, int pin2, int pin3, int pin4, int speed /*=255*/) {
  //INITIALIZER: pin1 and pin2 are the right motor input pins with pin3 and 4 being the left motor
  //Invariant: pin1, pin2, pin3, and pin4 must be INT
  //speed can be set within a range of 0 to 255 with 255 being max speed (default is 255)
  //futher addons for rotation/rotation angles and parameters for physical motor/wheel measurements
  //for rpm and rotation angle control
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  right_motor1 = pin1;
  right_motor2 = pin2;
  left_motor1 = pin3;
  left_motor2 = pin4;
  motor_speed = speed;
}

void Motors::begin() {
  pinMode(right_motor1, OUTPUT);
  pinMode(right_motor2, OUTPUT);
  pinMode(left_motor1, OUTPUT);
  pinMode(left_motor2, OUTPUT);
  digitalWrite(right_motor1, LOW);
  digitalWrite(right_motor2, LOW);
  digitalWrite(left_motor1, LOW);
  digitalWrite(left_motor2, LOW);
}
void Motors::setSpeed(int speed) {
  //set the current motor speed.
  //Precondition: speed must be an int between 0 and 255 inclusive
  motor_speed = speed;
}

int Motors::getSpeed() {
  //get the current motor speed
  return motor_speed;
}
void Motors::printMotors() {
  Serial.print("Right Motor:");
  Serial.print(" Pin ");
  Serial.print(right_motor1);
  Serial.print(" Pin ");
  Serial.println(right_motor2);
  Serial.print("Left Motor:");
  Serial.print(" Pin ");
  Serial.print(left_motor1);
  Serial.print(" Pin ");
  Serial.println(left_motor2);
}

void Motors::forward(int duration /*=-1*/) {
  //both motors turn forward (default the motors are turned on indefiintely)
  //Serial.println("Currently going forward");
  motor_forward(right_motor1, right_motor2);
  motor_forward(left_motor1, left_motor2);
  if (duration >= 0) {
    delay(duration);
    stop();
    //Serial.println("Motor stopped");
  }
}

void Motors::reverse(int duration /*=-1*/) {
  //both motors turn reverse (default the motors stay on indefinitely)
  //Serial.println("Currently going reverse");
  motor_reverse(right_motor1, right_motor2);
  motor_reverse(left_motor1, left_motor2);
  if (duration >= 0) {
    delay(duration);
    stop();
    //Serial.println("Motor stopped");
  }
}

void Motors::right(int duration /*=-1*/) {
  //turn the roomba to the right for a specified duration
  int temp = motor_speed;
  //setSpeed(60);
  //Serial.println("Currently turning right");
  motor_forward(right_motor1, right_motor2);
  motor_reverse(left_motor1, left_motor2);
  setSpeed(temp);
  if (duration >= 0) {
    delay(duration);
    stop();
    //Serial.println("Motor stopped");
  }
}

void Motors::left(int duration /*=-1*/) {
  //turn left for a specfied duration
  int temp = motor_speed;
  //setSpeed(60);
  //Serial.println("Currently turning left");
  motor_reverse(right_motor1, right_motor2);
  motor_forward(left_motor1, left_motor2);
  setSpeed(temp);
  if (duration >= 0) {
    delay(duration);
    stop();
    //Serial.println("Motor stopped");
  }
}

void Motors::stop() {
  //turns off all motors
  stop_motor(right_motor1, right_motor2);
  stop_motor(left_motor1, left_motor2);
  //Serial.println("Motors stopped");
}
