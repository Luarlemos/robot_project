//TESTE MOTORES VIBRAÇÃO
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <softPwm.h>
#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include "sensor_msgs/Range.h"
#include "geometry_msgs/Vector3.h"
#include <math.h>
#include <sstream>
#define PWM 80

int motor1pin = 4;
int motor2pin = 5;
int motor3pin = 6;


void Callback(const std_msgs::Bool& msg){
	if(msg.data==false){
                softPwmWrite(motor1pin, 0);
                softPwmWrite(motor2pin, 0);
                softPwmWrite(motor3pin, 0);

	}  
	if(msg.data==true){

	//ACIONAMENTO DOS MOTORES DE VIBRAÇÃO
		softPwmWrite(motor1pin, PWM);
//		delay(1000);
//                softPwmWrite(motor1pin, 0);
//                delay(1000);
		softPwmWrite(motor2pin, PWM);
//		delay(1000);
 //               softPwmWrite(motor2pin, 0);
   //             delay(1000);
		softPwmWrite(motor3pin, PWM);
//		delay(1000);
  //              softPwmWrite(motor3pin, 0);
    //            delay(1000);
	}
}

int main(int argc, char **argv){ 
wiringPiSetup();
/*	pinMode(enable1, OUTPUT);
        pinMode(enable2, OUTPUT);
        pinMode(motor1pin, OUTPUT);
        pinMode(motor2pin, OUTPUT);
        pinMode(motor3pin, OUTPUT);

        softPwmCreate(motor1pin,0,255);
        softPwmCreate(motor2pin,0,255);
        softPwmCreate(motor3pin,0,255);
*/
	
	//Set up the ros node and publisher
	ros::init(argc, argv, "vibracall");
	ros::NodeHandle n;	
//	geometry_msgs::Pose2D imu_msg;
//	ros::Publisher imu = n.advertise<geometry_msgs::Pose2D>("imu", 1000);
	ros::Subscriber motor = n.subscribe("motor",1, Callback);
//	ros::Rate loop_rate(10);

	//SETUP MOTORES VIBRACAO
	pinMode(motor1pin, OUTPUT);
	pinMode(motor2pin, OUTPUT);
	pinMode(motor3pin, OUTPUT);

	softPwmCreate(motor1pin,0,100);
	softPwmCreate(motor2pin,0,100);
	softPwmCreate(motor3pin,0,100);


ros::spin();

return 0;
}
