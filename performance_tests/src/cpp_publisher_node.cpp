#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include <dynamic_reconfigure/server.h>
#include "performance_tests/PublishRatesConfig.h"


ros::Rate* loop_rate;

// dynamic reconfigure callback
// change
void callback(performance_tests::PublishRatesConfig &config, uint32_t level) {
  
  ROS_INFO("Now publishing at: %d Hz", 
            config.cpp_publish_rate);

  loop_rate = new ros::Rate(config.cpp_publish_rate);
}

int main(int argc, char** argv){
	// setup ros
	ros::init(argc, argv, "cpp_publisher");
	ros::NodeHandle nh;
	ros::NodeHandle private_nh("~");
	loop_rate = new ros::Rate(100);

	// setup dynamic reconfigure
	dynamic_reconfigure::Server<performance_tests::PublishRatesConfig> server;
  	dynamic_reconfigure::Server<performance_tests::PublishRatesConfig>::CallbackType f;
  	f = boost::bind(&callback, _1, _2);
  	server.setCallback(f);

  	std::string output_topic_param;
  	private_nh.param<std::string> ("output_topic", output_topic_param, "cpp_published");
	// use a big queue size so that bottleneck from publisher does not become an issue
	ros::Publisher cpp_pub = private_nh.advertise<performance_tests::SuperAwesome>
		(output_topic_param,100);
	//ros loop
	while(ros::ok())
	{
		performance_tests::SuperAwesome awesome_msg;
		awesome_msg.string.data = "awesomely awesome";
		cpp_pub.publish(awesome_msg);
		
		loop_rate->sleep();
		ros::spinOnce();
	}
}