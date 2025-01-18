# Floor-Cleaning-Robot
This is my attempt at making a (knockoff) Roomba aka a floor-cleaning robot. I wanted to work on a project over winter break and one of my friends suggested this for some reason, so I was like why not? Please keep in mind that this is still a very rough build and there is a lot of stuff I could improve on for this project and also a lot of stuff that I still want to do. I can elaborate on this later, but basically it would have been way better if I actually could get reliable access to a 3d printer... 
As you can see in the following picture of the roomba (I'll be calling it that from now on), a lot of it is being held on with cardboard and tape. 

![alt text](https://github.com/MRFluffyNBS/Floor-Cleaning-Robot/blob/main/images/IMG_6248.jpg "Image of completed roomba")

### Video demo: 
[![Iroomba video demo](http://img.youtube.com/vi/Y5IRyU6TOsk/0.jpg)](http://www.youtube.com/watch?v=Y5IRyU6TOsk)

Click the image above to play video 

Even though the construction may not be the sturdiest, the "roomba" runs well most of the time and is pretty good at obstacle avoidance given that there isn't a carpet or high beam for the robot to get caught on. Once I can use a 3d printer more often, the next time would be to construct a sleeker and shorter chassis much like a real roomba so that the robot can move around easier. However, the base plate and wheels of the robot are 3d printed, however, there are also parts of the design that I would like to improve on seeing that I could only get stuff 3d printed once at my library. I have also included the CAD files in the repo. 

## Overview

The microcontroller I am using is an esp32 chip mounted on an Adafruit feather Huzzah32. A normal Arduino uno or most other microcontrollers can be used as well I just used the esp32 because of its wifi features because I also want to implement some web server functionality in the future as well (such as remote control options and updating on status). The motor driver I'm using is a DRV8833 motor driver with two H bridges. It can supply up to 1.5A and I am using two n20 motors geared at about 200 rpm to drive the Roomba wheels. The motor for the vacuum is an RS360 motor and I am just powering that with 6 AA batteries and a MOSFET to turn the vacuum on/off. I am using two HC-SR04 ultrasonic sensors to detect obstacles and two ir proximity sensors to detect if there is a fall off such as the edge of stairs. 
