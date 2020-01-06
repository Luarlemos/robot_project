//CODIGO TESTE SONAR
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include "sensor_msgs/Range.h"
#include "geometry_msgs/Vector3.h"
#include <sstream>


//const int vel = 116; //128 = ponto central, velocidade nula
int echo1 = 5,echo2 = 6, echo3 = 4;
int trig1 = 1,trig2 = 2, trig3 = 3; 
int leitura1, leitura2, leitura3;
long startTime;
long travelTime;


int sonar(int trig, int echo){
//	wiringPiSetup();
	pinMode(trig, OUTPUT);
      	pinMode(echo, INPUT);

	long startTime;
	long travelTime; 
	digitalWrite(trig, LOW); 
	delayMicroseconds(2); 
        //Send trig pulse
        digitalWrite(trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(trig, LOW);

        //Wait for echo start
        while(digitalRead(echo) == LOW);

        //Wait for echo end
        startTime = micros();
        while(digitalRead(echo) == HIGH);
        travelTime = micros() - startTime;

        //Get distance in cm
       	int distancia = travelTime / 58.2;

        return distancia;
}


int main(int argc, char **argv){
	wiringPiSetup();
//Inicialização do ROS
	ros::init(argc, argv, "sonar");
	ros::NodeHandle  n;
	geometry_msgs::Vector3 Leitura;
	ros::Publisher sensor = n.advertise<geometry_msgs::Vector3> ("sensor", 1);

	ros::Rate loop_rate(10);

	//ros::Subscriber imu = n.subscribe("imu",1000,Callback);

//	pinMode(13, OUTPUT);
	//Wire.begin();
//	pinMode(trig1, OUTPUT);
//	pinMode(echo1, INPUT);
//	pinMode(trig2, OUTPUT);
//	pinMode(echo2, INPUT);
//	pinMode(trig3, OUTPUT);
//	pinMode(echo3, INPUT);

	while (ros::ok()){
		
//ENVIAR DADOS DOS SONARES

		//SENSOR SONAR 1
		//Get distance in cm
		leitura1 = sonar(trig1,echo1);
		delay(200);
		//SENSOR SONAR 2
		//Get distance in cm
		leitura2 = sonar(trig2,echo2);
		delay(200);
		//SENSOR SONAR 3
		//Get distance in cm
		leitura3 = sonar(trig3,echo3);
		delay(200);
		Leitura.x = leitura1;
		Leitura.y = leitura2;
		Leitura.z = leitura3;

		sensor.publish(Leitura);
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}
