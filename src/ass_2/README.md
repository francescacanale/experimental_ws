# Experimental Robotics Laboratory - Second Assignment

### Download the .zip file correspondent to the workspace in the user home folder, then unzip the package folder and access it:
```
$ cd home/experimental_ws
```

### To source the environment:
```
$ source devel/setup.bash
```

### To build the package:
```
$ catkin_make
```

### Link to Robot
Enter in the raspberry via ssh. Be sure you are under the same Network of RaspPi.
```
$ ssh-keygen -R raspberrypi.local
```
```
$ ssh pi@raspberrypi.local
```

Enter the password and you are inside RaspPi. (remember: default psw "raspberry").
Once you are inside start roscore:
```
$ roscore
```
Open on your PC a new terminal.
Export the ROS_IP and the MASTER_URI
```
$ export ROS_IP=<localhost of PC>
```
```
$ export ROS_MASTER_URI=http://<localhost of RaspPI>:11311
```
Do this every time you open a terminal on PC, to link it to RaspPI roscore
Open a new window terminal and launch the file needed

## Camera detect the red ball
In RaspberryPi (with the roscore already launched)
```
$ rosrun raspicam_node rasp_image_compressed
```
!!"Use tab..."!!

From PC launch ball detection:
Go to the folder in which is present the python file
```
$ cd experimental_ws/src/ass_2>
```
```
$ python2 ball_detection.py>
```
[Code Detection](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/src/ball_detection.py)

## Simulate robot kick the ball
```
$ roslaunch ass_2 gazebo_robot_world.launch
```
and run the simulation.
[Code Launch](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/launch/gazebo_robot_world.launch)
[Code Controller](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/src/controller_node.cpp)

## Improve movement to the robot
With roscore active on RaspPi, open a new terminal (on RaspPI):
```
$ rosrun motor_driver motor_driver.py
```
[Code Raspberry Pi](https://github.com/francescacanale/experimental_ws/blob/master/src/motor_driver/scripts/motor_driver.py)
Launch again the simulation on gazebo.
Be sure on Arduino the code motor_driver.ino is running.
[Code Arduino](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/arduino_motors/motor_driver/motor_driver.ino)
Be sure the serial connection between RaspPi and Arduino is working.

How to connect Arduino to Raspberry via ROS.
The inspiration code is [this](https://github.com/mktk1117/six_wheel_robot/wiki/Make-a-ROS-package-to-communicate-with-Arduino-to-control-motors).

