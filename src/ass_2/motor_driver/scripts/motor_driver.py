#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist
import serial

#This script receives messages from "/cmd_vel" and translates them 
#to the rotation signal of each motor. Then, it sends this signals to Arduino. 
#At the same time, it receives messages from Arduino and publishes them to /arduino.

class driver:
    def __init__(self):
        # init ros
        rospy.init_node('car_driver', anonymous=True)           #initialize the node "car_driver"
        rospy.Subscriber('/robot/cmd_vel', Twist, self.get_cmd_vel)   #init sub to "cmd_vel"
        self.ser = serial.Serial('/dev/ttyACM0', 115200)        #init serial transmission via USB
        self.get_arduino_message()                              #init the arduino msg*

    # get cmd_vel message, and get linear velocity and angular velocity
    def get_cmd_vel(self, data):
        x = data.linear.x               # linear vel cmd along x-axis
        y = data.linear.y               # linear vel cmd along y-axis
	angular = data.angular.z        # angular vel cmd
        self.send_cmd_to_arduino(x, y, angular)  #send the command to arduino 

    # translate x, y, and angular velocity to PWM signal of each wheels, and send to arduino
    def send_cmd_to_arduino(self, x, y, angular):
        # calculate right and left wheels' signal
        ant_left = int((x - y - angular) * 80)   #signal to ant-left 
        ant_right = int((x + y + angular) * 80)  #signal to ant-right
        post_left = int((x + y - angular) * 80)  #signal to post-left
        post_right = int((x - y + angular) * 80) #signal to post-right

        # format for arduino
        message = "{},{},{},{}*".format(ant_left, ant_right, post_left, post_right) #create the string for arduino  
        print message

        # send by serial 
        self.ser.write(message) #message via USB

    # receive serial text from arduino and publish it to '/arduino' message
    def get_arduino_message(self):
        pub = rospy.Publisher('arduino', String, queue_size=10) 
        r = rospy.Rate(10)
        while not rospy.is_shutdown():
            message = self.ser.readline()
            pub.publish(message)
            r.sleep()

if __name__ == '__main__':
    try:
        d = driver()
    except rospy.ROSInterruptException: 
        pass
