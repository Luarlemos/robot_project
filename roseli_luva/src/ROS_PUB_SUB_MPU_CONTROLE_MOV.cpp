#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"
#include <iostream>

//DECLARAÇÃO DE VARIÁVEIS
int16_t AcX,AcY;

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

ros::Publisher pub;
geometry_msgs::Twist msg;

void Callback(const geometry_msgs::Pose2D& imu_msg){
	AcX = imu_msg.x;
	AcY = imu_msg.y;

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
}
int main(int argc, char **argv){
	ros::init(argc, argv, "controle");
	ros::NodeHandle n;
	pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
	ros::Subscriber imu = n.subscribe("imu",1000,Callback);
	ros::Rate loop_rate(10);
//	geometry_msgs::Twist msg;

	while(ros::ok()){
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
		msg.angular.z = 1.0;
	}
	if(AcX>=6000 && AcX<9000){
		msg.angular.z = 1.4;
	}
	if(AcX>=9000 && AcX<12000){
		msg.angular.z = 1.8;
	}
	if(AcX>=12000 && AcX<15000){
		msg.angular.z = 2.2;
	}
	if(AcX>=15000){
		msg.angular.z = 2.6;
	}
}
void esquerda(int16_t AcX) {
	if(AcX>=-3000 && AcX<3000){
		msg.angular.z = 0.0;
	}
	if(AcX>=-6000 && AcX<-3000){
		msg.angular.z = -1.0;
	}
	if(AcX>=-9000 && AcX<-6000){
		msg.angular.z = -1.4;
	}
	if(AcX>=-12000 && AcX<-9000){
		msg.angular.z = -1.8;
	}
	if(AcX>=-15000 && AcX<-12000){
		msg.angular.z = -2.2;
	}
	if(AcX<=-15000){
		msg.angular.z = -2.6;
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

