#include "grip.h"
#include "tim.h"
#include "caculate.h"
#include "motor_pid.h"
void rm_servo(double angle, float target_speed)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//GM6020占空比为5%到10%，最小值为3599*5%=179.95 最大值为3599*10%=359.9
		//对应角度 ccr = 0.5*angle + 179
		double arr ;
		arr = (179.0/360)*angle + 180;
		TIM8->CCR1 = arr;
		rotor_pid_task(target_speed);
		HAL_Delay(100);

}
void servo1(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR1 = arr;
		HAL_Delay(100);

}
void servo2(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR2 = arr;
		HAL_Delay(100);

}
void servo3(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR3 = arr;
		HAL_Delay(100);

}
void clip(double angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR4 = arr;
		HAL_Delay(100);

}

//机械臂的不同姿态
void init_pos()
{
//	attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
//	servo1(servoAngle[0]);
//	servo2(servoAngle[1]);
//	servo3(servoAngle[2]);
//	rm_servo(servoAngle[3], target_speed);
}
void move_get()
{
//	attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
//	servo1(servoAngle[0]);
//	servo2(servoAngle[1]);
//	servo3(servoAngle[2]);
//	rm_servo(servoAngle[3], target_speed);
}
void move_put()
{
//	attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta);
//	servo1(servoAngle[0]);
//	servo2(servoAngle[1]);
//	servo3(servoAngle[2]);
//	rm_servo(servoAngle[3], target_speed);
}
