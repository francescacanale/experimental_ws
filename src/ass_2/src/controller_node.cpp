#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "gazebo_msgs/ModelStates.h"
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

bool aligned = false;
bool onTrajectory = false;
bool iannone = false;
double robot_roll, robot_pitch, robot_yaw;
float yaw, q, m;


float *ball= new float [2]; //Variable to store the ball position
float *porta= new float [2]; //Variable to store the porta position
float *robot= new float [2]; //Variable to store the robot position
 

float round_cazzo (float var) {
	float var_rounded = floor(var*10)/10;
	return var_rounded;
}

// Function to align the robot
void alignment(float yaw, double robot_yaw) {
	
	// Misalignment between the orientation of the robot and the line ball-porta
	float misalignment = yaw - robot_yaw;

	if(robot_yaw > yaw + 0.05 && robot_yaw < yaw + M_PI - 0.05 && abs(misalignment) > 0.05) {
		cout<<"Clockwise\n";
		geometry_msgs::Twist vel;
		vel.angular.z = - 0.5 * misalignment;
		pub.publish(vel);
	}
	else if ((robot_yaw > yaw + M_PI + 0.05 || robot_yaw < yaw - 0.05) && abs(misalignment) > 0.05) {
		cout<<"Anticlockwise\n";
		geometry_msgs::Twist vel;
		vel.angular.z = + 0.5 * misalignment;
		pub.publish(vel);
	}
	else {
		aligned = true;
		cout<<"Aligned\n";
		geometry_msgs::Twist vel;
		vel.angular.z = 0;
		pub.publish(vel);
	}
}


// Function to move the robot to the trajectory ball-porta
void moveToTrajectory(float q) {

	float p = -m*robot[0] + robot[1]; //y coordinate at the origin of the line of the aligned robot
	float distance_rette = abs(p-q)/sqrt(pow(m,2) + 1);
	int sign_v = 0; // Sign of the velocities

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
		if(ball[1] < y_robot_new + 0.5) {
			behind = false;
		}
		else {
			behind = true;
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
		if(ball[1] < y_robot_new + 0.5) {
			behind = false;
		}
		else {
			behind = true;
		}
	}

	// If the y_robot_new is not behind the ball, the robot has to go back
	if (behind == false) {
		cout<<"INDIETRO\n";
		geometry_msgs::Twist vel;
		vel.linear.x = -0.5;
		vel.linear.y = 0;
		pub.publish(vel);
	}

	// If the robot is aligned and behind the ball it has to go on the trajectory ball-porta
	if(aligned && behind) {
		if (abs(distance_rette) > 0.1) {
			cout<<"TRASLO\n";
			geometry_msgs::Twist vel;
			vel.linear.y = 0.2 * abs(distance_rette) * sign_v;
			vel.linear.x = 0;
			pub.publish(vel);
		}
		else {
			cout<<"Ho traslato\n";
			onTrajectory = true;
			geometry_msgs::Twist vel;
			vel.linear.x = 0;
			vel.linear.y = 0;
			pub.publish(vel);
		}
	}
}


// Function to kick the ball
void kick() {

	// Distance between the robot and the ball
	float distance = sqrt(pow(ball[0]-robot[0],2) + pow(ball[1]-robot[1],2));
	//cout<<"\nDistance: ";
	//cout<<distance;

	if(distance > 0.29 && iannone == false) {
		cout<<"AVANZO\n";
		geometry_msgs::Twist vel;
		vel.linear.x = 1;
		vel.linear.y = 0;
		pub.publish(vel);
	}
	else {
		cout<<"Colpito!\n";
		iannone = true;
		geometry_msgs::Twist vel;
		vel.linear.x = 0;
		vel.linear.y = 0;
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

	m = (porta[1]-ball[1])/(porta[0]-ball[0]); //Angular coefficent of the line bal--porta
	q = (porta[0]*ball[1] - ball[0]*porta[1])/(porta[0] - ball[0]); //y coordinates at the origin of the line ball_porta
	yaw = atan(m); //Yaw angle wrt y axis of the world frame
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
