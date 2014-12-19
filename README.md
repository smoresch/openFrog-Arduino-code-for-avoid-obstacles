openFrog
========

FROG v2.0

An Arduino sketch for move a robot avoiding obstacles using distance sensor HC-SR04, and HUB-ee wheels.

The name 'frog' is from the sensor HC-SR04, the "head" of the robot.. it locks like a frog =P

The purpose of this project is to improve the ability of this arduino sketch to avoid obstacles. Anyone can use this code. 
Contact me at moreschisimone@gmail.com for info about hardware. Now i have one HC-SR04 sensor in front of the robot, and two HUB-ee wheels.

Any suggestion is appreciated to improve the robot. Hardware and software, too.

Frog is a low cost robot.

Actual supported and managed hardware:

- 1x HC-SR04 distance sensor
- 2x HUB-ee wheels for turn right and left
- 1x Arduino ONE board
- 3x LED 
	1 Yellow led for power on/off
	2 Red led on the back side, like car STOP. They switch ON when distance sensor detect an obstacle.
- 1x Button for start/stop the robot
- 2x 9V batteries (6LR61 type), one for power arduino and sensors, and one for power the wheels.

Has i have experienced, is useful to have two different source power for arduino and wheels, for avoid power problem to arduino board.


In this sketch you can set this variables:
<br><br>
<b>Basic settings</b>
- int maxSpeed = 140;  //  Speed when robot go forward (0-255)
- int turnSpeed = 120;  //  Speed when robot turn right/left (0-255)
- int secureDistance = 15;  //  cm
- int turnSecureDistance = 40;  //  cm
- int timeBeforeTurn = 1000;  //  Time in milliseconds for start turn when robot detect obstacles and stops.


<b>Advanced settings</b>
- int pending = 6;  //  Current number of pending turn action 
- int totPending = 6;   //  Minimum number of arduino loops for turn the robot when detect obstacles. After this number of loops robot continue to detect distance for detect if it can go forward or continue to turn for avoid obstacles. The degrees the robot turns depends from: this variables, turn speed and main loop delay.
          
