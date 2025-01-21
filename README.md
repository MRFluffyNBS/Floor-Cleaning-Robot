# Floor-Cleaning-Robot (***Work in Progess***)
This is my attempt at making a (knockoff) Roomba aka a floor-cleaning robot. I wanted to work on a rather simple project over winter break ad the topic of a robot vacuum came up when one of my friends suggested the idea. Honestly I feel like a lot of people have done this before so I primarily did this project just to gain some experience/knowledge. Please keep in mind that this is still a very rough build and there is a lot of stuff I could improve on for this project and also a lot of stuff that I still want to do. I can elaborate on this later, but basically it would have been way better if I actually could get reliable access to a 3d printer... 
As you can see in the following picture of the roomba (I'll be calling it that from now on), a lot of it is being held on with cardboard and tape. 

![alt text](https://github.com/MRFluffyNBS/Floor-Cleaning-Robot/blob/main/images/IMG_6248.jpg "Image of completed roomba")

### Video demo: 
[![Iroomba video demo](http://img.youtube.com/vi/Y5IRyU6TOsk/0.jpg)](http://www.youtube.com/watch?v=Y5IRyU6TOsk)

***Click the image above to play video***

Even though the construction may not be the sturdiest, the "roomba" runs well most of the time and is pretty good at obstacle avoidance given that there isn't a carpet or high beam for the robot to get caught on. Once I can use a 3d printer more often, the next goal would be to construct a sleeker and shorter chassis much like a real roomba so that the robot can move around easier. However, the base plate and wheels of the robot are 3d printed, however, there are also parts of the design that I would like to improve on seeing that I could only get stuff 3d printed once at my library. I have also included the CAD files in the repo. 

## Overview

The microcontroller I am using is an esp32 chip mounted on an Adafruit feather Huzzah32. A normal Arduino uno or most other microcontrollers can be used as well I just used the esp32 because of its wifi features because I also want to implement some web server functionality in the future as well (such as remote control options and updating on status). The motor driver I'm using is a DRV8833 motor driver with two H bridges. It can supply up to 1.5A and I am using two n20 motors geared at about 200 rpm to drive the Roomba wheels. The motor for the vacuum is an RS360 motor and I am just powering that with 6 AA batteries and a MOSFET to turn the vacuum on/off. I am using two HC-SR04 ultrasonic sensors to detect obstacles and two ir proximity sensors to detect if there is a fall off such as the edge of stairs. 

<img src="https://github.com/MRFluffyNBS/Floor-Cleaning-Robot/blob/main/images/feather.jpg" alt="adafruit feather" style="width:40%; height:auto;" />
Adafruit Feather Huzzah ESP32

## Step 1: Chassis + wheels
<p float="left">
  <img src="https://github.com/MRFluffyNBS/Floor-Cleaning-Robot/blob/main/images/cad1.jpg" alt="Chassis 1" style="width:40%; height:auto;" /> 
  <img src="https://github.com/MRFluffyNBS/Floor-Cleaning-Robot/blob/main/images/cad2.jpg" alt="Chassis 2" style="width:40%; height:auto;" />
</p>



## Step 2: Motor driver + Motors
<img src="https://github.com/MRFluffyNBS/Floor-Cleaning-Robot/blob/main/images/initial%20wiring.jpg" alt="Chassis 2" style="width:40%; height:auto;" />
In order to control the motor driver, you have to use a H bridge that allows for motors to be run both forward and backward. A H bridge consists of basically 4 transistors. The transistors or switches alternate between npn and pnp resistors, so when a HIGH signal is applied to one side, it turns a switch on and the other switch off. This prevents short circuits and means you only need two inputs to control a h bridge. The motor driver I used had two H bridges so it could control two motors. For each pair of inputs, I connected two GPIO pins on the ESP32. These inputs corresponded to the two wires leading to the motors. To turn the motors on in either direction you just need to set one input pin to HIGH and the other one to LOW. In order to control speed, I made sure all GPIO pins supported PWM. Just use PWM on the input that is normally set HIGH to control the motor speed. 

## Step 3: Sensors 
<img src="https://github.com/MRFluffyNBS/Floor-Cleaning-Robot/blob/main/images/updated_all_sensors.jpg" alt="Chassis 2" style="width:40%; height:auto;" />
For sensors, I used two ultrasonic sensors on the front end of the roomba. If a sensor detects an object in front of it, the roomba turns a random angle the other direction. The same logic is applied to the IR sensors but instead, they are there to make sure there is always a solid floor beneath. The ultrasonic sensor works by sending out a pulse that bounces off an object and is then read by the sensor. The code for this is fairly simple and can be easily found online. Just make sure to account for a 0 in the reading because sometimes the sensor times out and doesn't output a valid reading. This could erroneously trigger that an object is detected in front. 

## Step 2: Motor and Sensor Libraries 
To make writing code easier and allow for better integration of the software when writing a pathfinding algorithm/future setting up for remote use, I made separate classes for turning the motors and object detection for both the ultrasonic sensors and IR proximity sensors. Using these classes, I could create simple functions such as forward/reverse to move the Roomba and also one single command to check if there is an object in front of the sensors. I wrote these classes a separate file in the format of Arduino libraries. They are split into two files each with a .h file for method/class prototypes and a .cpp file for the actual implementation. This [video](https://www.youtube.com/watch?v=IiZl3p-ZohM) goes into it in more detail. 

## Step 5: Powering the Roomba 


## Step 6: Vacuum 

## Step 7: Putting everything together 

## Extra + TODO: Wireless Controlling with ESP32


