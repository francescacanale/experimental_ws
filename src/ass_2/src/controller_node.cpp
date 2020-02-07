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
ros::Subscriber positions_sub;

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

	if(robot_yaw > yaw + 0.1 && robot_yaw < yaw + M_PI - 0.1 && abs(misalignment) > 0.1) {
		cout<<"A\n";
		geometry_msgs::Twist vel;
		vel.angular.z = 0.5 * abs(misalignment);
		pub.publish(vel);
	}
	else if ((robot_yaw > yaw + M_PI + 0.1 || robot_yaw < yaw - 0.1) && abs(misalignment) > 0.1) {
		cout<<"B\n";
		geometry_msgs::Twist vel;
		vel.angular.z = - 0.5 * abs(misalignment);
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
	int sign_v = 0;

	// Computing if the robot after translation will be behind/ahead the ball
	bool behind;
	float y_ball_robot;
	float y_robot_new;
	float dis_rette = abs(p-q)/sqrt(pow(m,2) + 1);

	// Case 1: P>Q
	if (p>q) {
		if (m>0) {
			y_robot_new = robot[1] - dis_rette*sin(M_PI/2-m);
			sign_v = -1;
		}
		else {
			y_robot_new = robot[1] - dis_rette*sin(m-M_PI/2);
			sign_v = 1;
		}
		if (robot[1] < ball[1]) { // If the robot is now behind the ball
			y_ball_robot = ball[1];
		}
		else { // If the robot is now ahead the ball
			y_ball_robot = robot[1];
		}
		if(y_ball_robot < y_robot_new) {
			behind = false;
		}
		else {
			behind = true;
		}
	}
	// Case 2: P<Q
	else {
		if (m>0) {
			y_robot_new = robot[1] + dis_rette*sin(M_PI/2-m);
			sign_v = 1;
		}
		else {
			y_robot_new = robot[1] + dis_rette*sin(m-M_PI/2);
			sign_v = -1;
		}
		if (robot[1] < ball[1]) { // If the robot is now behind the ball
			y_ball_robot = ball[1];
		}
		else { // If the robot is now ahead the ball
			y_ball_robot = robot[1];
		}

		if(y_ball_robot < y_robot_new + 0.5) {
			behind = false;
		}
		else {
			behind = true;
		}
	}

	// If the robot is not behind it has to go back
	if (behind == false) {
		geometry_msgs::Twist vel;
		vel.linear.x = -1;
		vel.linear.y = 0;
		pub.publish(vel);
	}
	// When it is behind it has to do nothing
	else {
		geometry_msgs::Twist vel;
		vel.linear.x = 0;
		vel.linear.y = 0;
		pub.publish(vel);
	}

	// If the robot is aligned and behind the ball it has to go on the trajectory ball-porta
	if(aligned && behind) {
		if (abs(distance) > 0.04) {
			geometry_msgs::Twist vel;
			vel.linear.y = 0.5 * abs(distance) * sign_v;
			vel.linear.x = 0;
			pub.publish(vel);
		}
		else {
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
	cout<<"\nDistance: ";
	cout<<distance;

	if(distance > 0.25 && iannone == false) {
		geometry_msgs::Twist vel;
		vel.linear.x = 1;
		vel.linear.y = 0;
		pub.publish(vel);
	}
	else {
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
