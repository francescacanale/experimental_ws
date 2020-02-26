#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <ass_2/Translation.h>
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

// Boolean variable to know the steps of the process
bool aligned = false;
bool behindBall = false;
bool onTrajectory = false;
bool kicked = false;

float yaw, q, m;
geometry_msgs::Twist tmp; 			// Temporary variable for comparing cmd_vel messages
int sign_v = 0;			  		// Sign of the velocities

float *ball = new float[2];			// Variable to store the ball initial position
float *moving_ball = new float[2];		// Variable to store the moving ball position
float *porta = new float[2];			// Variable to store the porta initial position
float *robot = new float[2];			// Variable to store the robot position
double robot_roll, robot_pitch, robot_yaw;	// Variables to store the robot orientation


// Function to decide which velocities give to the robot
bool controlVelocities(geometry_msgs::Twist vel) {

	// The velocity is given to the robot only if it is different form the prevoius given velocity
	if (vel.linear.x == tmp.linear.x && vel.linear.y == tmp.linear.y && vel.angular.z == tmp.angular.z) {
		return false;
	}
	else {
		tmp = vel;
		return true;
	}
}


// Function to align the robot on the line ball-porta
void alignment(float yaw, double robot_yaw) {

	// Misalignment between the orientation of the robot and the line ball-porta
	float misalignment = yaw - robot_yaw;

	// Understand the fastest way to align
	if ((robot_yaw > yaw + M_PI + 0.05 || robot_yaw < yaw - 0.05) && abs(misalignment) > 0.03) {
		cout << "ANTICLOCKWISE\n";					// Moving the robot anti-clockwise
		geometry_msgs::Twist vel;
		vel.angular.z = + 0.3;	// Giving an angular velocity on z axis
		pub.publish(vel);						// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else if ((robot_yaw > yaw + 0.05 && robot_yaw < yaw + M_PI - 0.05) && abs(misalignment) > 0.03) {
		cout << "CLOCKWISE\n"; 						// Moving the robot clockwise
		geometry_msgs::Twist vel;
		vel.angular.z = - 0.3;	// Giving an angular velocity on z axis
		pub.publish(vel);						// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else if ((robot_yaw > yaw + M_PI + 0.05 || robot_yaw < yaw - 0.05) && abs(misalignment) > 0.03) {
		cout << "ANTICLOCKWISE\n";					// Moving the robot anti-clockwise
		geometry_msgs::Twist vel;
		vel.angular.z = + 0.3 * misalignment / abs(misalignment);	// Giving an angular velocity on z axis
		pub.publish(vel);						// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else {
		aligned = true;			// Now the robot is aligned on the ine ball-porta
		cout << "Aligned\n";
		geometry_msgs::Twist vel;
		vel.angular.z = 0;		// Giving a zero angular velocity on z axis
		pub.publish(vel); 		// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
}


// Function to move the robot back if it is not behind the ball
void moveBack() {

	float p = -m * robot[0] + robot[1];				// y coordinate at the origin of the line of the aligned robot
	float distance_rette = abs(p - q) / sqrt(pow(m, 2) + 1);	// Distance btw two parallel lines
	float y_robot_new;						// y coordinate that the robot will have after the translation

	// Case 1: Parallel vertical lines
	if (abs(q) > 100) {
		y_robot_new = robot[1];			// If the lines are vertical the y of the robot remains the same
		if (ball[1] < y_robot_new + 2) { 	// If the robot after the translation will not be behind the ball
			cout << "MOVING BACK\n";        // Moving the robot back
			geometry_msgs::Twist vel;
			vel.linear.x = -0.2;		// Giving a linear velocity on x axis
			pub.publish(vel);		// Publishing the velocity
			if (controlVelocities(vel))
				pub_robot.publish(vel);
		}
		else {
			behindBall = true;		// The robot is now behind the ball
			cout << "Behind the ball\n";
		}
	}
	// Case 2: P>Q
	else if (p > q) {
		if (m > 0) {
			y_robot_new = robot[1] - abs(distance_rette * sin(M_PI / 2 - m));
			sign_v = -1;
		}
		else {
			y_robot_new = robot[1] - abs(distance_rette * sin(m - M_PI / 2));
			sign_v = 1;
		}
		if (ball[1] < y_robot_new + 2) { 	// If the robot after the translation will not be behind the ball
			cout << "MOVING BACK\n";        // Moving the robot back
			geometry_msgs::Twist vel;
			vel.linear.x = -0.2;		// Giving a linear velocity on x axis
			pub.publish(vel);		// Publishing the velocity
			if (controlVelocities(vel))
				pub_robot.publish(vel);
		}
		else {
			behindBall = true;		// The robot is now behind the ball
			cout << "Behind the ball\n";
		}
	}
	// Case 3: P<Q
	else {
		if (m > 0) {
			y_robot_new = robot[1] + abs(distance_rette * sin(M_PI / 2 - m));
			sign_v = 1;
		}
		else {
			y_robot_new = robot[1] + abs(distance_rette * sin(m - M_PI / 2));
			sign_v = -1;
		}
		if (ball[1] < y_robot_new + 2) {	// If the robot after the translation will not be behind the ball
			cout << "MOVING BACK\n";        // Moving the robot back
			geometry_msgs::Twist vel;
			vel.linear.x = -0.2;		// Giving a linear velocity on x axis
			pub.publish(vel);		// Publishing the velocity
			if (controlVelocities(vel))
				pub_robot.publish(vel);
		}
		else {
			behindBall = true;		// The robot is now behind the ball
			cout << "Behind the ball\n";
		}
	}
}


// Function to move the robot on the trajectory ball-porta
void moveToTrajectory() {

	float p = -m * robot[0] + robot[1];				// y coordinate at the origin of the line of the aligned robot
	float distance_rette = abs(p - q) / sqrt(pow(m, 2) + 1);	// Distance btw to parallel lines
	float distance_rette_vertical = robot[0] - ball[0];		// Distance btw two parallel lines, vertical case

	
	if (abs(q) > 100 && abs(distance_rette_vertical) > 0.1) { 	// Particular case of vertical lines
		cout << "TRASLATION\n";					// Moving the robot on the trajectory ball-porta
		geometry_msgs::Twist vel;
		vel.linear.y = 0.2 * distance_rette_vertical / abs(distance_rette_vertical); 	// Giving a linear velocity on y axis
		pub.publish(vel);					// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);

	}
	else if (abs(distance_rette) > 0.1) {		// Normal case of oblique lines
		cout << "TRASLATION\n";			// Moving the robot on the trajectory ball-porta
		geometry_msgs::Twist vel;
		vel.linear.y = 0.2 * sign_v;		// Giving a linear velocity on y axis
		pub.publish(vel);			// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else {
		onTrajectory = true;			// The robot is now on the trajectory ball-porta
		cout << "I've traslated\n";						
		geometry_msgs::Twist vel;
		vel.linear.y = 0;			// Giving a zero linear velocity on y axis
		pub.publish(vel);			// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
}


// Function to kick the ball
void kick() {

	if (moving_ball[0] == ball[0] && moving_ball[1] == ball[1]) {	// If the ball is still
		cout << "GO FORWARD\n";					// Moving the robot foward to kick the ball
		geometry_msgs::Twist vel;
		vel.linear.x = 0.3;					// Giving a linear velocity on x axis
		pub.publish(vel);					// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
	else {
		kicked = true;				// The robot has kicked the ball
		cout << "Kick!\n";
		geometry_msgs::Twist vel;
		vel.linear.x = 0;			// Giving a zero linear velocity on x axis
		pub.publish(vel);			// Publishing the velocity
		if (controlVelocities(vel))
			pub_robot.publish(vel);
	}
}


// Callback for the odometry of the robot
void odomCallback(const nav_msgs::Odometry::ConstPtr &msg)    
{
	// Computing pose of the robot
	robot[0] = msg->pose.pose.position.x;
	robot[1] = msg->pose.pose.position.y;

	// Computing orientation of the robot
	tf::Quaternion t(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	tf::Matrix3x3 m(t);
	m.getRPY(robot_roll, robot_pitch, robot_yaw);	// Getting Roll Pitch and Yaw from the Quaternion

	// Decide the steps to kick the ball
	if (aligned == false) {

		// Calling the function to align the robot
		alignment(yaw, robot_yaw);
	}
	else{
		if (behindBall == false) {

			// Calling the function to move the robot back if it is not behind the ball
			moveBack();
		}
		else {
			if (onTrajectory == false) {

				// Calling the function to move the robot to trajectory ball-porta
				moveToTrajectory();
			}
			else {
				if (kicked == false) {

					// Calling the function to kick the ball
					kick();
				}
				else {}
			}
		}
	}
}


// Callback for the model objects
void modelCallback(const gazebo_msgs::ModelStates::ConstPtr &msg) {

	// Position of the ball
	ball[0] = msg->pose[1].position.x;
	ball[1] = msg->pose[1].position.y;

	// Position of the porta
	porta[0] = msg->pose[2].position.x;
	porta[1] = msg->pose[2].position.y;

	m = (porta[1] - ball[1]) / (porta[0] - ball[0]);			// Angular coefficent of the line ball-porta
	q = (porta[0] * ball[1] - ball[0] * porta[1]) / (porta[0] - ball[0]);	// y coordinates at the origin of the line ball-porta
	yaw = atan(m);								// Yaw angle wrt x axis of the world frame
}


// Callback for the model of the moving ball
void linkCallback(const gazebo_msgs::LinkStates::ConstPtr &msg) {

	// Position of the ball
	moving_ball[0] = msg->pose[1].position.x;
	moving_ball[1] = msg->pose[1].position.y;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "controller");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	while (1) {

		// Defining the Subrscribers
		ros::Subscriber robot_sub = n.subscribe("odom", 1000, odomCallback);			// Subcriber to the odometry of the robot
		ros::Subscriber moodel_sub = n.subscribe("/gazebo/model_states", 1000, modelCallback);	// Subcriber to the initial position of the objects
		ros::Subscriber link_sub = n.subscribe("/gazebo/link_states", 1000, linkCallback);	// Subcriber to the moving position of the ball

		// Defining the Publishers
		pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);		// Publisher of the velocities for Gazebo
		pub_robot = n.advertise<geometry_msgs::Twist>("robot/cmd_vel", 100);	// Publisher of the velocities for Arduino

		ros::spin();
		loop_rate.sleep();
	}

	return 0;
}
