#!/usr/bin/env python
# Setup ROS
import rospy

#setup modules
from dynamic_reconfigure.server import Server
from performance_tests.cfg import PublishRatesConfig
from performance_tests.msg import SuperAwesome 

# global variable
global loop_rate

# callback method for reconfigure request
def callback(config, level):
	global loop_rate
	rospy.loginfo("""Now Publishing at: {python_publish_rate} Hz
          """.format(**config))
	#update global loop_rate variable
	loop_rate = rospy.Rate(config.python_publish_rate)
	return config

#main method
if __name__ == "__main__":
	#initialize the node
    rospy.init_node("python_publisher_node", anonymous = True)
    # initialize loop_rate to a default value
    global loop_rate
    loop_rate = rospy.Rate(100)

    output_topic_param = rospy.get_param('output_topic', '/python_publisher_node/python_published')

    #setup publisher
    pub = rospy.Publisher(output_topic_param, SuperAwesome, queue_size=100)
    #setup dynamic_reconfigure callback
    srv = Server(PublishRatesConfig, callback)

    # ros loop -> make message -> publish message -> sleep -> repeat 
    while not rospy.is_shutdown():
        output_msg = SuperAwesome()
        output_msg.string.data = "awesomely awesome"
        pub.publish(output_msg)
        loop_rate.sleep()


    
