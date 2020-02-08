# Experimental Robotics Laboratory - First Assignment

### Download the .zip file correspondent to the workspace in the user home folder, then unzip the package folder and access it:
$ cd home/experimental_ws

### To source the environment:
`$ source devel/setup.bash`

### To build the package:
`$ catkin_make`

## MAP
There are 4 maps available that the user can choose. To load the desired map the user has to change the name of the map modifying the string with its name at line[479] in the service_node.cpp. The user can find this executable accessing the folder through the command:
`$ cd /src/ass_1/src`

The names of the possible maps that the user can choose and their dimensions are: "map_1.txt" (6x10), "map_2.txt" (12x6), "map_3.txt" (6x6), "map_4.txt" (11x13). These can be found in the following path: 
/home/experimental_ws/src/ass_1/map

Each map corresponds to a matrix composed by values equal to:
- -1 which correspond to an obstacle
- positive integers corresponding to the number of times for which the node has been visited. 
All the nodes which are not obstacles are initialized to 0 in the txt file corresponding to the maps and once the robot visits one of them, their value will be incremented by one unit.

## ROSLAUNCH
There are 4 launch files in the launch folder; the difference between them is the number of robots spawned during the initialization and their initial positions. In order to run a launchfile, once accessed the ass_1 package folder, write on the terminal the following command :
`$ roslaunch ass_1 <name_launch>`

To select the desired launchfile the user has to substitute the variable <name_launch> with one of the following string depending on which type of simulation he wants to run:
1) gazebo_1robot.launch : simulation with only one robot
2) gazebo_2robots.launch : simulationwith 2 robots
3) gazebo_3robots.launch : simulation with 3 robots
4) gazebo_4robots.launch : simulation with 4 robots

In order to choose the initial position of the n robots the user has to pass them as parameters while running the lunchfile choosen as in the following example:
`$ roslaunch ass_1 gazebo_2robots.launch x1:=2 y1:=2 x2:=1 y2:=3`
In this example the robot1 will start in position (2,2) while robot2 in position(1,3). 

If the user do not pass the parameters while running the launchfile the default parameter will be used.
The default parameters depend on the launch file the user wants to run according to the following:
1) x1=-1 y1=1;
2) x1=-1 y1=1, x2=4 y2=-1;
3) x1=-1 y1=1, x2=1 y2=-1, x3=4 y3=-1;
4) x1=-1 y1=1, x2=1 y2=-1, x3=-1 y3=4, x4=4 y4=-1;

The description of the models of the robot can be found inside the files contained in the folder "urdf" inside the src folder of the package ass_1.

## GOAL OF THE ASSIGNMENT
### The goal is to make the robots exploring the map until all the nodes are visited at least once.
A critical issue of our code is represented from the fact that sometimes during the exploration, some robots could bump in each other since the unique possible target choice for one of them is the node that also another robot is visiting at that moment. In case of crash it is adviced to stop the simulation and trying to set different initial positions for the robots.

# Experimental Robotics Laboratory - Second Assignment
## Camera detect the ball
## Simulate robot kick the ball
## Improve movement to the robot 
### How to connect Arduino to Raspberry via ROS
Il codice prende ispirazione da qui, seguire questi comandi: https://github.com/mktk1117/six_wheel_robot/wiki/Make-a-ROS-package-to-communicate-with-Arduino-to-control-motors
Più dettagli sulla comunicazione Arduino/Raspberry: https://github.com/mktk1117/six_wheel_robot/wiki/Communication-between-Arduino-and-Raspberry-Pi


