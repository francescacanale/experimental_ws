#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "gazebo_msgs/ModelStates.h"
//#include "ass_1/GetPosition.h"
#include <std_msgs/Int32.h>
#include <tf/transform_listener.h>

#include <iostream>
#include <fstream>
#include <istream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

ros::Publisher pub;
ros::Subscriber positions_sub;
//ros::ServiceClient client;

// Needed only in the real world:
//ros::Subscriber sub_ball;
//ros::Subscriber sub_robot;

bool object_detected = false;
bool aligned = false;
bool onTrajectory = false;
bool iannone = false;
double robot_roll, robot_pitch, robot_yaw;
float yaw, q, m;


float *ball= new float [2]; //Variable to store the ball position
float *porta= new float [2]; //Variable to store the porta position
float *robot= new float [2]; //Variable to store the robot position
 

// Function to align the robot
void alignment(float yaw, double robot_yaw) {
	
	// Misalignment between the orientation of the robot and the line ball-porta
	float misalignment = yaw - robot_yaw;

	if(abs(misalignment) < (M_PI - 0.02) && abs(misalignment) > 0.02) {
		geometry_msgs::Twist vel;
		vel.angular.z = 0.5 * misalignment;
		pub.publish(vel);
	}

	else {
		aligned = true;
		geometry_msgs::Twist vel;
		vel.angular.z = 0;
		pub.publish(vel);
	}
}

// Function to move the robot to the trajectory ball-porta
void moveToTrajectory(float q) {

	//y coordinate at the origin of the line of the aligned robot
	float p = -m*robot[0] + robot[1];

	float distance = q - p;
	
	if(aligned) {
		if (abs(distance) > 0.04) {
			geometry_msgs::Twist vel;
			vel.linear.y = 0.5 * distance;
			pub.publish(vel);
		}
		else {
			onTrajectory = true;
			geometry_msgs::Twist vel;
			vel.linear.y = 0;
			pub.publish(vel);
		}
	}
}

// Function to kick the ball
void kick() {



	if (behind == true) {
		if(distance > 0.25 && iannone == false) {
			geometry_msgs::Twist vel;
			vel.linear.x = 1;
			pub.publish(vel);
		}
		else {
			iannone = true;
			cout<<"IANNONE TRUE\n";
			geometry_msgs::Twist vel;
			vel.linear.x = 0;
			pub.publish(vel);
		}
	}
	else {
		geometry_msgs::Twist vel;
		vel.linear.x = -1;
		pub.publish(vel);
	}

}


// Callback for the odometry of the robot
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
   {	
	//Computing pose robot
    robot[0] = msg->pose.pose.position.x;
    robot[1] = msg->pose.pose.position.y;

	// Computing orientation robot
	tf::Quaternion t(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	tf::Matrix3x3 m(t);
	m.getRPY(robot_roll, robot_pitch, robot_yaw);

	if (aligned == false) {
		// Calling the function to align the robot
		alignment(yaw, robot_yaw);
	}
	else {
		cout<<"I'm alinged\n";

		if (onTrajectory == false) {
			// Calling the function to move the robot to trajectory ball-porta
			moveToTrajectory(q);
		}
		else {
			cout<<"I'm on trajectory\n";

			if (iannone == false) {
				// Calling the function to kick the ball
				kick();
				}
			else
				cout<<"BOOOOM\n";
		}
	}
}

// Callback for the model objects
void modelCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
   {
	//Position of the ball
    ball[0] = msg->pose[1].position.x;
    ball[1] = msg->pose[1].position.y;
	//ball[2] = msg->twist[1].

	//Position of the porta
    porta[0] = msg->pose[2].position.x;
    porta[1] = msg->pose[2].position.y;

	object_detected = true;

	if(object_detected) {
		m = (porta[1]-ball[1])/(porta[0]-ball[0]); //Angular coefficent of the misalignment line
		q = (porta[0]*ball[1] - ball[0]*porta[1])/(porta[0] - ball[0]); //y coordinates at the origin of the misalignment line
		yaw = atan(m); //Yaw angle wrt y axis of the world frame
	}
}
	

int main(int argc, char **argv)
{
	ros::init(argc, argv, "controller");
	ros::NodeHandle n;

	// Publisher of the velocities
	pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 5); 

	//Subscribing to the position topic
	ros::Subscriber robot_sub = n.subscribe("odom", 1000, odomCallback); //Subcriber to the odometry of the robot
	ros::Subscriber moodel_sub = n.subscribe("/gazebo/model_states", 1000, modelCallback); //Subcriber to the position of the objects

	ros::Rate loop_rate(10);
	ros::spin();
	return 0;
}
