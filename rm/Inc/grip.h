#ifndef _GRIP_H
#define _GRIP_H
#include "stdint.h"
double init_pos();
void get();   //��ȡ����
void putDown(); //��������
double down();		//��е���½�
double up();
double grip();			//��ס���
double loose();			//�ɿ����
void rm_servo(double angle);		//��̨���
void servo1(float angle);
void servo2(float angle);
void servo3(float angle);
void clip(double angle);			//���Ӷ��


#endif