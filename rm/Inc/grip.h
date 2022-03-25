#ifndef _GRIP_H
#define _GRIP_H
#include "stdint.h"

void rm_servo(double angle, float target_speed);		//��̨�����
void servo1(float angle);
void servo2(float angle);
void servo3(float angle);
void clip(double angle);			//���Ӷ��

//��е�۵Ĳ�ͬ��̬
void init_pos();
void move_get();
void move_put();
void move_get2();
void up();
typedef struct
{
  float pointX;		//y, z�������е������ƽ��
	float pointY;		//x, y�������̨����ƽ��
	float pointZ;
	
	//float handBiasAngle;				//��3��x��ĸ�����
	//uint8_t mode;	//	1 normal
	//float panAngle;
} MecArmAttiSturcture;
uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *pTheta);
uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta);
#endif