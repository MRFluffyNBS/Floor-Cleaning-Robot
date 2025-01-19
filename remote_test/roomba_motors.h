#ifndef ROOMBA_MOTORS_H
#define ROOMBA_MOTORS_H

#include <Arduino.h>

class Motors {
  private:
    int right_motor1;
    int right_motor2;
    int left_motor1;
    int left_motor2; 
    int motor_speed;
    
    void motor_forward(int motor1, int motor2); 
    void motor_reverse(int motor1, int motor2);
    void stop_motor(int motor1, int motor2);

  public: 
    Motors(int pin1, int pin2, int pin3, int pin4, int speed);
    void begin();
    void setSpeed(int speed);
    int getSpeed();
    void printMotors();

    void forward(int duration=-1);
    void reverse(int duration=-1);
    void right(int duration=-1);
    void left(int duration=-1);
    void stop();
};


#endif