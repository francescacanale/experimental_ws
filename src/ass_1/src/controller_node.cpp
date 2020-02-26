#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "gazebo_msgs/ModelStates.h"
#include "gazebo_msgs/LinkStates.h"
#include <std_msgs/Int32.h>
#include <ass_1/GetPosition.h>
#include <tf/transform_listener.h>

#include <iostream>
#include <fstream>
#include <istream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

ros::Publisher pub;
ros::ServiceClient client;

bool arrived = true;		// Variable for knowing if the robot is arrived to the target position
bool completed = false;		// Variable for kwnowing when the whole map has been visited
int *goal= new int [4];		// Variable to store the target positions and the velocities


void completedCallback(const std_msgs::Int32::ConstPtr& msg) {
	int a = msg->data; 
	if(a == 1) {
		cout<<"***Game over***\n";
		completed = true;

		// When the game is over the robots are stopped
		geometry_msgs::Twist vel3;
		vel3.linear.x = 0;
		vel3.linear.y = 0;
		vel3.angular.z = 10;		// Little drift
		pub.publish(vel3);
	}		   
}


// Function to compute the euclidean distance between the actual position of the robot and the target position
float euclideanDistance(double actual_x, double actual_y, int goal_x, int goal_y) {
	return sqrt(pow((goal_x - actual_x),2) + pow((goal_y - actual_y), 2));
}


// Callback for the odometry messages
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
	
	// Odometry of the robot
	double x_current = msg->pose.pose.position.x;
	double y_current = msg->pose.pose.position.y;

	if (arrived == true) {
		
		arrived = false;

		// Calling the service to know the target position and the direction of the velocity
		ass_1::GetPosition srv;
		srv.request.my_position_x = x_current;
		srv.request.my_position_y = y_current;
		client.call(srv);

		goal[0] = srv.response.target_x;
		goal[1] = srv.response.target_y;
		goal[2] = srv.response.vel_x;
		goal[3] = srv.response.vel_y;
	}

	float distance = euclideanDistance(x_current, y_current, goal[0], goal[1]);
	float distance_tolerance = 0.1;

	// If I'm not arrived to the target position yet, I give the velocities to the robot
	if(distance >= distance_tolerance && completed == false) { 
		geometry_msgs::Twist vel;
		vel.linear.x = 0.5 * goal[2];
		vel.linear.y = 0.5 * goal[3];
		pub.publish(vel);
	}
	// If I'm arrived to the traget position the robot stops
	else { 
		arrived = true; 
		geometry_msgs::Twist vel2;
		vel2.linear.x = 0;
		vel2.linear.y = 0;
		pub.publish(vel2);
	}
}
	

int main(int argc, char **argv) {

	// Initializing the vector for the target positions and for the velocities
   	goal[0] = 0;
	goal[1] = 0;
	goal[2] = 0;
	goal[3] = 0;

	ros::init(argc, argv, "controller");
	ros::NodeHandle n;
	pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 5);		// Publisher of the velocities

	// Initializing the service client
	client = n.serviceClient<ass_1::GetPosition>("/goal_position");

	ros::Subscriber sub_completed = n.subscribe("/completed", 5, completedCallback);	// Subscriber to completed topic
	ros::Subscriber sub = n.subscribe("odom",1000, odomCallback);						// Subcriber to the odometry
	ros::Rate loop_rate(10);
	ros::spin();
	return 0;
}
