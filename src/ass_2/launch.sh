# source ./start_legobot.sh
echo "hostname IP is:"
IP=127.0.0.1        #$(eval "hostname -I")
echo $IP

echo "setting ROS_IP to:"
export ROS_IP=$IP
echo $ROS_IP

echo "setting ROS_HOSTNAME to:"
export ROS_HOSTNAME=$IP
echo $ROS_HOSTNAME


echo "setting ROS_MASTER_URI to:"
CORE_URI="http://130.251.13.162:11311"
export ROS_MASTER_URI=$CORE_URI
echo $ROS_MASTER_URI
