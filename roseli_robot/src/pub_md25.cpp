
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
//#include "boost/thread.hpp"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Empty.h"
//#include <ecl/threads.hpp>
//#include <roseli/ResetEnc.h>
//#include <roseli/GetOdom.h>
#include <iostream>

int main(int argc, char **argv){

ros::init(argc, argv, "motorcontrole");
ros::NodeHandle n;
ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
ros::Rate loop_rate(10);

while (ros::ok()){
geometry_msgs::Twist msg;

msg.linear.x = 2.0;




pub.publish(msg);

ros::spinOnce();

loop_rate.sleep();

}
return 0;
}
