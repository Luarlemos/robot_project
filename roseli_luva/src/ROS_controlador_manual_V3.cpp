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

#define MPU_ADDR     0x68 //I2c address of the MPU-6050
#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47

int fd;
int16_t AcX,AcY,x,y,z;
int motor1pin = 4;
int motor2pin = 5;
int motor3pin = 6;
int PWM = 20;
//wiringPiSetup();
const long previousMillis=0;

void MPU6050_Init(){
	
	/* Write to sample rate register */
	wiringPiI2CWriteReg8 (fd, SMPLRT_DIV, 0x07);	
	/* Write to power management register */
	wiringPiI2CWriteReg8 (fd, PWR_MGMT_1, 0x01);	
	/* Write to Configuration register */
	wiringPiI2CWriteReg8 (fd, CONFIG, 0);		
	/* Write to Gyro Configuration register */
	wiringPiI2CWriteReg8 (fd, GYRO_CONFIG, 24);	
	/*Write to interrupt enable register */
	wiringPiI2CWriteReg8 (fd, INT_ENABLE, 0x01);	

	}
 
int read_word_2c(int addr){
	short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd, addr);
	low_byte = wiringPiI2CReadReg8(fd, addr+1);
	value = (high_byte << 8) | low_byte;
	return value;
}

void ms_delay(int val){
	int i,j;
	for(i=0;i<=val;i++)
		for(j=0;j<1200;j++);
}

void motor1(int16_t aux){
//        pinMode(motor1pin, OUTPUT);

        softPwmCreate(motor1pin,0,100);

        softPwmWrite(motor1pin, 0);

	if(aux>=2 && aux<=10){
		softPwmWrite(motor1pin, PWM+45);
	}
	if(aux>10 && aux<=15){
		softPwmWrite(motor1pin, PWM+30);
	}
	if(aux>15 && aux<=20){
		softPwmWrite(motor1pin, PWM+15);
	}
	if(aux>20 && aux<=25){
		softPwmWrite(motor1pin, PWM);
	}
	if(aux>25){
		softPwmWrite(motor1pin, 0);
	}
}
void motor2(int16_t aux2){
  //      pinMode(motor2pin, OUTPUT);

        softPwmCreate(motor2pin,0,100);

        softPwmWrite(motor2pin, 0);

	if(aux2>=2 && aux2<=10){
		softPwmWrite(motor2pin, PWM+45);
	}
	if(aux2>10 && aux2<=15){
		softPwmWrite(motor2pin, PWM+30);
	}
	if(aux2>15 && aux2<=20){
		softPwmWrite(motor2pin, PWM+15);
	}
	if(aux2>20 && aux2<=25){
		softPwmWrite(motor2pin, PWM);
	}
	if(aux2>25){
		softPwmWrite(motor2pin, 0);
	}
}
void motor3(int16_t aux3){
 //       pinMode(motor3pin, OUTPUT);

        softPwmCreate(motor3pin,0,100);

        softPwmWrite(motor3pin, 0);

	if(aux3>=2 && aux3<=10){
		softPwmWrite(motor3pin, PWM+45);
	}
	if(aux3>10 && aux3<=15){
		softPwmWrite(motor3pin, PWM+30);
	}
	if(aux3>15 && aux3<=20){
		softPwmWrite(motor3pin, PWM+15);
	}
	if(aux3>20 && aux3<=25){
		softPwmWrite(motor3pin, PWM);
	}
	if(aux3>25){
		softPwmWrite(motor3pin, 0);
	}
}

void Callback(const geometry_msgs::Vector3& Leitura){
	//RECEBER DADOS DOS SENSORES
	x=Leitura.x;
	y=Leitura.y;
	z=Leitura.z;

        pinMode(motor1pin, OUTPUT);
        pinMode(motor2pin, OUTPUT);
        pinMode(motor3pin, OUTPUT);
/*
        softPwmCreate(motor1pin,0,255);
        softPwmCreate(motor2pin,0,255);
        softPwmCreate(motor3pin,0,255);

        softPwmWrite(motor1pin, 0);
        softPwmWrite(motor2pin, 0);
        softPwmWrite(motor3pin, 0);
*/
	//ACIONAMENTO DOS MOTORES DE VIBRAÇÃO
	motor1(x);
	motor2(y);
	motor3(z);
}
int main(int argc, char **argv){ 
	wiringPiSetup();
//	fd = wiringPiI2CSetup(MPU_ADDR);

//	MPU6050_Init(); //Inicializar o acelerometro

	//Set up the ros node and publisher
	ros::init(argc, argv, "luva");
	ros::NodeHandle n;	
	geometry_msgs::Pose2D imu_msg;
	ros::Publisher imu = n.advertise<geometry_msgs::Pose2D>("imu", 1);
	ros::Subscriber sensor = n.subscribe("sensor",1, Callback);
	ros::Rate loop_rate(10);
/*
	//SETUP MOTORES VIBRACAO
	pinMode(motor1pin, OUTPUT);
	pinMode(motor2pin, OUTPUT);
	pinMode(motor3pin, OUTPUT);

	softPwmCreate(motor1pin,0,255);
	softPwmCreate(motor2pin,0,255);
	softPwmCreate(motor3pin,0,255);
*/	 
	while (ros::ok()){
	        fd = wiringPiI2CSetup(MPU_ADDR);

	        MPU6050_Init(); //Inicializar o acelerometro

		AcX = read_word_2c(ACCEL_XOUT_H);
		AcY = read_word_2c(ACCEL_YOUT_H);
		
		if((AcX==0.0 && AcY==0.0) || (AcX==-1.0 && AcY==-1.0)){
	                MPU6050_Init(); //Inicializar o acelerometro
		}
		imu_msg.x = AcX;
		imu_msg.y = AcY;

		imu.publish(imu_msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}

