#include "grip.h"
#include "tim.h"
#include "motor_pid.h"
#include "math.h"
#include "FreeRTOS.h"
#include "queue.h"
#define pi 3.1415
extern float servoAngle[4];
extern float servoRefAngle[4];
extern QueueHandle_t	myQueue01Handle;
MecArmAttiSturcture  tx;	
void rm_servo(double angle, float target_speed)
{
		//大疆板子对应APB1外设，时钟频率对应168Mhz
		//GM6020占空比为5%到10%，最小值为4199*5%=210 最大值为4199*10%=419
		//对应角度 ccr = 0.3*angle + 365	
	
			
		double arr ;
		if(servoRefAngle[0] < angle)
		{
			for(; servoRefAngle[0] < angle; servoRefAngle[0]++)
			{
				arr = 0.3*servoRefAngle[0] + 365;
				TIM8->CCR1 = arr;
		//rotor_pid_task(target_speed);
				HAL_Delay(50);
			}
		}
		if(servoRefAngle[0] >= angle)
		{
			for(; servoRefAngle[0] >= angle; servoRefAngle[0]--)
			{
				arr = 0.3*servoRefAngle[0] + 365;
				TIM8->CCR1 = arr;
		//rotor_pid_task(target_speed);
				HAL_Delay(50);
			}
		}
		

}
void servo1(float angle)
{
		//大疆板子对应APB1TIME1,时钟频率为84Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为4199*2.5%=105 最大值为4199*12.5%=524
		
		float arr ;
		if(servoRefAngle[1] < angle)
		{
			for(; servoRefAngle[1] < angle; servoRefAngle[1]++)
			{
				arr = 2.3*servoRefAngle[1] + 315;
				TIM2->CCR1 = arr;
		
				HAL_Delay(10);
			}
		}
		if(servoRefAngle[1] >= angle)
		{
			for(; servoRefAngle[1] >= angle; servoRefAngle[1]--)
			{
				arr = 2.3*servoRefAngle[1] + 315;
				TIM2->CCR1 = arr;
		
				HAL_Delay(10);
			}
		}
		
//		arr = 2.3*angle + 315;
//		TIM2->CCR1 = arr;
//		HAL_Delay(100);
		//-90~90

}
void servo2(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 2.3*angle + 524
		float arr ;
		if(servoRefAngle[2] < angle)
		{
			for(; servoRefAngle[2] < angle; servoRefAngle[2]++)
			{
				arr = 2.3*servoRefAngle[2] + 524;
				TIM2->CCR2 = arr;
		
				HAL_Delay(10);
			}
		}
		if(servoRefAngle[2] >= angle)
		{
			for(; servoRefAngle[2] >= angle; servoRefAngle[2]--)
			{
				arr = 2.3*servoRefAngle[2] + 524;
				TIM2->CCR2 = arr;
		
				HAL_Delay(10);
			}
		}
		
//		arr = 2.3*angle + 524;
//		TIM2->CCR2 = arr;
//		HAL_Delay(100);
		//-180到0
}
void servo3(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为4199*2.5%=105 最大值为4199*12.5%=524
		//对应角度 ccr = 2.3*angle + 315
		float arr ;
		if(servoRefAngle[3] < angle)
		{
			for(; servoRefAngle[3] <= angle; servoRefAngle[3]++)
			{
				arr = 2.3*servoRefAngle[3] + 315;
				TIM2->CCR3 = arr;
		
				HAL_Delay(10);
			}
		}
		if(servoRefAngle[3] >= angle)
		{
			for(; servoRefAngle[3] >= angle; servoRefAngle[3]--)
			{
				arr = 2.3*servoRefAngle[3] + 315;
				TIM2->CCR3 = arr;
		
				HAL_Delay(10);
			}
		}
		
//		arr = 2.3*angle + 315;
//		TIM2->CCR3 = arr;
//		HAL_Delay(100);
		//-90~90
}
void clip(double angle)
{
		
		
		
		float arr ;
		arr = 2.3*angle + 315;
		TIM2->CCR4 = arr;
		HAL_Delay(100);

}


void init_pos()
{		
		tx.pointX = 0.35;
		tx.pointY = 0.21;
		tx.pointZ = 0.27;
		xQueueSendToBack(myQueue01Handle, (void *)&tx, 0);
		clip(-26);
		//attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
		//servo1(servoAngle[0]);
		//servo2(servoAngle[1]);
		//servo3(servoAngle[2]);
		HAL_Delay(2000);
	//rm_servo(servoAngle[3], target_speed);
}
void move_get()
{		
		tx.pointX = 0.35;
		tx.pointY = 0.35;
		tx.pointZ = 0.08;
		xQueueSendToBack(myQueue01Handle, (void *)&tx, 0);
		clip(-26);
		//attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
		//servo1(servoAngle[0]);
		//servo2(servoAngle[1]);
		//servo3(servoAngle[2]);
		HAL_Delay(2000);
//	rm_servo(servoAngle[3], target_speed);
}
void move_get2()
{
		tx.pointX = 0.35;
		tx.pointY = 0.35;
		tx.pointZ = 0.08;
		xQueueSendToBack(myQueue01Handle, (void *)&tx, 0);
		clip(-10);
		//attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
		//servo1(servoAngle[0]);
		//servo2(servoAngle[1]);
		//servo3(servoAngle[2]);
		HAL_Delay(2000);
}
void up()
{
		tx.pointX = 0.35;
		tx.pointY = 0.21;
		tx.pointZ = 0.27;
		xQueueSendToBack(myQueue01Handle, (void *)&tx, 0);
		clip(-10);
		//attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
		//servo1(servoAngle[0]);
		//servo2(servoAngle[1]);
		//servo3(servoAngle[2]);
		HAL_Delay(2000);
}
void move_put()
{
//	attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta);
//	servo1(servoAngle[0]);
//	servo2(servoAngle[1]);
//	servo3(servoAngle[2]);
//	rm_servo(servoAngle[3], target_speed);
}

//解算部分
uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta)
{
	
	float L1 = 0.20; //杆长
	float L2 = 0.12;
	float L3 = 0.13;
	float alpha, beta, lp, By, Bz;
	By = S.pointY-L3; //这里设置γ为-90
	Bz = S.pointZ;
	lp = By*By + Bz*Bz;
	
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
	alpha = atan2(Bz,By);
	
	beta = acos((L1*L1+lp-L2*L2)/(2.0*L1*sqrt(lp))); //这里使用弧度制

	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;								//1号舵机角度
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;	//2号舵机角度
	ptheta[2] = (-ptheta[0] -ptheta[1]- 90);										//3号舵机角度,注意ptheta2是角度制了
	ptheta[3] = (atan2(S.pointX, S.pointY))*180.f/pi;						//云台舵机角度

	return 0;
}

uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta)
{
	
	float L1 = 0.20; //杆长
	float L2 = 0.12;
	float L3 = 0.13;
	float alpha, beta, lp, By, Bz;
	By = S.pointY; //这里设置γ为-90
	Bz = S.pointZ + L3;
	lp = By*By + Bz*Bz;
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
	alpha = atan2(Bz,By);
	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //这里使用弧度制,注意除法的类型转换，以及转换为角度制
	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;
	ptheta[2] = (-ptheta[0] -ptheta[1]- 180);
	ptheta[3] = (atan2(S.pointX, S.pointY))*180.f/pi;

	return 0;
}
	