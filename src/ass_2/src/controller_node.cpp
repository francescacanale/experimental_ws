#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "gazebo_msgs/ModelStates.h"
#include "gazebo_msgs/LinkStates.h"
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
ros::Publisher pub_robot;

bool aligned = false;
bool onTrajectory = false;
bool iannone = false;
bool start = true;
bool ok_behind = false;
double robot_roll, robot_pitch, robot_yaw;
float yaw, q, m;
geometry_msgs::Twist tmp;


//Define the initial variable
float *ball= new float [2]; 		//Variable to store the ball initial position
float *moving_ball= new float [2]; 	//Variable to store the moving ball position
float *porta= new float [2]; 		//Variable to store the porta initial position
float *robot= new float [2]; 		//Variable to store the robot position
 
bool controlVelocities(geometry_msgs::Twist vel) {
	
	//geometry_msgs::Twist tmp;
	if (vel.linear.x == tmp.linear.x && vel.linear.y == tmp.linear.y && vel.angular.z == tmp.angular.z) {
			return false;
	}
	else {
			tmp = vel;
			return true;
	}
}


// Function to align the robot
void alignment(float yaw, double robot_yaw) {
	// Misalignment between the orientation of the robot and the line ball-porta
	float misalignment = yaw - robot_yaw;

	if (start) {
		cout<<"START\n";									
		geometry_msgs::Twist vel;
		vel.linear.x =  0.3 ;
		start = false;
		pub_robot.publish(vel);
	}

	if(robot_yaw > yaw + 0.05 && robot_yaw < yaw + M_PI - 0.05 && abs(misalignment) > 0.05) {
		cout<<"Clockwise\n";									//Moving Clockwise to orient the robot
		geometry_msgs::Twist vel;								//Message Twist vel
		vel.angular.z = - 0.3 * misalignment/abs(misalignment);	//Giving an angular velocity aroung z axis
		pub.publish(vel);
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else if ((robot_yaw > yaw + M_PI + 0.05 || robot_yaw < yaw - 0.05) && abs(misalignment) > 0.05) {
		cout<<"Anticlockwise\n";								//Moving Anti-Clockwise to orient the robot
		geometry_msgs::Twist vel;								//Message Twist vel
		vel.angular.z = + 0.3 * misalignment/abs(misalignment);	//Giving an angular velocity aroung z axis
		pub.publish(vel);
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else {
		aligned = true;
		cout<<"Aligned\n";			//The robot is finally aligned
		geometry_msgs::Twist vel;	//Message Twist vel
		vel.angular.z = 0;			//No angular velocity
		pub.publish(vel);
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
}


// Function to move the robot to the trajectory ball-porta
void moveToTrajectory(float q) {
	float p = -m*robot[0] + robot[1]; 						//y coordinate at the origin of the line of the aligned robot
	float distance_rette = abs(p-q)/sqrt(pow(m,2) + 1);		//Distance btw to parallel lines
	int sign_v = 0; 										//Sign of the velocities

	// Computing if the robot after translation will be behind/ahead the ball
	bool behind;
	float y_robot_new; // y coordinate that the robot will have after the translation

	// Case 1: P>Q
	if (p>q) {
		if (m>0) {
			y_robot_new = robot[1] - abs(distance_rette*sin(M_PI/2-m));
			sign_v = -1;
		}
		else {
			y_robot_new = robot[1] - abs(distance_rette*sin(m-M_PI/2));
			sign_v = 1;
		}
		if(ball[1] < y_robot_new + 1) {
			behind = false;
		}
		else {
			//behind = true;
			ok_behind = true;
		}
	}
	// Case 2: P<Q
	else {
		if (m>0) {
			y_robot_new = robot[1] + abs(distance_rette*sin(M_PI/2-m));
			sign_v = 1;
		}
		else {
			y_robot_new = robot[1] + abs(distance_rette*sin(m-M_PI/2));
			sign_v = -1;
		}
		if(ball[1] < y_robot_new + 1) {
			behind = false;
		}
		else {
			behind = true;
			ok_behind = true;
		}
	}

	// If the y_robot_new is not behind the ball, the robot has to go back
	if (ok_behind == false) {
		cout<<"BACK\n";
		geometry_msgs::Twist vel;
		vel.linear.x = -0.2;
		pub.publish(vel);
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}

	// If the robot is aligned and behind the ball it has to go on the trajectory ball-porta
	if(aligned && ok_behind) {
		if (abs(distance_rette) > 0.1) {
			cout<<"TRASLATION\n";
			geometry_msgs::Twist vel;
			vel.linear.y = 0.2 * sign_v;
			pub.publish(vel);
			if (controlVelocities(vel))
				pub_robot.publish(vel);
		}
		else {
			cout<<"Ho traslato\n";
			onTrajectory = true;
			geometry_msgs::Twist vel;
			vel.linear.x = 0;
			vel.linear.y = 0;
			pub.publish(vel);
			if (controlVelocities(vel))
				pub_robot.publish(vel);

		}
	}
}

	
// Function to kick the ball
void kick() {

	// Distance between the robot and the ball
	float distance = sqrt(pow(ball[0]-robot[0],2) + pow(ball[1]-robot[1],2));

	if(iannone == false && moving_ball[0] == ball[0] && moving_ball[1] == ball[1]) {
		cout<<"GO FORWARD\n";
		geometry_msgs::Twist vel;
		vel.linear.x = 0.3;
		pub.publish(vel);
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else {
		cout<<"Kick!\n";
		iannone = true;
		geometry_msgs::Twist vel;
		vel.linear.x = 0;
		vel.linear.y = 0;
		pub.publish(vel);
		if (controlVelocities(vel))
			pub_robot.publish(vel);
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

		if (onTrajectory == false) {
			// Calling the function to move the robot to trajectory ball-porta
			moveToTrajectory(q);
		}
		else {

			if (iannone == false) {
				// Calling the function to kick the ball
				kick();
				}
			else {}
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

	m = (porta[1]-ball[1])/(porta[0]-ball[0]); 						//Angular coefficent of the line bal--porta
	q = (porta[0]*ball[1] - ball[0]*porta[1])/(porta[0] - ball[0]); //y coordinates at the origin of the line ball_porta
	yaw = atan(m); 													//Yaw angle wrt y axis of the world frame
}

// Callback for the model of the moving objects
void linkCallback(const gazebo_msgs::LinkStates::ConstPtr& msg)
   {
	//Position of the ball
    moving_ball[0] = msg->pose[1].position.x;
    moving_ball[1] = msg->pose[1].position.y;
}
	

int main(int argc, char **argv)
{
	ros::init(argc, argv, "controller");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	while (1) {
		//Subscribing to the position topic
		ros::Subscriber robot_sub = n.subscribe("odom", 1000, odomCallback); 					//Subcriber to the odometry of the robot
		ros::Subscriber moodel_sub = n.subscribe("/gazebo/model_states", 1000, modelCallback); 	//Subcriber to the initial position of the objects
		ros::Subscriber link_sub = n.subscribe("/gazebo/link_states", 1000, linkCallback); 		//Subcriber to the moving position of the objects
		pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);
		pub_robot = n.advertise<geometry_msgs::Twist>("robot/cmd_vel", 100);
		
	    ros::spin();
	    loop_rate.sleep();
    }




	return 0;
}
