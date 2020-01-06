//CODIGO SONAR3
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
int echo3 = 4;
int trig3 = 3; 
int leitura3;
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
	ros::init(argc, argv, "sonar3");	//NOME DO NÓ
	ros::NodeHandle  n;
	std_msgs::Float64 Leitura3;
	ros::Publisher sonar3 = n.advertise<std_msgs::Float64> ("sensor3", 1);
	ros::Rate loop_rate(10);

	pinMode(trig3, OUTPUT);
	pinMode(echo3, INPUT);

	while (ros::ok()){

//ENVIAR DADOS DOS SONARES
		//SENSOR SONAR 1
		//Get distance in cm
		leitura3 = sonar(trig3,echo3);

				
		Leitura3.data = leitura3;

		sonar3.publish(Leitura3);
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}
