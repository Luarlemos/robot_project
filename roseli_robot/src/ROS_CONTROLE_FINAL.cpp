//CONTROLE FINAL ROBÔ
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/Float64.h"
#include <sstream>

//DECLARAÇÃO DE VARIÁVEIS
int16_t AcX,AcY;
//int echo1 = 5, echo2 = 6, echo3 = 4;
//int trig1 = 1, trig2 = 2, trig3 = 3; 
int leitura1, leitura2, leitura3;
long startTime;
long travelTime;
unsigned long previousMillis=0;
const long tempo=1000;

//PROTÓTIPOS
void frente(int16_t AcY);
void parar(int16_t AcX,int16_t AcY);
void direita(int16_t AcX);
void esquerda(int16_t AcX);
void tras(int16_t AcY);
void frentedireita(int16_t AcX,int16_t AcY);
void frenteesquerda(int16_t AcX,int16_t AcY);
void trasdireita(int16_t AcX,int16_t AcY);
void trasesquerda(int16_t AcX,int16_t AcY);

//ros::Publisher pub;
geometry_msgs::Twist msg;
//ros::Publisher sensor;
//geometry_msgs::Vector3 Leitura;
/*int sonar(int trig, int echo){
//        wiringPiSetup();
  
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
        while(digitalRead(echo) == LOW){
//printf("OIIII\n");
        //Wait for echo end
        startTime = micros();}
        while(digitalRead(echo) == HIGH);
        travelTime = micros() - startTime;

        //Get distance in cm
        int distancia = travelTime / 58.2;
        return distancia;
}
*/

void Callback(const geometry_msgs::Pose2D& imu_msg){
	AcX = imu_msg.x;
	AcY = imu_msg.y;
/*
	//MOVIMENTAÇAO DO ROBÔ
	frente(AcY);
	parar(AcX,AcY);
	direita(AcX);
	esquerda(AcX);
	tras(AcY);
	frentedireita(AcX,AcY);
	frenteesquerda(AcX,AcY);
	trasdireita(AcX,AcY);
	trasesquerda(AcX,AcY);
	
	pub.publish(msg);
*/
}
void Callback1(const std_msgs::Float64::ConstPtr& Leitura1){
	leitura1 = Leitura1->data;
//	sensor.publish(Leitura);
}
void Callback2(const std_msgs::Float64::ConstPtr& Leitura2){
        leitura2 = Leitura2->data;
  //      sensor.publish(Leitura);
}
void Callback3(const std_msgs::Float64::ConstPtr& Leitura3){
        leitura3 = Leitura3->data;
//        sensor.publish(Leitura);
}


int main(int argc, char **argv){
	wiringPiSetup();
//	unsigned long currentMillis= micros();

	ros::init(argc, argv, "controle");
	ros::NodeHandle n;
	geometry_msgs::Vector3 Leitura;
	ros::Publisher pub;
//	geometry_msgs::Twist msg;
	ros::Publisher sensor = n.advertise<geometry_msgs::Vector3> ("sensor", 1);
	pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
	sensor = n.advertise<geometry_msgs::Vector3>("sensor", 1);

	ros::Subscriber imu = n.subscribe("imu",1,Callback);
        ros::Subscriber sensor1 = n.subscribe("sensor1",1,Callback1);
        ros::Subscriber sensor2 = n.subscribe("sensor2",1,Callback2);
        ros::Subscriber sensor3 = n.subscribe("sensor3",1,Callback3);


	ros::Rate loop_rate(100);

	while(ros::ok()){
	Leitura.x=leitura1;
	Leitura.y=leitura2;
	Leitura.z = leitura3;

/*
previousMillis=0;
//	travelTime=0;
//	startTime=0;
	//ENVIAR DADOS DOS SONARES
//		previousMillis=0;
		//SENSOR SONAR 1
		//Get distance in cm
		leitura1 = sonar(trig1,echo1);
		printf("help1\n");
		if(currentMillis-previousMillis>=tempo){
			previousMillis = currentMillis;
		}

		//SENSOR SONAR 2
		//Get distance in cm
		leitura2 = sonar(trig2,echo2);
		printf("help2\n");
                if(currentMillis-previousMillis>=tempo){ 
	                previousMillis = currentMillis;
                }

		//SENSOR SONAR 3
		//Get distance in cm
//		leitura3=sonar(trig3,echo3);
		//printf("help3\n");
                if(currentMillis-previousMillis>=tempo){ 
                        previousMillis = currentMillis;
              }

		Leitura.x = leitura1;
		Leitura.y = leitura2;
		Leitura.z = leitura3;
*/                
        //MOVIMENTAÇAO DO ROBÔ
        frente(AcY);
        parar(AcX,AcY);
        direita(AcX);
        esquerda(AcX);
        tras(AcY);
        frentedireita(AcX,AcY);
        frenteesquerda(AcX,AcY);
        trasdireita(AcX,AcY);
        trasesquerda(AcX,AcY);

        pub.publish(msg);

		sensor.publish(Leitura);

		ros::spinOnce();
		loop_rate.sleep();		
	}
return 0;
}

//MOVIMENTOS DO ROBÔ
void frente(int16_t AcY) {
	if(AcY>=-3000 && AcY<3000){
		msg.linear.x = 0.0;
	}
	if(AcY>=3000 && AcY<6000){
		msg.linear.x = 1.0;
	}
	if(AcY>=6000 && AcY<9000){
		msg.linear.x = 1.4;
	}
	if(AcY>=9000 && AcY<12000){
		msg.linear.x = 1.8;
	}
	if(AcY>=12000 && AcY<15000){
		msg.linear.x = 2.2;
	}
	if(AcY>=15000){
		msg.linear.x = 2.6;
	}
}
void parar(int16_t AcX,int16_t AcY) {
	if(AcY>=-3000 && AcY<3000 && AcX>=-3000 && AcX<3000){
		msg.linear.x = 0.0;
		msg.angular.z = 0.0;
	}	
}
void direita(int16_t AcX) {
	if(AcX>=-3000 && AcX<3000){
		msg.angular.z = 0.0;
	}
	if(AcX>=3000 && AcX<6000){
		msg.angular.z = 0.7;
	}
	if(AcX>=6000 && AcX<9000){
		msg.angular.z = 1.0;
	}
	if(AcX>=9000 && AcX<12000){
		msg.angular.z = 1.3;
	}
	if(AcX>=12000 && AcX<15000){
		msg.angular.z = 1.6;
	}
	if(AcX>=15000){
		msg.angular.z = 2.0;
	}
}
void esquerda(int16_t AcX) {
	if(AcX>=-3000 && AcX<3000){
		msg.angular.z = 0.0;
	}
	if(AcX>=-6000 && AcX<-3000){
		msg.angular.z = -0.7;
	}
	if(AcX>=-9000 && AcX<-6000){
		msg.angular.z = -1.0;
	}
	if(AcX>=-12000 && AcX<-9000){
		msg.angular.z = -1.3;
	}
	if(AcX>=-15000 && AcX<-12000){
		msg.angular.z = -1.6;
	}
	if(AcX<=-15000){
		msg.angular.z = -2.0;
	}
}
void tras(int16_t AcY) {
	if(AcY>=-3000 && AcY<3000){
		msg.linear.x = 0.0;
	}	
	if(AcY>=-6000 && AcY<-3000){
		msg.linear.x = -1.0;
	}
	if(AcY>=-9000 && AcY<-6000){
		msg.linear.x = -1.4;
	}
	if(AcY>=-12000 && AcY<-9000){
		msg.linear.x = -1.8;
	}
	if(AcY>=-15000 && AcY<-12000){
		msg.linear.x = -2.2;
	}
	if(AcY<=-15000){
		msg.linear.x = -2.6;
	}
}
void frentedireita(int16_t AcX,int16_t AcY) {
	frente(AcY);
	direita(AcX);
}
void frenteesquerda(int16_t AcX,int16_t AcY) {
	frente(AcY);
	esquerda(AcX);
}
void trasdireita(int16_t AcX,int16_t AcY) {
	tras(AcY);
	direita(AcX);
}
void trasesquerda(int16_t AcX,int16_t AcY) {
	tras(AcY);
	esquerda(AcX);
}

