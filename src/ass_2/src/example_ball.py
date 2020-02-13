#!/usr/bin/env python

# Python libs
import sys, time
from ass_2.msg import Translation

# numpy and scipy
import numpy as np
from scipy.ndimage import filters

import imutils
import statistics

# OpenCV
import cv2

# Ros libraries
import roslib
import rospy

# Ros Messages
from sensor_msgs.msg import CompressedImage

VERBOSE=False

class image_feature:

    def __init__(self):
        '''Initialize ros publisher, ros subscriber'''

	# Topic where we publish the translation vector
	self.translation_pub = rospy.Publisher("translation", Translation, queue_size=10) 

        # Subscribed Topic
        self.subscriber = rospy.Subscriber("/raspicam_node/image/compressed", CompressedImage, self.callback,  queue_size = 1)
        if VERBOSE :
            print "subscribed to /raspicam_node/image/compressed"

	# Camera calibration parameters
	self.camera_matrix = np.array([[322.0704122808738, 0., 199.2680620421962], [0., 320.8673986158544, 155.2533082600705], [0., 0., 1.]])
	self.dist_coefs = np.array([0.1639958233797625, -0.271840030972792, 0.001055841660100477, -0.00166555973740089, 0.])

	# Transformation matrix between camera and ball
	self.T_matrix = [[0., 0., 0., 0.], [0., 0., 0., 0.], [0., 0., 0., 0.]] # Init

	# Object Points coordinates
	radius_ball = 3.5 # Real radius of the ball
	self.object_point = np.array([[0., 0., -radius_ball], [radius_ball, 0., 0.], [-radius_ball, 0., 0.], [0., -radius_ball, 0.], [0., radius_ball, 0.]])

    def callback(self, ros_data):
        '''Callback function of subscribed topic. 
        Here images get converted and features detected'''
        if VERBOSE :
            print 'received image of type: "%s"' % ros_data.format

        #### direct conversion to CV2 ####
        np_arr = np.fromstring(ros_data.data, np.uint8)
        image_np = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

	# Defining RED range
	redLower = (160, 100, 100)
	redUpper = (179, 255, 255)

	blurred = cv2.GaussianBlur(image_np, (11, 11), 0)
	hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
	mask = cv2.inRange(hsv, redLower, redUpper)
	mask = cv2.erode(mask, None, iterations=2)
	mask = cv2.dilate(mask, None, iterations=2)
	cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)
	cnts = imutils.grab_contours(cnts)
	center = None

	# Only proceed if at least one contour was found
	if len(cnts) > 0:
		# find the largest contour in the mask, then use
		# it to compute the minimum enclosing circle and
		# centroid
		c = max(cnts, key=cv2.contourArea)
		((x, y), radius) = cv2.minEnclosingCircle(c)
		M = cv2.moments(c)
		center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"])) # centroid coordinates		
 
		# Only proceed if the radius meets a minimum size
		if radius > 10:
			# draw the circle and centroid on the frame,
			# then update the list of tracked points
			cv2.circle(image_np, (int(x), int(y)), int(radius),
				(0, 255, 255), 2)
			cv2.circle(image_np, center, 5, (0, 0, 255), -1)

			# Image Points coordinates
			float_center = np.float32(center)
			float_center2 = ([float_center[0]+radius, float_center[1]])			
			float_center3 = ([float_center[0]-radius, float_center[1]])
			float_center4 = ([float_center[0], float_center[1]-radius])
			float_center5 = ([float_center[0], float_center[1]+radius])
			image_point = np.array([float_center, float_center2, float_center3, float_center4, float_center5])
			#print float_center
			#print float_center2
			#print float_center3
			#print float_center4
			#print float_center5

			# Calling solvePnP, it computes T-matrix between the object frame and the camera
			(_, rotation_vector, translation_vector) = cv2.solvePnP(self.object_point, image_point , self.camera_matrix, self.dist_coefs)
			
			(rotation_matrix, _) = cv2.Rodrigues(rotation_vector)
			self.T_matrix = np.concatenate((np.identity(3), translation_vector), axis=1)

			multiplication = np.dot(self.camera_matrix, self.T_matrix)

			object_in_image = np.array([[center[0]], [center[1]], [1]])
			object_position = np.dot(np.linalg.pinv(multiplication), object_in_image)
			object_position = object_position / object_position[3]

			# Printing translation vector
			print 'Object position: '
			print abs(object_position)

			# Publishing the translation vector
			self.translation_pub.publish(float(translation_vector[0]), float(translation_vector[1]), float(translation_vector[2]))
 
	# update the points queue
        cv2.imshow('window', image_np)
        cv2.waitKey(2)


def main(args):
    '''Initializes and cleanup ros node'''
    ic = image_feature()
    rospy.init_node('image_feature', anonymous=True)
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print "Shutting down ROS Image feature detector module"
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
