//CODIGO SONAR1
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

//DECLARAÇÃO DE VARIÁVEIS
int echo1 = 5;
int trig1 = 1; 
int leitura1;
long startTime;
long travelTime;

//FUNÇÃO AUXILIAR SENSOR
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

//FUNÇÃO PRINCIPAL
int main(int argc, char **argv){
	wiringPiSetup();	//INICIALIZA A BIBLIOTECA WIRING PI
//Inicialização do ROS
	ros::init(argc, argv, "sonar1");	//NOME DO NÓ
	ros::NodeHandle  n;
	std_msgs::Float64 Leitura1;
	ros::Publisher sonar1 = n.advertise<std_msgs::Float64> ("sensor1", 1);
	ros::Rate loop_rate(10);

	pinMode(trig1, OUTPUT);
	pinMode(echo1, INPUT);

	while (ros::ok()){

//ENVIAR DADOS DOS SONARES
		//SENSOR SONAR 1
		//Get distance in cm
		leitura1 = sonar(trig1,echo1);

				
		Leitura1.data = leitura1;

		sonar1.publish(Leitura1);
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}
