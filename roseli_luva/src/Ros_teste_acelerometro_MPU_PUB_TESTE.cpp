//teste leitura acelerômetro MPU-6050
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include "ros/ros.h"
#include <sensor_msgs/Imu.h>
#include "geometry_msgs/Pose2D.h"
#include <wiringPiI2C.h>
#include <stdio.h>
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
int16_t AcX,AcY,AcZ;

void MPU6050_Init(){
	
	wiringPiI2CWriteReg8 (fd, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
	wiringPiI2CWriteReg8 (fd, PWR_MGMT_1, 0x01);	/* Write to power management register */
	wiringPiI2CWriteReg8 (fd, CONFIG, 0);		/* Write to Configuration register */
	wiringPiI2CWriteReg8 (fd, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
	wiringPiI2CWriteReg8 (fd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */

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

int main(int argc, char **argv){ 
	fd = wiringPiI2CSetup(MPU_ADDR);
//	wiringPiI2CWriteReg8 (fd,0x6B,0x00);//disable sleep mode
//	MPU6050_Init(); //Inicializar o acelerometro
//	wiringPiI2CWriteReg16(fd, PWR_MGMT_1,0);

	//Set up the ros node and publisher
	ros::init(argc, argv, "mpu");
	ros::NodeHandle n;	
	geometry_msgs::Pose2D imu_msg;
	sensor_msgs::Imu msg;
        ros::Publisher pub = n.advertise<sensor_msgs::Imu>("imu1", 1);

	ros::Publisher imu = n.advertise<geometry_msgs::Pose2D>("imu", 1);
ros::Rate loop_rate(10);
        
/*
	Wire.begin();
	Wire.beginTransmission(MPU_addr);
	Wire.write(0x6B);  // PWR_MGMT_1 register
	Wire.write(0);     // set to zero (wakes up the MPU-6050)
	Wire.endTransmission(true);
*/
 
//	long publisher_timer;
	 
	while (ros::ok()){
/*		Wire.beginTransmission(MPU_addr);
		Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
		Wire.endTransmission(false);
		Wire.requestFrom(MPU_addr,6,true);  // request a total of 14 registers  String AX = String(mpu6050.getAccX());

			  
		AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C ACCEL_XOUT_L)    
		AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
		AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)*/
        MPU6050_Init(); //Inicializar o acelerometro
        wiringPiI2CWriteReg16(fd, PWR_MGMT_1,0);
		
		AcX = read_word_2c(ACCEL_XOUT_H);
		AcY = read_word_2c(ACCEL_YOUT_H);
//		AcZ = read_word_2c(ACCEL_ZOUT_H);

		imu_msg.x = AcX;
		imu_msg.y = AcY;
//		imu_msg.theta = AcZ;
	  
		/*if (millis() > publisher_timer) {
			// step 1: request reading from sensor
			imu.publish(&imu_msg);
			publisher_timer = millis() + 100; //publish ten times a second
			ros::spinOnce();
		}*/
		//delay(40);
		msg.header.stamp=ros::Time::now();
		msg.header.frame_id='0';
		msg.linear_acceleration.x=read_word_2c(ACCEL_XOUT_H);
                msg.linear_acceleration.y=read_word_2c(ACCEL_YOUT_H);
		pub.publish(msg);
		imu.publish(imu_msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
return 0;
}
