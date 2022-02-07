#ifndef _GRIP_H
#define _GRIP_H
#include "stdint.h"
double init_pos();
void get();   //获取物体
void putDown(); //放下物体
double down();		//机械臂下降
double up();
double grip();			//夹住物块
double loose();			//松开物块
void rm_servo(double angle);		//云台舵机
void servo1(float angle);
void servo2(float angle);
void servo3(float angle);
void clip(double angle);			//夹子舵机


#endif