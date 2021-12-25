#ifndef _MOVE_H
#define _MOVE_H
#include "stdint.h"

void change_pwm(int ch,int dir,int vel);
void dir_init();
void go_pwm();
void straight();
void pause();
void left();
void right();
void avoid();
//void advoid();

#endif