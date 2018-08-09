#!/usr/bin/env python
# Setup ROS
import rospy

#setup modules
from performance_tests.msg import SuperAwesome 

global msg_counter
global timer_start
# callback method for reconfigure request
def callback(data):
    global timer_start
    global msg_counter
    if (rospy.get_time() - timer_start) > 1.0:
        rospy.loginfo("Receiveing msgs at : %d Hz", msg_counter)
        msg_counter = 0;
        timer_start = rospy.get_time()
    else:
        msg_counter += 1

    return
	

#main method
if __name__ == "__main__":
	#initialize the node
    global timer_start
    global msg_counter

    #initialize variables and ros
    msg_counter = 0
    rospy.init_node("python_subscriber_node", anonymous = True)
    timer_start = rospy.get_time()

    # get parameter to publish
    input_topic_param = rospy.get_param('~input_topic', 'python_publisher_node/python_published')
    rospy.Subscriber(input_topic_param, SuperAwesome, callback, queue_size=1)


    rospy.spin()


    
