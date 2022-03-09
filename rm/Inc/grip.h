#ifndef _GRIP_H
#define _GRIP_H
#include "stdint.h"

void rm_servo(double angle, float target_speed);		//云台舵机角
void servo1(float angle);
void servo2(float angle);
void servo3(float angle);
void clip(double angle);			//夹子舵机

void init_pos();
void move_get();
void move_put();
#endif