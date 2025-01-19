#include "sensors.h"

//private methods 


//public methods

Ultson::Ultson(int trig, int echo, float tolerance /*=10*/, float calibration /*=0*/) {
  trig_pin = trig;
  echo_pin=echo;
  
  min_length = tolerance;
  offset = calibration;
  
}

void Ultson::begin() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}

float Ultson::getTolerance() {
  return min_length;

}

void Ultson::setTolerance(float value) {
  min_length = value;
}

float Ultson::getOffset() {
  return offset;
}

void Ultson::setOffset(float value) {
  offset = value;
}


bool Ultson::objectDetected() {
  float distance;
  float duration;
  //sequence to start ultrasonic sensor
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  distance = (duration * 0.0344 / 2) + offset;

  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(60); //buffer period between ultrasonic sensors

  if (distance <= min_length && distance > 0) { //sometimes the sensor bugs out and reads a 0.0 so we'll ignore when that happens
    Serial.println("Object detected");
    return true; 
  }
  else {
    //Serial.println("No object detected");
    return false;
  }
}

Irsensor::Irsensor(int ir) {
  ir_pin = ir;
}

void Irsensor::begin() {
  pinMode(ir_pin, INPUT);
}

bool Irsensor::checkDistance() {

  if (digitalRead(ir_pin) == HIGH) { //There is a distance of more than 2 cm under proximity sensor
    Serial.println("Falloff detected");
    return true;
  }
  else {
    return false;
  }


}