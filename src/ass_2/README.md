# Second Assignment - Autonomous Soccer-Robot

## GOAL OF THE ASSIGNMENT
### The goal is to build a omnidirectinal wheeled robot that should be able to detect a red ball and push it towards a goal.

## CODE ARCHITECTURE
Our code architecture can be summarized in three tasks described in the following picture:
<p align="center">
 <img src="ExRob Diagram.png"/>
</p>

## THE ROBOT
The robot was built using a kit that contains:
- Arduino (dire modello)
- Raspberry (dire modello)
- Camera (dire modello)
- 4 omni-directional wheels
- .....

## GETTING STARTED
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
### Prepare your RaspberryPi
DIRE DI INSTALLARE ROS + OPENCV
METTERE LINK A SITO CHE ABBIAMO USATO PER FARE TUTTO (FLASHARE, METTERE WIFI...)

### Link between PC and RaspberryPi:
Enter in the raspberry via ssh.

Be sure you are under the same Network of RaspPi.
```
$ ssh-keygen -R raspberrypi.local
```
```
$ ssh pi@raspberrypi.local
```

Enter the password (default psw "raspberry") and you are inside RaspPi.

Once you are inside export the ROS_IP:
```
$ export ROS_IP=<localhost of RaspPi>
```
and then start roscore:
```
$ roscore
```
Open a new terminal on your PC.
Export the ROS_IP and the MASTER_URI
```
$ export ROS_IP=<localhost of PC>
```
```
$ export ROS_MASTER_URI=http://<localhost of RaspPI>:11311
```
Do this every time you open a new terminal on your PC, to link it to RaspPI roscore.

## TASK 1: RED BALL DETECTION
In RaspberryPi (with the roscore already launched):
```
$ roslaunch raspicam_node camerav2_410x308_10fps.launch
```

From your PC launch [Ball Detection Code](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/src/ball_detection.py):

Go to the folder in which is present the python file:
```
$ cd experimental_ws/src/ass_2/src
```
```
$ python2 ball_detection.py
```

## TASK 2: SIMULATION IN GAZEBO
To run the simulation of the robot kicking a ball in gazebo, from your PC launch [Robot Controller Code](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/src/controller_node.cpp):
```
$ cd experimental_ws
```
```
$ roslaunch ass_2 gazebo_robot_world.launch
```
and run the simulation.

You can easly change the starting position/orientation of the robot by changing it in the [Launch file](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/launch/gazebo_robot_world.launch).

You can also change the starting position of the ball and the goal by changing it in the [Gazebo World file] (https://github.com/francescacanale/experimental_ws/blob/master/src/crestino_gazebo/worlds/crestino.world)

## TASK 3: MAKE THE REAL ROBOT MOVE
With roscore active on RaspPi, open a new RaspPi terminal and go inside catkin workspace:
```
$ cd catkin_ws
```
then run the [Motor Code Raspberry Pi](https://github.com/francescacanale/experimental_ws/blob/master/src/motor_driver/scripts/motor_driver.py):
```
$ rosrun motor_driver motor_driver.py
```
Then launch again the simulation in Gazebo.

Be sure on Arduino the [Code Arduino](https://github.com/francescacanale/experimental_ws/blob/master/src/ass_2/arduino_motors/motor_driver/motor_driver.ino) is running and be sure the serial connection between RaspPi and Arduino is working.

How to connect Arduino to Raspberry via ROS.
The inspiration code is [this](https://github.com/mktk1117/six_wheel_robot/wiki/Make-a-ROS-package-to-communicate-with-Arduino-to-control-motors).


