#include "grip.h"
#include "tim.h"
#include "caculate.h"
#include "motor_pid.h"
void rm_servo(double angle, float target_speed)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//GM6020ռ�ձ�Ϊ5%��10%����СֵΪ3599*5%=179.95 ���ֵΪ3599*10%=359.9
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		double arr ;
		arr = (179.0/360)*angle + 180;
		TIM8->CCR1 = arr;
		rotor_pid_task(target_speed);
		HAL_Delay(100);

}
void servo1(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR1 = arr;
		HAL_Delay(100);

}
void servo2(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR2 = arr;
		HAL_Delay(100);

}
void servo3(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR3 = arr;
		HAL_Delay(100);

}
void clip(double angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR4 = arr;
		HAL_Delay(100);

}

//��е�۵Ĳ�ͬ��̬
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
