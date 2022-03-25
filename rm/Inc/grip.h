#ifndef _GRIP_H
#define _GRIP_H
#include "stdint.h"

void rm_servo(double angle, float target_speed);		//云台舵机角
void servo1(float angle);
void servo2(float angle);
void servo3(float angle);
void clip(double angle);			//夹子舵机

//机械臂的不同姿态
void init_pos();
void move_get();
void move_put();
void move_get2();
void up();
typedef struct
{
  float pointX;		//y, z面决定机械臂所在平面
	float pointY;		//x, y面决定云台所在平面
	float pointZ;
	
	//float handBiasAngle;				//杆3对x轴的俯仰角
	//uint8_t mode;	//	1 normal
	//float panAngle;
} MecArmAttiSturcture;
uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *pTheta);
uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta);
#endif