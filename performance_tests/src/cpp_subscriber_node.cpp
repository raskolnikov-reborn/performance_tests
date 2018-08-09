#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"

// Persistent variables
ros::Time measured_time;
int counter;

// Callback : executes on receipt of message and prints the number of messages received over the last 1 second
void superAwesomeCallback(const performance_tests::SuperAwesomeConstPtr& msg){
	double seconds = (ros::Time::now() - measured_time).toSec();
	if(seconds > 1.0)
	{
		measured_time = ros::Time::now();
		ROS_INFO("Receiveing msgs at : %d Hz", counter);
		counter = 0;
		
	}
	else counter++;
	
}

//main
int main(int argc, char** argv){
	
	// setup ros
	ros::init(argc, argv, "cpp_subscriber");
	ros::NodeHandle nh;
	ros::NodeHandle private_nh("~");

	// initialize counter, measured_time and register callback
	counter = 0;
	measured_time = ros::Time::now();
	// keeping a queue size of one to measure all packet loss
	std::string input_topic_param;
  	private_nh.param<std::string> ("input_topic", input_topic_param, "/cpp_publisher/cpp_published");
	ros::Subscriber cpp_sub = nh.subscribe(input_topic_param, 1, superAwesomeCallback);

	
	ros::spin();
}