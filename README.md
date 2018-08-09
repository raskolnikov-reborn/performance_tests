# performance_tests
simple performance testing ros package for cpp and python publishing, subscription and benchmarking at various publish rates using dynamic reconfigure


## dependencies
### ros
  roscpp
  rospy
  std_msgs
  message_generation
  dynamic_reconfigure
  
 ### Others
 boost
 
 ## build
 copy the package into a catkin workspace and build using catkin_make or catkin build
 Tested on ros-melodic with osx and ubuntu 18.04
 
 ## launch 
 There are 4 launch files in the package titled cpp_to_cpp.launch, cpp_to_python.launch, python_to_python.launch, python_to_cpp.launch
 The names are self explanatory
 launch them with the --screen option and the publisher and subscriber are setup 
 
 ## Benchmark
 open up rqt_reconfigure after launching the required launch files and then increase the publisher rate for cpp or python
 The console print on the terminal running the launch should show how many messages per second are being processed.
 
 #### Findings 
 Performance of cpp and python subscribers is comparable on my machine upto a baseline of about 10000 messages, regardless of publishers as well as queue size.
 On Increasing publish rate beyond 10000 the queue size performance becomes more sensitive to queue size as well as cpp and python both start dropping packets. cpp_subscriber drops less packets when built with gcc on ubuntu. Performance is too close to tell when cpp_subscriber is built using clang on osx.
 
