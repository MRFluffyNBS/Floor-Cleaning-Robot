#include "roomba_motors.h"
#include "sensors.h"

//right motor pin1 and pin2
const int motor_pin1 = 16;
const int motor_pin2 = 17;
//left motor pin3 and pin4 
const int motor_pin3 = 27;
const int motor_pin4 = 33; 
//duration and speed settings
const int duration = -1; //set the duration to -1 for the motors to turn continously until method stop() is called
int speed = 150;
//Motors initalize
Motors roomba(motor_pin1, motor_pin2, motor_pin3, motor_pin4, speed);

const int rtrig_pin = 18;
const int recho_pin = 5;

const int ltrig_pin = 32;
const int lecho_pin = 15;

const int sensor_tolerance = 15;

Ultson rightSonic(rtrig_pin, recho_pin, sensor_tolerance);
Ultson leftSonic(ltrig_pin, lecho_pin, sensor_tolerance);

const int rir_pin = 4;
const int lir_pin = 14; 

Irsensor rIr(rir_pin);
Irsensor lIr(lir_pin);

const int button_pin = 19;

int degrees = 90;
int direction = 0;

const int switch_pin = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //set pimode for motors
  roomba.begin();
  roomba.printMotors();
  //set pinmode for the ultrasonic sensors
  rightSonic.begin();
  leftSonic.begin();

  rIr.begin();
  lIr.begin();
  
  pinMode(button_pin, INPUT);
  pinMode(13, OUTPUT);
  //set random seed to arbitrary number 
  randomSeed(12346);
  //setting up pinmode for GPIO pin that switches on/off the vacuum
  pinMode(switch_pin, OUTPUT);
  digitalWrite(switch_pin, LOW); //ensures the vacuum is turned off before the roomba starts working
  Serial.println("Off, waiting for signal...");

  while (digitalRead(button_pin) == LOW) { //waits for button to be pressed to turn on
  }

  Serial.println(" Turning on...");
  digitalWrite(switch_pin, HIGH); //turn on high (temp)
}

void loop() {
  //check if the right ultrasonic sensor detects an object first
  
  if (rightSonic.objectDetected() == true || rIr.checkDistance() == true) {
    Serial.println("Right sensor detected");
    roomba.stop();
    delay(100);//Gives the motors time to wind down 
    //Somtimes the only one motor spins up when going directly into reverse
    roomba.reverse(800);

    roomba.stop();
    degrees = random(45, 136); // random number from 45 to 135 degrees
    float time = degrees * (400.0 / roomba.getSpeed());
    //Serial.print("Degrees/time of rotation: "); 
    //Serial.println(time);
    //Turns opposite direction to which sensor has detected an object
    //most likely there is more space on the left if the right sensor detects somehting first
    roomba.left(time);
    delay(60);
    roomba.forward();
  }
  else if (leftSonic.objectDetected() == true || lIr.checkDistance() == true) {
    Serial.println("Left sensor detected");
    roomba.stop();
    delay(100); //Gives the motors time to wind down 
    //Somtimes the only one motor spins up when going directly into reverse
    roomba.reverse(800);

    roomba.stop();
    degrees = random(60, 181); // random number from 45 to 180 degrees
    float time = degrees * 5.0;
    //Serial.print("Degrees/time of rotation: "); 
    //Serial.println(time);
    //same reteoric as the other sensor
    roomba.right(time);
    delay(60);
    roomba.forward();
  }
    else {//proceed forward
    //delay(60);
    roomba.forward();
    }
}
