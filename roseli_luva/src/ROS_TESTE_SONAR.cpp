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


const int vel = 116; //128 = ponto central, velocidade nula
int echo1 = 3, echo2 = 5, echo3 = 7;
int trig1 = 2, trig2 = 4, trig3 = 6; 
int leitura1, leitura2, leitura3;
long startTime;
long travelTime;


int sonar(int trig, int echo){
	digitalWrite(trig, LOW); 
	delayMicroseconds(2); 
        //Send trig pulse
        digitalWrite(trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(trig, LOW);

        //Wait for echo start
        while(digitalRead(echo) == LOW);

        //Wait for echo end
        long startTime = micros();
        while(digitalRead(echo) == HIGH);
        long travelTime = micros() - startTime;

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
	pinMode(trig1, OUTPUT);
	pinMode(echo1, INPUT);
//	pinMode(trig2, OUTPUT);
//	pinMode(echo2, INPUT);
//	pinMode(trig3, OUTPUT);
//	pinMode(echo3, INPUT);

	while (ros::ok()){

//ENVIAR DADOS DOS SONARES

		//SENSOR SONAR 1
		//Get distance in cm
		leitura1 = sonar(trig1,echo1);

		//SENSOR SONAR 2
		//Get distance in cm
		//leitura2 = sonar(trig2,echo2);
		//SENSOR SONAR 3
		//Get distance in cm
	//	leitura3 = sonar(trig3,echo3);
		
		Leitura.x = leitura1;
	//	printf("Leitura1 = %d",leitura1);
		//Leitura.y = leitura2;
		//Leitura.z = leitura3;

/*		if (leitura1 > 35) leitura1 = 1;
		else if (leitura1 >= 25 && leitura1 <= 35) leitura1 = 2;
		else leitura1 = 3;
		if (leitura2 > 35) leitura2 = 4;
		else if (leitura2 >= 25 && leitura2 <= 35) leitura2 = 5;
		else leitura2 = 6;
		if (leitura3 > 35) leitura3 = 7;
		else if (leitura3 >= 25 && leitura3 <= 35) leitura3 = 8;
		else leitura3 = 9;
*/
//		Leitura.x = leitura1;
//		Leitura.y = leitura2;
//		Leitura.z = leitura3;
		sensor.publish(Leitura);
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}
