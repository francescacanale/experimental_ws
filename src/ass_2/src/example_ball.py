#!/usr/bin/env python

# Python libs
import sys, time
from ass_2.msg import Translation

# numpy and scipy
import numpy as np
from scipy.ndimage import filters

import imutils

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

        # Topic where we publish
        self.image_pub = rospy.Publisher("/output/image_raw/compressed", CompressedImage, queue_size=1)

        # Subscribed Topic
        self.subscriber = rospy.Subscriber("/raspicam_node/image/compressed", CompressedImage, self.callback,  queue_size = 1)
        if VERBOSE :
            print "subscribed to /raspicam_node/image/compressed"

	# Camera calibration parameters
	self.camera_matrix = np.array([[322.0704122808738, 0., 199.2680620421962], [0., 320.8673986158544, 155.2533082600705], [0., 0., 1.]])
	self.dist_coefs = np.array([0.1639958233797625, -0.271840030972792, 0.001055841660100477, -0.00166555973740089, 0.])


    def callback(self, ros_data):
        '''Callback function of subscribed topic. 
        Here images get converted and features detected'''
        if VERBOSE :
            print 'received image of type: "%s"' % ros_data.format

        #### direct conversion to CV2 ####
        np_arr = np.fromstring(ros_data.data, np.uint8)
        image_np = cv2.imdecode(np_arr, cv2.IMREAD_COLOR) # OpenCV >= 3.0:

	# Defining RED range
	greenLower = (255, 0, 0)         #BLUE  100, 150, 50
	greenUpper = (190,255,255)     #      140, 255, 255

	blurred = cv2.GaussianBlur(image_np, (11, 11), 0)
	hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
	mask = cv2.inRange(hsv, greenLower, greenUpper)
	mask = cv2.erode(mask, None, iterations=2)
	mask = cv2.dilate(mask, None, iterations=2)
	#cv2.imshow('mask', mask)
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

			# Object Points coordinates (Mattere misure reali pallina)
			object_point = np.array([[radius , 0., 0.], [0., radius, 0.], [0., -radius, 0.], [0., 0., radius], [0., 0., -radius]])

			# Image Points coordinates
			float_center = np.float32(center)
			float_center2 = ([float_center[0], float_center[1]+radius])			
			float_center3 = ([float_center[0], float_center[1]-radius])
			float_center4 = ([float_center[0]-radius, float_center[1]])
			float_center5 = ([float_center[0]+radius, float_center[1]])
			image_point = np.array([float_center, float_center2, float_center3, float_center4, float_center5])

			# Calling solvePnP, it computes T between the object frame and the camera
			(_, rotation_vector, translation_vector) = cv2.solvePnP(object_point, image_point , self.camera_matrix, self.dist_coefs)
			
			# Printing translation vector
			print '\nTranslation vector: '
			print translation_vector

			# translation = [float(translation_vector[0]), float(translation_vector[1]), float(translation_vector[2])]

			# Publishing the translation vector
			self.translation_pub.publish(float(translation_vector[0]), float(translation_vector[1]), float(translation_vector[2]))
 
	# update the points queue
	#pts.appendleft(center)
        cv2.imshow('window', image_np)
        cv2.waitKey(2)

     
        #self.subscriber.unregister()

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
