#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class Ultson {
  private:
    float min_length;
    int trig_pin;
    int echo_pin;
    float offset;
  public:
    Ultson(int trig, int echo, float tolerance = 10.0, float calibration = 0.0);
    void begin();
    float getTolerance();
    void setTolerance(float value);
    bool objectDetected();
    float getOffset();
    void setOffset(float value);

};

class Irsensor {
  private:
    int ir_pin;
  public:
    Irsensor(int ir);
    void begin();
    bool checkDistance();
};


#endif